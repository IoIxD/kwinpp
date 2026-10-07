#pragma once

/* helper functions and shit to be used internally by kwinpp */

#include <QIcon>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QList>
#include <QPoint>
#include <QPointF>
#include <QRect>
#include <QRectF>
#include <QSize>
#include <QSizeF>
#include <QString>
#include <QUuid>
#include <string>
#include <type_traits>

#include "kwinpp.hpp"

namespace kwinpp_internal {

/* Every KWin object handed to us by the script is identified by the key it was
 * stored under in the script's object map. On our side each key gets exactly
 * one handle object (a KWin::Window etc.), so pointers can be turned back into
 * keys when they're passed as arguments. Handles live for the whole process. */
void *handle_for(const QString &ref, void *(*create)());
template <typename T> T *handle_for(const QString &ref) {
  if (ref.isEmpty())
    return nullptr;
  return static_cast<T *>(
      handle_for(ref, []() -> void * { return new T(); }));
}
/* The key for a handle, "workspace" for KWin::workspace. */
QString ref_of(const void *handle);

/* Runs func ("Class.member") on the object referenced by target inside KWin
 * and returns the JSON encoded result. Throws std::runtime_error if KWin
 * reports an error or doesn't answer. */
QJsonValue call_kwin_func_raw(const QString &target, const QString &func,
                              const QJsonArray &args);

template <typename> struct is_qlist : std::false_type {};
template <typename E> struct is_qlist<QList<E>> : std::true_type {};

template <typename> inline constexpr bool dependent_false = false;

template <typename T> QJsonValue to_json(const T &v) {
  using U = std::remove_cvref_t<T>;
  if constexpr (std::is_same_v<U, std::nullptr_t>) {
    return QJsonValue::Null;
  } else if constexpr (std::is_pointer_v<U> &&
                       !std::is_convertible_v<U, QString>) {
    if (!v)
      return QJsonValue::Null;
    return QJsonObject{{"$ref", ref_of(v)}};
  } else if constexpr (std::is_enum_v<U>) {
    return static_cast<qint64>(v);
  } else if constexpr (std::is_same_v<U, bool>) {
    return v;
  } else if constexpr (std::is_arithmetic_v<U>) {
    return static_cast<double>(v);
  } else if constexpr (std::is_convertible_v<const U &, QString>) {
    return QString(v);
  } else if constexpr (std::is_same_v<U, QRect> ||
                       std::is_same_v<U, QRectF>) {
    return QJsonObject{{"x", v.x()},
                       {"y", v.y()},
                       {"width", v.width()},
                       {"height", v.height()}};
  } else if constexpr (std::is_same_v<U, QPoint> ||
                       std::is_same_v<U, QPointF>) {
    return QJsonObject{{"x", v.x()}, {"y", v.y()}};
  } else if constexpr (std::is_same_v<U, QSize> ||
                       std::is_same_v<U, QSizeF>) {
    return QJsonObject{{"width", v.width()}, {"height", v.height()}};
  } else if constexpr (is_qlist<U>::value) {
    QJsonArray array;
    for (const auto &e : v)
      array.append(to_json(e));
    return array;
  } else {
    static_assert(dependent_false<U>, "kwinpp: can't send this type to KWin");
  }
}

template <typename T> T from_json(const QJsonValue &v) {
  using U = std::remove_cv_t<T>;
  if constexpr (std::is_void_v<U>) {
    return;
  } else if constexpr (std::is_pointer_v<U>) {
    return handle_for<std::remove_cv_t<std::remove_pointer_t<U>>>(
        v.toString());
  } else if constexpr (std::is_same_v<U, bool>) {
    return v.toBool();
  } else if constexpr (std::is_enum_v<U> || std::is_integral_v<U>) {
    return static_cast<U>(v.toInteger());
  } else if constexpr (std::is_floating_point_v<U>) {
    return v.toDouble();
  } else if constexpr (std::is_same_v<U, QString>) {
    return v.toString();
  } else if constexpr (std::is_same_v<U, QUuid>) {
    return QUuid::fromString(v.toString());
  } else if constexpr (std::is_same_v<U, QRect>) {
    const QJsonObject o = v.toObject();
    return QRect(qRound(o["x"].toDouble()), qRound(o["y"].toDouble()),
                 qRound(o["width"].toDouble()), qRound(o["height"].toDouble()));
  } else if constexpr (std::is_same_v<U, QRectF>) {
    const QJsonObject o = v.toObject();
    return QRectF(o["x"].toDouble(), o["y"].toDouble(), o["width"].toDouble(),
                  o["height"].toDouble());
  } else if constexpr (std::is_same_v<U, QPoint>) {
    const QJsonObject o = v.toObject();
    return QPoint(qRound(o["x"].toDouble()), qRound(o["y"].toDouble()));
  } else if constexpr (std::is_same_v<U, QPointF>) {
    const QJsonObject o = v.toObject();
    return QPointF(o["x"].toDouble(), o["y"].toDouble());
  } else if constexpr (std::is_same_v<U, QSize>) {
    const QJsonObject o = v.toObject();
    return QSize(qRound(o["width"].toDouble()), qRound(o["height"].toDouble()));
  } else if constexpr (std::is_same_v<U, QSizeF>) {
    const QJsonObject o = v.toObject();
    return QSizeF(o["width"].toDouble(), o["height"].toDouble());
  } else if constexpr (std::is_same_v<U, QIcon>) {
    // icons can't be serialized from inside a KWin script
    return QIcon();
  } else if constexpr (is_qlist<U>::value) {
    U list;
    for (const QJsonValue &e : v.toArray())
      list.append(from_json<typename U::value_type>(e));
    return list;
  } else {
    static_assert(dependent_false<U>,
                  "kwinpp: can't receive this type from KWin");
  }
}

/* Calls func ("Class.member", see the api table in the KWin script) on the
 * object referenced by target, e.g.
 *   call_kwin_func<QString>(ref_of(this), "Window.caption");
 *   call_kwin_func<void>("workspace", "WorkspaceWrapper.raiseWindow", w); */
template <typename Ret, typename... Args>
Ret call_kwin_func(const QString &target, const QString &func,
                   const Args &...args) {
  return from_json<Ret>(
      call_kwin_func_raw(target, func, QJsonArray{to_json(args)...}));
}

}; // namespace kwinpp_internal
