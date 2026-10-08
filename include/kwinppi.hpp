#pragma once

/* helper functions and shit to be used internally by kwinpp. */

#include "kwinpp_types.hpp"
#include <chrono>
#include <cmath>
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

#include <nlohmann/json.hpp>

#ifndef KWINPP_NO_QT
#include <QIcon>
#include <QPalette>
#include <QRegion>
#include <QString>
#include <QUuid>
#endif

namespace kwinpp {

/* Returned by the on*() signal functions. Callbacks stay connected until
 * disconnect() is called or the object they're connected to is destroyed;
 * letting a Connection go out of scope does nothing. */
class Connection {
public:
  Connection() = default;
  explicit Connection(std::uint64_t id) : id(id) {}

  /* Stops the callback from being called. Safe to call more than once, and
   * from inside the callback itself. */
  void disconnect() noexcept;

private:
  std::uint64_t id = 0; // 0: not connected
};

}; // namespace kwinpp

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
    if (!v.is_string())
      return nullptr;
    return handle_for<std::remove_cv_t<std::remove_pointer_t<U>>>(
        json_string(v));
  } else if constexpr (std::is_same_v<U, bool>) {
    return json_bool(v);
  } else if constexpr (std::is_enum_v<U> || std::is_integral_v<U>) {
    return static_cast<U>(json_integer(v));
  } else if constexpr (std::is_floating_point_v<U>) {
    return static_cast<U>(json_double(v));
  } else if constexpr (std::is_same_v<U, std::chrono::milliseconds>) {
    return U(json_integer(v));
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
  } else if constexpr (std::is_same_v<U, QPalette>) {
    // neither can palettes
    return QPalette();
  } else if constexpr (std::is_same_v<U, QRegion>) {
    QRegion region;
    if (v.is_array())
      for (const nlohmann::json &e : v)
        region += from_json<KWin::Rect>(e);
    return region;
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

/* Called with the signal's arguments, as sent by the script. */
using SignalHandler = std::function<void(const nlohmann::json &args)>;

/* Connects handler to signal on the object referenced by target inside KWin.
 * Throws std::runtime_error if the object doesn't have that signal. */
kwinpp::Connection connect_kwin_signal_raw(const std::string &target,
                                           const std::string &signal,
                                           SignalHandler handler);

template <typename... Args, std::size_t... I>
void invoke_with_json(const std::function<void(Args...)> &callback,
                      const nlohmann::json &args, std::index_sequence<I...>) {
  static const nlohmann::json null;
  callback(from_json<std::decay_t<Args>>(
      args.is_array() && I < args.size() ? args[I] : null)...);
}

/* Callbacks are run one at a time on a thread of kwinpp's, so they can call
 * back into KWin but have to synchronize with the rest of the program. */
template <typename... Args>
kwinpp::Connection connect_kwin_signal(const std::string &target,
                                       const std::string &signal,
                                       std::function<void(Args...)> callback) {
  return connect_kwin_signal_raw(
      target, signal,
      [callback = std::move(callback)](const nlohmann::json &args) {
        invoke_with_json(callback, args, std::index_sequence_for<Args...>{});
      });
}

}; // namespace kwinpp_internal
