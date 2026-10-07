#pragma once

/* helper functions and shit to be used internally by kwinpp. Included by
 * kwinpp.hpp after it has picked the API's value types (KWin::Rect etc.). */

#include "kwinpp_types.hpp"
#include <cmath>
#include <cstdint>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

namespace kwinpp_internal {

/* A JSON value, as exchanged with the KWin script. Integers and floating point
 * numbers are kept apart so integers survive the trip exactly. */
struct Json;
using JsonArray = std::vector<Json>;
using JsonObject = std::vector<std::pair<std::string, Json>>;
struct Json {
  std::variant<std::nullptr_t, bool, std::int64_t, double, std::string,
               JsonArray, JsonObject>
      value;

  Json() : value(nullptr) {}
  Json(std::nullptr_t) : value(nullptr) {}
  Json(bool b) : value(b) {}
  Json(std::int64_t i) : value(i) {}
  Json(double d) : value(d) {}
  Json(std::string s) : value(std::move(s)) {}
  Json(JsonArray a) : value(std::move(a)) {}
  Json(JsonObject o) : value(std::move(o)) {}

  bool isNull() const { return std::holds_alternative<std::nullptr_t>(value); }
  bool toBool() const {
    const bool *b = std::get_if<bool>(&value);
    return b && *b;
  }
  std::int64_t toInteger() const {
    if (const auto *i = std::get_if<std::int64_t>(&value))
      return *i;
    if (const auto *d = std::get_if<double>(&value))
      return static_cast<std::int64_t>(*d);
    return 0;
  }
  double toDouble() const {
    if (const auto *d = std::get_if<double>(&value))
      return *d;
    if (const auto *i = std::get_if<std::int64_t>(&value))
      return static_cast<double>(*i);
    return 0.0;
  }
  std::string toString() const {
    const auto *s = std::get_if<std::string>(&value);
    return s ? *s : std::string();
  }
  JsonArray toArray() const {
    const auto *a = std::get_if<JsonArray>(&value);
    return a ? *a : JsonArray();
  }
  /* The member called key, or null if there isn't one. */
  const Json &operator[](std::string_view key) const {
    static const Json null;
    if (const auto *o = std::get_if<JsonObject>(&value))
      for (const auto &[k, v] : *o)
        if (k == key)
          return v;
    return null;
  }
};

/* Every KWin object handed to us by the script is identified by the key it was
 * stored under in the script's object map. On our side each key gets exactly
 * one handle object (a KWin::Window etc.), so pointers can be turned back into
 * keys when they're passed as arguments. Handles live until they're deleted. */
void *handle_for(const std::string &ref, void *(*create)());
template <typename T> T *handle_for(const std::string &ref) {
  if (ref.empty())
    return nullptr;
  return static_cast<T *>(handle_for(ref, []() -> void * { return new T(); }));
}
/* The key for a handle, "workspace" for KWin::workspace. */
std::string ref_of(const void *handle);
/* Called by handle destructors. Forgets the handle and tells the script to
 * drop the object it refers to. Does nothing for anything that isn't a handle
 * (e.g. a copy of one). */
void release_handle(const void *handle) noexcept;

/* Runs func ("Class.member") on the object referenced by target inside KWin
 * and returns the result. Throws std::runtime_error if KWin reports an error
 * or doesn't answer. */
Json call_kwin_func_raw(const std::string &target, const std::string &func,
                        JsonArray args);

template <typename> struct is_list : std::false_type {};
template <typename E> struct is_list<std::vector<E>> : std::true_type {};
#ifndef KWINPP_NO_QT
template <typename E> struct is_list<QList<E>> : std::true_type {};
#endif

/* qRound(): halfway cases round away from zero. */
inline int round_to_int(double d) { return int(std::round(d)); }

template <typename> inline constexpr bool dependent_false = false;

template <typename T> Json to_json(const T &v) {
  using U = std::remove_cvref_t<T>;
  if constexpr (std::is_same_v<U, std::nullptr_t>) {
    return Json();
  } else if constexpr (std::is_convertible_v<const U &, std::string_view>) {
    return Json(std::string(std::string_view(v)));
#ifndef KWINPP_NO_QT
  } else if constexpr (std::is_same_v<U, QString>) {
    return Json(v.toStdString());
  } else if constexpr (std::is_same_v<U, QUuid>) {
    return Json(v.toString().toStdString());
#endif
  } else if constexpr (std::is_pointer_v<U>) {
    if (!v)
      return Json();
    return Json(JsonObject{{"$ref", Json(ref_of(v))}});
  } else if constexpr (std::is_enum_v<U>) {
    return Json(static_cast<std::int64_t>(v));
  } else if constexpr (std::is_same_v<U, bool>) {
    return Json(v);
  } else if constexpr (std::is_integral_v<U>) {
    return Json(static_cast<std::int64_t>(v));
  } else if constexpr (std::is_floating_point_v<U>) {
    return Json(static_cast<double>(v));
  } else if constexpr (std::is_same_v<U, KWin::Rect> ||
                       std::is_same_v<U, KWin::RectF>) {
    return Json(JsonObject{{"x", Json(double(v.x()))},
                           {"y", Json(double(v.y()))},
                           {"width", Json(double(v.width()))},
                           {"height", Json(double(v.height()))}});
  } else if constexpr (std::is_same_v<U, KWin::Point> ||
                       std::is_same_v<U, KWin::PointF>) {
    return Json(
        JsonObject{{"x", Json(double(v.x()))}, {"y", Json(double(v.y()))}});
  } else if constexpr (std::is_same_v<U, KWin::Size> ||
                       std::is_same_v<U, KWin::SizeF>) {
    return Json(JsonObject{{"width", Json(double(v.width()))},
                           {"height", Json(double(v.height()))}});
  } else if constexpr (is_list<U>::value) {
    JsonArray array;
    array.reserve(v.size());
    for (const auto &e : v)
      array.push_back(to_json(e));
    return Json(std::move(array));
  } else {
    static_assert(dependent_false<U>, "kwinpp: can't send this type to KWin");
  }
}

template <typename T> T from_json(const Json &v) {
  using U = std::remove_cv_t<T>;
  if constexpr (std::is_void_v<U>) {
    return;
  } else if constexpr (std::is_pointer_v<U>) {
    return handle_for<std::remove_cv_t<std::remove_pointer_t<U>>>(v.toString());
  } else if constexpr (std::is_same_v<U, bool>) {
    return v.toBool();
  } else if constexpr (std::is_enum_v<U> || std::is_integral_v<U>) {
    return static_cast<U>(v.toInteger());
  } else if constexpr (std::is_floating_point_v<U>) {
    return static_cast<U>(v.toDouble());
  } else if constexpr (std::is_same_v<U, std::string>) {
    return v.toString();
#ifndef KWINPP_NO_QT
  } else if constexpr (std::is_same_v<U, QString>) {
    return QString::fromStdString(v.toString());
  } else if constexpr (std::is_same_v<U, QUuid>) {
    return QUuid::fromString(QString::fromStdString(v.toString()));
  } else if constexpr (std::is_same_v<U, QIcon>) {
    // icons can't be serialized from inside a KWin script
    return QIcon();
#endif
  } else if constexpr (std::is_same_v<U, KWin::Rect>) {
    return KWin::Rect(round_to_int(v["x"].toDouble()),
                      round_to_int(v["y"].toDouble()),
                      round_to_int(v["width"].toDouble()),
                      round_to_int(v["height"].toDouble()));
  } else if constexpr (std::is_same_v<U, KWin::RectF>) {
    return KWin::RectF(v["x"].toDouble(), v["y"].toDouble(),
                       v["width"].toDouble(), v["height"].toDouble());
  } else if constexpr (std::is_same_v<U, KWin::Point>) {
    return KWin::Point(round_to_int(v["x"].toDouble()),
                       round_to_int(v["y"].toDouble()));
  } else if constexpr (std::is_same_v<U, KWin::PointF>) {
    return KWin::PointF(v["x"].toDouble(), v["y"].toDouble());
  } else if constexpr (std::is_same_v<U, KWin::Size>) {
    return KWin::Size(round_to_int(v["width"].toDouble()),
                      round_to_int(v["height"].toDouble()));
  } else if constexpr (std::is_same_v<U, KWin::SizeF>) {
    return KWin::SizeF(v["width"].toDouble(), v["height"].toDouble());
  } else if constexpr (is_list<U>::value) {
    U list;
    if (const auto *array = std::get_if<JsonArray>(&v.value)) {
      list.reserve(array->size());
      for (const Json &e : *array)
        list.push_back(from_json<typename U::value_type>(e));
    }
    return list;
  } else {
    static_assert(dependent_false<U>,
                  "kwinpp: can't receive this type from KWin");
  }
}

/* Calls func ("Class.member", see the api table in the KWin script) on the
 * object referenced by target, e.g.
 *   call_kwin_func<std::string>(ref_of(this), "Window.caption");
 *   call_kwin_func<void>("workspace", "WorkspaceWrapper.raiseWindow", w); */
template <typename Ret, typename... Args>
Ret call_kwin_func(const std::string &target, const std::string &func,
                   const Args &...args) {
  return from_json<Ret>(
      call_kwin_func_raw(target, func, JsonArray{to_json(args)...}));
}

}; // namespace kwinpp_internal
