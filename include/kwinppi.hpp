#pragma once

/* helper functions and shit to be used internally by kwinpp. */

#include "kwinpp_types.hpp"
#include <cmath>
#include <cstdint>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

#include <nlohmann/json.hpp>

#ifndef KWINPP_NO_QT
#include <QIcon>
#include <QString>
#include <QUuid>
#endif

namespace kwinpp_internal {

/* get a kwin object based on the map handle*/
template <typename T> T *handle_for(const std::string &ref) {
  void *handle_for_nongeneric(const std::string &ref, void *(*create)());
  return static_cast<T *>(
      handle_for_nongeneric(ref, []() -> void * { return new T(); }));
}

std::string ref_of(const void *handle);
void release_handle(const void *handle) noexcept;

/* Runs func ("Class.member") on the object referenced by target inside KWin
 * and returns the result. Throws std::runtime_error if KWin reports an error
 * or doesn't answer. */
nlohmann::json call_kwin_func_raw(const std::string &target,
                                  const std::string &func,
                                  std::vector<nlohmann::json> args);

template <typename> struct is_list : std::false_type {};
template <typename E> struct is_list<std::vector<E>> : std::true_type {};
#ifndef KWINPP_NO_QT
template <typename E> struct is_list<QList<E>> : std::true_type {};
#endif

template <typename> inline constexpr bool dependent_false = false;

/* Lenient readers for values from the script: anything missing or of the
 * wrong type reads as false, 0 or empty instead of throwing. */
inline bool json_bool(const nlohmann::json &v) {
  return v.is_boolean() && v.get<bool>();
}
inline std::int64_t json_integer(const nlohmann::json &v) {
  return v.is_number() ? v.get<std::int64_t>() : 0;
}
inline double json_double(const nlohmann::json &v) {
  return v.is_number() ? v.get<double>() : 0.0;
}
inline std::string json_string(const nlohmann::json &v) {
  return v.is_string() ? v.get<std::string>() : std::string();
}
/* The member called key, or null if there isn't one. */
inline const nlohmann::json &json_member(const nlohmann::json &v,
                                         const std::string &key) {
  static const nlohmann::json null;
  if (v.is_object())
    if (const auto it = v.find(key); it != v.end())
      return *it;
  return null;
}

template <typename T> nlohmann::json to_json(const T &v) {
#ifdef KWINPP_NO_QT
  using U = std::remove_cvref_t<T>;
#else
  using U = std::remove_cv_t<std::remove_reference_t<T>>;
#endif

  if constexpr (std::is_same_v<U, std::nullptr_t>) {
    return nlohmann::json();
  } else if constexpr (std::is_convertible_v<const U &, std::string_view>) {
    return nlohmann::json(std::string(std::string_view(v)));
#ifndef KWINPP_NO_QT
  } else if constexpr (std::is_same_v<U, QString>) {
    return nlohmann::json(v.toStdString());
  } else if constexpr (std::is_same_v<U, QUuid>) {
    return nlohmann::json(v.toString().toStdString());
#endif
  } else if constexpr (std::is_pointer_v<U>) {
    if (!v)
      return nlohmann::json();
    return nlohmann::json({{"$ref", nlohmann::json(ref_of(v))}});
  } else if constexpr (std::is_enum_v<U>) {
    return nlohmann::json(static_cast<std::int64_t>(v));
  } else if constexpr (std::is_same_v<U, bool>) {
    return nlohmann::json(v);
  } else if constexpr (std::is_integral_v<U>) {
    return nlohmann::json(static_cast<std::int64_t>(v));
  } else if constexpr (std::is_floating_point_v<U>) {
    return nlohmann::json(static_cast<double>(v));
  } else if constexpr (std::is_same_v<U, KWin::Rect> ||
                       std::is_same_v<U, KWin::RectF>) {
    return nlohmann::json({{"x", nlohmann::json(double(v.x()))},
                           {"y", nlohmann::json(double(v.y()))},
                           {"width", nlohmann::json(double(v.width()))},
                           {"height", nlohmann::json(double(v.height()))}});
  } else if constexpr (std::is_same_v<U, KWin::Point> ||
                       std::is_same_v<U, KWin::PointF>) {
    return nlohmann::json({{"x", nlohmann::json(double(v.x()))},
                           {"y", nlohmann::json(double(v.y()))}});
  } else if constexpr (std::is_same_v<U, KWin::Size> ||
                       std::is_same_v<U, KWin::SizeF>) {
    return nlohmann::json({{"width", nlohmann::json(double(v.width()))},
                           {"height", nlohmann::json(double(v.height()))}});
  } else if constexpr (is_list<U>::value) {
    std::vector<nlohmann::json> array;
    array.reserve(v.size());
    for (const auto &e : v)
      array.push_back(to_json(e));
    return nlohmann::json(std::move(array));
  } else {
    static_assert(dependent_false<U>, "kwinpp: can't send this type to KWin");
  }
}

template <typename T> T from_json(const nlohmann::json &v) {
  using U = std::remove_cv_t<T>;
  if constexpr (std::is_void_v<U>) {
    return;
  } else if constexpr (std::is_pointer_v<U>) {
    return handle_for<std::remove_cv_t<std::remove_pointer_t<U>>>(
        json_string(v));
  } else if constexpr (std::is_same_v<U, bool>) {
    return json_bool(v);
  } else if constexpr (std::is_enum_v<U> || std::is_integral_v<U>) {
    return static_cast<U>(json_integer(v));
  } else if constexpr (std::is_floating_point_v<U>) {
    return static_cast<U>(json_double(v));
  } else if constexpr (std::is_same_v<U, std::string>) {
    return json_string(v);
#ifndef KWINPP_NO_QT
  } else if constexpr (std::is_same_v<U, QString>) {
    return QString::fromStdString(json_string(v));
  } else if constexpr (std::is_same_v<U, QUuid>) {
    return QUuid::fromString(QString::fromStdString(json_string(v)));
  } else if constexpr (std::is_same_v<U, QIcon>) {
    // icons can't be serialized from inside a KWin script
    return QIcon();
#endif
  } else if constexpr (std::is_same_v<U, KWin::Rect>) {
    return KWin::Rect(int(std::round(json_double(json_member(v, "x")))),
                      int(std::round(json_double(json_member(v, "y")))),
                      int(std::round(json_double(json_member(v, "width")))),
                      int(std::round(json_double(json_member(v, "height")))));
  } else if constexpr (std::is_same_v<U, KWin::RectF>) {
    return KWin::RectF(json_double(json_member(v, "x")),
                       json_double(json_member(v, "y")),
                       json_double(json_member(v, "width")),
                       json_double(json_member(v, "height")));
  } else if constexpr (std::is_same_v<U, KWin::Point>) {
    return KWin::Point(int(std::round(json_double(json_member(v, "x")))),
                       int(std::round(json_double(json_member(v, "y")))));
  } else if constexpr (std::is_same_v<U, KWin::PointF>) {
    return KWin::PointF(json_double(json_member(v, "x")),
                        json_double(json_member(v, "y")));
  } else if constexpr (std::is_same_v<U, KWin::Size>) {
    return KWin::Size(int(std::round(json_double(json_member(v, "width")))),
                      int(std::round(json_double(json_member(v, "height")))));
  } else if constexpr (std::is_same_v<U, KWin::SizeF>) {
    return KWin::SizeF(json_double(json_member(v, "width")),
                       json_double(json_member(v, "height")));
  } else if constexpr (is_list<U>::value) {
    U list;
    if (v.is_array()) {
      list.reserve(v.size());
      for (const nlohmann::json &e : v)
        list.push_back(from_json<typename U::value_type>(e));
    }
    return list;
  } else {
    static_assert(dependent_false<U>,
                  "kwinpp: can't receive this type from KWin");
  }
}

template <typename Ret, typename... Args>
Ret call_kwin_func(const std::string &target, const std::string &func,
                   const Args &...args) {
  return from_json<Ret>(call_kwin_func_raw(target, func, {to_json(args)...}));
}

}; // namespace kwinpp_internal
