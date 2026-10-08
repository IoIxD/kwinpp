#include "kwinpp.hpp"
#include "kwinppi.hpp"

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdlib>
#include <mutex>
#include <optional>
#include <queue>
#include <stdexcept>
#include <string>
#include <string_view>
#include <thread>
#include <vector>

#include <cerrno>
#include <dbus/dbus.h>
#include <poll.h>
#include <sys/eventfd.h>
#include <unistd.h>

#ifdef KWINPP_NO_QT
#include <unordered_map>
#else
#include <QHash>
#endif

namespace KWin {
WorkspaceWrapper workspace;
}

namespace {

constexpr auto SERVICE = "net.ioi_xd.kwinpp";
constexpr auto PATH = "/net/ioi_xd/kwinpp";
constexpr auto INTERFACE = "net.ioi_xd.kwinpp";
constexpr auto PLUGIN_NAME = "kwinpp";

/* Loaded into KWin once. It long-polls us over D-Bus for requests
 * ({id, target, func, args}), runs the matching entry of `api` and sends
 * {id, value} or {id, error} back. {release} requests drop an object from
 * `objects` and get no answer. KWin objects never leave KWin: they're kept
 * in `objects` and we get the key they're stored under instead. */
const char *const KWIN_SCRIPT = R"KWINPP(
const SERVICE = "net.ioi_xd.kwinpp";
const PATH = "/net/ioi_xd/kwinpp";
const INTERFACE = "net.ioi_xd.kwinpp";

const objects = new Map(); // key -> object
const keys = new Map();    // object -> key
let nextKey = 0;

function ref(obj) {
    let key = keys.get(obj);
    if (key === undefined) {
        key = "obj:" + nextKey++;
        keys.set(obj, key);
        objects.set(key, obj);
    }
    return key;
}

function deref(key) {
    if (key === "workspace")
        return workspace;
    const obj = objects.get(key);
    if (obj === undefined)
        throw new Error("unknown kwinpp reference " + key);
    return obj;
}

// Forgets the object stored under key, so KWin can free it.
function release(key) {
    const obj = objects.get(key);
    if (obj === undefined)
        return;
    objects.delete(key);
    keys.delete(obj);
}

function encode(v) {
    if (v === null || v === undefined)
        return null;
    switch (typeof v) {
    case "boolean":
    case "number":
    case "string":
        return v;
    }
    if ("objectName" in v) // QObject
        return ref(v);
    if (typeof v.length === "number") // QList
        return Array.prototype.map.call(v, encode);
    if ("width" in v && "x" in v)
        return {x: v.x, y: v.y, width: v.width, height: v.height};
    if ("width" in v)
        return {width: v.width, height: v.height};
    if ("x" in v)
        return {x: v.x, y: v.y};
    return String(v); // QUuid
}

function decode(v) {
    if (v === null || typeof v !== "object")
        return v;
    if (Array.isArray(v))
        return v.map(decode);
    if ("$ref" in v)
        return deref(v.$ref);
    return v; // rects, points and sizes are passed as plain objects
}

const api = {};
function getters(cls, names) {
    for (const name of names)
        api[cls + "." + name] = (obj) => obj[name];
}
function properties(cls, names) {
    getters(cls, names);
    for (const name of names) {
        const setter = "set" + name[0].toUpperCase() + name.slice(1);
        api[cls + "." + setter] = (obj, value) => { obj[name] = value; };
    }
}
function methods(cls, names) {
    for (const name of names)
        api[cls + "." + name] = (obj, ...args) => obj[name](...args);
}

getters("WorkspaceWrapper", [
    "desktops", "desktopGridSize", "desktopGridWidth", "desktopGridHeight",
    "workspaceWidth", "workspaceHeight", "workspaceSize", "activeScreen",
    "screens", "activities", "virtualScreenSize", "virtualScreenGeometry",
    "stackingOrder", "cursorPos",
]);
properties("WorkspaceWrapper", ["currentDesktop", "activeWindow", "currentActivity"]);
methods("WorkspaceWrapper", [
    "slotSwitchDesktopNext", "slotSwitchDesktopPrevious", "slotSwitchDesktopRight",
    "slotSwitchDesktopLeft", "slotSwitchDesktopUp", "slotSwitchDesktopDown",
    "slotSwitchToNextScreen", "slotSwitchToPrevScreen", "slotSwitchToRightScreen",
    "slotSwitchToLeftScreen", "slotSwitchToAboveScreen", "slotSwitchToBelowScreen",
    "slotWindowToNextScreen", "slotWindowToPrevScreen", "slotWindowToRightScreen",
    "slotWindowToLeftScreen", "slotWindowToAboveScreen", "slotWindowToBelowScreen",
    "slotToggleShowDesktop", "slotWindowMaximize", "slotWindowMaximizeVertical",
    "slotWindowMaximizeHorizontal", "slotWindowMinimize", "slotWindowShade",
    "slotWindowRaise", "slotWindowLower", "slotWindowRaiseOrLower",
    "slotActivateAttentionWindow", "slotWindowMoveLeft", "slotWindowMoveRight",
    "slotWindowMoveUp", "slotWindowMoveDown", "slotWindowExpandHorizontal",
    "slotWindowExpandVertical", "slotWindowShrinkHorizontal",
    "slotWindowShrinkVertical", "slotWindowQuickTileLeft",
    "slotWindowQuickTileRight", "slotWindowQuickTileTop",
    "slotWindowQuickTileBottom", "slotWindowQuickTileTopLeft",
    "slotWindowQuickTileTopRight", "slotWindowQuickTileBottomLeft",
    "slotWindowQuickTileBottomRight", "slotSwitchWindowUp", "slotSwitchWindowDown",
    "slotSwitchWindowRight", "slotSwitchWindowLeft", "slotIncreaseWindowOpacity",
    "slotLowerWindowOpacity", "slotWindowOperations", "slotWindowClose",
    "slotWindowMove", "slotWindowResize", "slotWindowAbove", "slotWindowBelow",
    "slotWindowOnAllDesktops", "slotWindowFullScreen", "slotWindowNoBorder",
    "slotWindowToNextDesktop", "slotWindowToPreviousDesktop",
    "slotWindowToDesktopRight", "slotWindowToDesktopLeft", "slotWindowToDesktopUp",
    "slotWindowToDesktopDown",
    "sendClientToScreen", "showOutline", "hideOutline", "currentDesktopForScreen",
    "setCurrentDesktopForScreen", "screenAt", "tilingForScreen", "clientArea",
    "createDesktop", "removeDesktop", "supportInformation", "raiseWindow",
    "getClient", "windowAt", "isEffectActive",
]);

getters("VirtualDesktop", ["id", "x11DesktopNumber"]);
properties("VirtualDesktop", ["name"]);

getters("Output", [
    "geometry", "devicePixelRatio", "name", "manufacturer", "model", "serialNumber",
]);
methods("Output", ["mapToGlobal", "mapFromGlobal"]);

getters("Window", [
    "bufferGeometry", "clientGeometry", "pos", "size", "x", "y", "width", "height",
    "output", "rect", "resourceName", "resourceClass", "windowRole",
    "desktopWindow", "dock", "toolbar", "menu", "normalWindow", "dialog", "splash",
    "utility", "dropdownMenu", "popupMenu", "tooltip", "notification",
    "criticalNotification", "appletPopup", "onScreenDisplay", "comboBox",
    "dndIcon", "windowType", "managed", "deleted", "popupWindow", "outline",
    "internalId", "pid", "stackingOrder", "fullScreenable", "active", "closeable",
    "icon", "shadeable", "minimizable", "iconGeometry", "specialWindow", "caption",
    "minSize", "maxSize", "wantsInput", "transient", "transientFor", "modal",
    "move", "resize", "decorationHasAlpha", "providesContextHelp", "maximizable",
    "moveable", "moveableAcrossScreens", "resizeable", "desktopFileName",
    "hasApplicationMenu", "applicationMenuActive", "unresponsive", "colorScheme",
    "hidden", "inputMethod",
]);
properties("Window", [
    "opacity", "skipsCloseAnimation", "fullScreen", "desktops", "onAllDesktops",
    "activities", "skipTaskbar", "skipPager", "skipSwitcher", "keepAbove",
    "keepBelow", "shade", "minimized", "demandsAttention", "frameGeometry",
    "noBorder", "tile",
]);
methods("Window", ["closeWindow", "setMaximize"]);

getters("TileManager", ["rootTile"]);
methods("TileManager", ["bestTileForPosition"]);

getters("Tile", [
    "absoluteGeometry", "absoluteGeometryInScreen", "positionInLayout", "parent",
    "tiles", "windows", "isLayout", "canBeRemoved",
]);
properties("Tile", ["relativeGeometry", "padding"]);
methods("Tile", ["resizeByPixels"]);

function handle(request) {
    if (request === "") // keepalive
        return;
    const req = JSON.parse(request);
    if ("release" in req) { // sent by handle destructors, not answered
        release(req.release);
        return;
    }
    let reply;
    try {
        const fn = api[req.func];
        if (fn === undefined)
            throw new Error("unknown kwinpp function " + req.func);
        reply = {id: req.id, value: encode(fn(deref(req.target), ...req.args.map(decode)))};
    } catch (e) {
        reply = {id: req.id, error: String(e)};
    }
    callDBus(SERVICE, PATH, INTERFACE, "result", JSON.stringify(reply));
}

function poll() {
    callDBus(SERVICE, PATH, INTERFACE, "poll", (request) => {
        try {
            handle(request);
        } finally {
            poll();
        }
    });
}
poll();
)KWINPP";

/* Owns a libdbus error and frees it when it goes out of scope. */
struct DBusErrorHolder {
  DBusError error;
  DBusErrorHolder() { dbus_error_init(&error); }
  ~DBusErrorHolder() { dbus_error_free(&error); }
  DBusErrorHolder(const DBusErrorHolder &) = delete;
  DBusErrorHolder &operator=(const DBusErrorHolder &) = delete;
  operator DBusError *() { return &error; }
  bool isSet() const { return dbus_error_is_set(&error); }
  std::string message() const { return error.message ? error.message : ""; }
};

constexpr auto INTROSPECTION =
    R"(<!DOCTYPE node PUBLIC "-//freedesktop//DTD D-BUS Object Introspection 1.0//EN"
 "http://www.freedesktop.org/standards/dbus/1.0/introspect.dtd">
<node>
  <interface name="net.ioi_xd.kwinpp">
    <method name="poll"><arg direction="out" type="s"/></method>
    <method name="result"><arg direction="in" type="s"/></method>
  </interface>
</node>
)";

/* KWin gives up on a D-Bus call after ~25s and the script's poll loop dies
 * with it, so idle polls are answered before that happens. */
constexpr auto KEEPALIVE = std::chrono::seconds(10);

/* The D-Bus end of the script. kwinpp has a private session bus connection
 * that's only touched by its own thread (see run), so polls get answered
 * whatever the program is doing and no event loop is needed from it. */
class Bridge {
public:
  DBusConnection *connection = nullptr;
  int wakeFd = -1; // eventfd, written to make run() look at `requests`

  std::mutex mutex;
  std::condition_variable cv;
  bool ready = false; // the script has polled at least once
  DBusMessage *pendingPoll = nullptr;
  std::chrono::steady_clock::time_point pendingPollSince;
  std::queue<std::string> requests;
#ifdef KWINPP_NO_QT
  std::unordered_map<int64_t, nlohmann::json> results;
#else
  QHash<int64_t, nlohmann::json> results;
#endif

  /* Queues a request for the script. Call from any thread, with mutex held. */
  void submit(const std::string &request) {
    requests.push(request);
    const uint64_t one = 1;
    (void)!write(wakeFd, &one, sizeof(one));
  }

  static DBusHandlerResult handleMessage(DBusConnection *, DBusMessage *message,
                                         void *data) {
    return static_cast<Bridge *>(data)->handle(message);
  }

  /* The bus loop. Never returns unless the bus connection goes away. */
  void run() {
    const int busFd = [this] {
      int fd = -1;
      dbus_connection_get_unix_fd(connection, &fd);
      return fd;
    }();
    for (;;) {
      // messages may already be buffered (e.g. read during start()'s calls)
      if (!dbus_connection_read_write(connection, 0))
        return;
      while (dbus_connection_dispatch(connection) ==
             DBUS_DISPATCH_DATA_REMAINS) {
      }

      int timeout = -1;
      {
        std::lock_guard lock(mutex);
        flush();
        if (pendingPoll) {
          const auto now = std::chrono::steady_clock::now();
          if (now - pendingPollSince >= KEEPALIVE)
            replyToPoll(std::string());
          else
            timeout = std::chrono::ceil<std::chrono::milliseconds>(
                          pendingPollSince + KEEPALIVE - now)
                          .count();
        }
      }

      pollfd fds[] = {
          {busFd,
           short(POLLIN |
                 (dbus_connection_has_messages_to_send(connection) ? POLLOUT
                                                                   : 0)),
           0},
          {wakeFd, POLLIN, 0},
      };
      if (poll(fds, 2, timeout) > 0 && (fds[1].revents & POLLIN)) {
        uint64_t count;
        (void)!read(wakeFd, &count, sizeof(count));
      }
    }
  }

private:
  DBusHandlerResult handle(DBusMessage *message) {
    if (dbus_message_is_method_call(message, INTERFACE, "poll")) {
      std::lock_guard lock(mutex);
      if (pendingPoll)
        replyToPoll(std::string());
      pendingPoll = dbus_message_ref(message);
      pendingPollSince = std::chrono::steady_clock::now();
      ready = true;
      flush();
      cv.notify_all();
      return DBUS_HANDLER_RESULT_HANDLED;
    }
    if (dbus_message_is_method_call(message, INTERFACE, "result")) {
      DBusErrorHolder error;
      const char *json = nullptr;
      if (!dbus_message_get_args(message, error, DBUS_TYPE_STRING, &json,
                                 DBUS_TYPE_INVALID))
        return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
      nlohmann::json reply = nlohmann::json::parse(json, nullptr, false);
      sendReply(message, nullptr);
      if (!reply.is_object() || !reply.contains("id") ||
          !reply["id"].is_number_integer())
        return DBUS_HANDLER_RESULT_HANDLED;
      const int64_t id = reply["id"].get<int64_t>();
      std::lock_guard lock(mutex);
      results.insert_or_assign(id, std::move(reply));
      cv.notify_all();
      return DBUS_HANDLER_RESULT_HANDLED;
    }
    if (dbus_message_is_method_call(message, DBUS_INTERFACE_INTROSPECTABLE,
                                    "Introspect")) {
      sendReply(message, INTROSPECTION);
      return DBUS_HANDLER_RESULT_HANDLED;
    }
    return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
  }

  /* Answers call, with string as its only argument if it isn't null. */
  void sendReply(DBusMessage *call, const char *string) {
    DBusMessage *reply = dbus_message_new_method_return(call);
    if (string)
      dbus_message_append_args(reply, DBUS_TYPE_STRING, &string,
                               DBUS_TYPE_INVALID);
    dbus_connection_send(connection, reply, nullptr);
    dbus_message_unref(reply);
  }

  /* Call with mutex held and a poll pending. */
  void replyToPoll(const std::string &request) {
    sendReply(pendingPoll, request.data());
    dbus_message_unref(pendingPoll);
    pendingPoll = nullptr;
  }

  /* Hands the next request to a waiting poll. Call with mutex held. */
  void flush() {
    if (pendingPoll && !requests.empty())
      replyToPoll(requests.back());
  }
};

constexpr auto CALL_TIMEOUT = std::chrono::seconds(5);

Bridge *bridge = nullptr;

/* Calls method on KWin with the given string arguments, blocking until it
 * answers. Only used by start(), before the bus loop takes the connection. */
void callKWin(const char *path, const char *interface, const char *method,
              const std::vector<std::string> &args = {},
              int32_t *result = nullptr) {
  DBusMessage *message =
      dbus_message_new_method_call("org.kde.KWin", path, interface, method);
  for (const std::string &arg : args) {
    const char *value = arg.c_str();
    dbus_message_append_args(message, DBUS_TYPE_STRING, &value,
                             DBUS_TYPE_INVALID);
  }
  DBusErrorHolder error;
  DBusMessage *reply = dbus_connection_send_with_reply_and_block(
      bridge->connection, message, DBUS_TIMEOUT_USE_DEFAULT, error);
  dbus_message_unref(message);
  if (!reply)
    throw std::runtime_error("kwinpp: " + std::string(method) + ": " +
                             error.message());
  if (result && !dbus_message_get_args(reply, error, DBUS_TYPE_INT32, result,
                                       DBUS_TYPE_INVALID)) {
    dbus_message_unref(reply);
    throw std::runtime_error("kwinpp: " + std::string(method) + ": " +
                             error.message());
  }
  dbus_message_unref(reply);
}

/* Writes KWIN_SCRIPT to a new file in $TMPDIR (or /tmp) and returns its path.
 * KWin reads the file when the script is run, so it's kept around until the
 * program exits. */
const std::string &writeScriptFile() {
  const char *dir = getenv("TMPDIR");
  static std::string path =
      std::string(dir && *dir ? dir : "/tmp") + "/kwinpp-XXXXXX.js";
  const int fd = mkstemps(path.data(), 3);
  if (fd < 0)
    throw std::runtime_error("kwinpp: couldn't create the KWin script file");
  atexit([] { unlink(path.c_str()); });

  const std::string_view script = KWIN_SCRIPT;
  for (size_t written = 0; written < script.size();) {
    const ssize_t n =
        write(fd, script.data() + written, script.size() - written);
    if (n < 0 && errno == EINTR)
      continue;
    if (n < 0) {
      close(fd);
      throw std::runtime_error("kwinpp: couldn't write the KWin script");
    }
    written += n;
  }
  close(fd);
  return path;
}

void start() {
  dbus_threads_init_default();
  bridge = new Bridge();

  DBusErrorHolder error;
  // a private connection, so the program's own use of the bus isn't affected
  bridge->connection = dbus_bus_get_private(DBUS_BUS_SESSION, error);
  if (!bridge->connection)
    throw std::runtime_error("kwinpp: couldn't connect to the session bus: " +
                             error.message());
  dbus_connection_set_exit_on_disconnect(bridge->connection, false);

  if (dbus_bus_request_name(bridge->connection, SERVICE,
                            DBUS_NAME_FLAG_DO_NOT_QUEUE,
                            error) != DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER)
    throw std::runtime_error("kwinpp: couldn't register " +
                             std::string(SERVICE) + " on the session bus");
  static const DBusObjectPathVTable vtable = {nullptr, &Bridge::handleMessage};
  if (!dbus_connection_register_object_path(bridge->connection, PATH, &vtable,
                                            bridge))
    throw std::runtime_error("kwinpp: couldn't register " + std::string(PATH));

  bridge->wakeFd = eventfd(0, EFD_CLOEXEC | EFD_NONBLOCK);
  if (bridge->wakeFd < 0)
    throw std::runtime_error("kwinpp: couldn't create an eventfd");

  const std::string &scriptPath = writeScriptFile();

  callKWin("/Scripting", "org.kde.kwin.Scripting", "unloadScript",
           {PLUGIN_NAME});
  int32_t id = -1;
  callKWin("/Scripting", "org.kde.kwin.Scripting", "loadScript",
           {scriptPath, PLUGIN_NAME}, &id);
  if (id < 0)
    throw std::runtime_error("kwinpp: KWin refused to load the script");
  callKWin(("/Scripting/Script" + std::to_string(id)).c_str(),
           "org.kde.kwin.Script", "run");

  // from here on only the bus thread touches the connection
  std::thread([] { bridge->run(); }).detach();

  std::unique_lock lock(bridge->mutex);
  if (!bridge->cv.wait_for(lock, CALL_TIMEOUT, [] { return bridge->ready; }))
    throw std::runtime_error("kwinpp: the KWin script never connected");
}

/* Why start() failed, if it did. Exceptions can't escape a constructor
 * function, so the error is rethrown from the first call instead. */
std::optional<std::string> startError;

/* Runs when the library is loaded, before main(). */
__attribute__((constructor)) void startOnLoad() {
  try {
    start();
  } catch (const std::exception &e) {
    startError = e.what();
  }
}

std::mutex handleMutex;
std::unordered_map<std::string, void *> handles;
std::unordered_map<const void *, std::string> handleRefs;

} // namespace

namespace kwinpp_internal {

void *handle_for_nongeneric(const std::string &ref, void *(*create)()) {
  std::lock_guard lock(handleMutex);
  void *&handle = handles[ref];
  if (!handle) {
    handle = create();
    handleRefs.emplace(handle, ref);
  }
  return handle;
}

std::string ref_of(const void *handle) {
  if (handle == &KWin::workspace)
    return "workspace";
  std::lock_guard lock(handleMutex);
  const auto it = handleRefs.find(handle);
  return it == handleRefs.end() ? std::string() : it->second;
}

void release_handle(const void *handle) noexcept {
  std::string ref;
  {
    std::lock_guard lock(handleMutex);
    const auto it = handleRefs.find(handle);
    if (it == handleRefs.end())
      return; // a copy, or not a handle at all
    ref = std::move(it->second);
    handleRefs.erase(it);
    handles.erase(ref);
  }
  if (startError || !bridge)
    return;
  try {
    const nlohmann::json request{{"release", ref}};
    std::lock_guard lock(bridge->mutex);
    bridge->submit(request.dump());
  } catch (...) {
    // destructors can't throw, and a leaked object in KWin is harmless
  }
}

nlohmann::json call_kwin_func_raw(const std::string &target,
                                  const std::string &func,
                                  std::vector<nlohmann::json> args) {
  if (startError)
    throw std::runtime_error(*startError);

  static std::atomic<int64_t> nextId = 0;
  const int64_t id = nextId++;
  const nlohmann::json request{{"id", id},
                               {"target", target},
                               {"func", func},
                               {"args", std::move(args)}};

  std::unique_lock lock(bridge->mutex);
  bridge->submit(request.dump());
  if (!bridge->cv.wait_for(lock, CALL_TIMEOUT,
                           [id] { return bridge->results.contains(id); }))
    throw std::runtime_error("kwinpp: KWin didn't answer " + func);
#ifdef KWINPP_NO_QT
  nlohmann::json reply = bridge->results.at(id);
#else
  nlohmann::json reply = bridge->results.take(id);
#endif
  if (reply.contains("error")) {
    const nlohmann::json &error = reply["error"];
    throw std::runtime_error(
        "kwinpp: " + func + ": " +
        (error.is_string() ? error.get<std::string>() : error.dump()));
  }
  return reply.contains("value") ? std::move(reply["value"]) : nullptr;
}

} // namespace kwinpp_internal
