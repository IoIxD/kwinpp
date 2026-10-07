#include "kwinpp.hpp"
#include "kwinppi.hpp"

#include <QCoreApplication>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusVirtualObject>
#include <QDir>
#include <QHash>
#include <QJsonDocument>
#include <QQueue>
#include <QTemporaryFile>
#include <QTimerEvent>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <optional>
#include <string>
#include <stdexcept>
#include <thread>

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
 * {id, value} or {id, error} back. KWin objects never leave KWin: they're kept
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

/* The D-Bus end of the script. Lives on kwinpp's application thread (see
 * startApplication) so polls get answered whatever the program is doing. */
class Bridge : public QDBusVirtualObject {
public:
  std::mutex mutex;
  std::condition_variable cv;
  bool ready = false; // the script has polled at least once
  std::optional<QDBusMessage> pendingPoll;
  QQueue<QString> requests;
  QHash<qint64, QJsonObject> results;

  QString introspect(const QString &) const override {
    return QStringLiteral(R"(<interface name="net.ioi_xd.kwinpp">
  <method name="poll"><arg direction="out" type="s"/></method>
  <method name="result"><arg direction="in" type="s"/></method>
</interface>)");
  }

  bool handleMessage(const QDBusMessage &message,
                     const QDBusConnection &connection) override {
    if (message.member() == "poll") {
      std::lock_guard lock(mutex);
      if (pendingPoll)
        connection.send(pendingPoll->createReply(QString()));
      pendingPoll = message;
      ready = true;
      flush();
      cv.notify_all();
      return true;
    }
    if (message.member() == "result" && !message.arguments().isEmpty()) {
      const QJsonObject reply =
          QJsonDocument::fromJson(
              message.arguments().first().toString().toUtf8())
              .object();
      connection.send(message.createReply());
      std::lock_guard lock(mutex);
      results.insert(reply["id"].toInteger(), reply);
      cv.notify_all();
      return true;
    }
    return false;
  }

  /* Hands the next request to a waiting poll. Call with mutex held. */
  void flush() {
    if (!pendingPoll || requests.isEmpty())
      return;
    QDBusConnection::sessionBus().send(
        pendingPoll->createReply(requests.dequeue()));
    pendingPoll.reset();
  }

protected:
  /* KWin gives up on a D-Bus call after ~25s and the script's poll loop dies
   * with it, so answer idle polls before that happens. */
  void timerEvent(QTimerEvent *) override {
    std::lock_guard lock(mutex);
    if (!pendingPoll)
      return;
    QDBusConnection::sessionBus().send(pendingPoll->createReply(QString()));
    pendingPoll.reset();
  }
};

constexpr auto CALL_TIMEOUT = std::chrono::seconds(5);

Bridge *bridge = nullptr;

void callKWin(const QString &path, const QString &interface,
              const QString &method, const QVariantList &args,
              QVariant *result = nullptr) {
  QDBusMessage message =
      QDBusMessage::createMethodCall("org.kde.KWin", path, interface, method);
  message.setArguments(args);
  const QDBusMessage reply = QDBusConnection::sessionBus().call(message);
  if (reply.type() == QDBusMessage::ErrorMessage)
    throw std::runtime_error("kwinpp: " + method.toStdString() + ": " +
                             reply.errorMessage().toStdString());
  if (result && !reply.arguments().isEmpty())
    *result = reply.arguments().first();
}

/* Qt D-Bus only delivers calls while the application thread is in its event
 * loop, and the program's main thread isn't ours to block. So the
 * QCoreApplication is created on, and runs on, a thread of our own. */
void startApplication() {
  std::mutex mutex;
  std::condition_variable cv;
  bool running = false;
  std::thread([&] {
    static int argc = 1;
    static char arg0[] = "kwinpp";
    static char *argv[] = {arg0, nullptr};
    new QCoreApplication(argc, argv);
    bridge = new Bridge();
    bridge->startTimer(10000);
    {
      std::lock_guard lock(mutex);
      running = true;
    }
    cv.notify_all();
    QCoreApplication::exec();
  }).detach();
  std::unique_lock lock(mutex);
  cv.wait(lock, [&] { return running; });
}

void start() {
  startApplication();

  QDBusConnection bus = QDBusConnection::sessionBus();
  if (!bus.registerService(SERVICE))
    throw std::runtime_error("kwinpp: couldn't register " +
                             std::string(SERVICE) + " on the session bus");
  if (!bus.registerVirtualObject(PATH, bridge))
    throw std::runtime_error("kwinpp: couldn't register " + std::string(PATH));

  // KWin reads the file when the script is run, so keep it around
  static QTemporaryFile scriptFile(QDir::tempPath() + "/kwinpp-XXXXXX.js");
  if (!scriptFile.open())
    throw std::runtime_error("kwinpp: couldn't write the KWin script");
  scriptFile.write(KWIN_SCRIPT);
  scriptFile.flush();

  callKWin("/Scripting", "org.kde.kwin.Scripting", "unloadScript",
           {QString(PLUGIN_NAME)});
  QVariant id;
  callKWin("/Scripting", "org.kde.kwin.Scripting", "loadScript",
           {scriptFile.fileName(), QString(PLUGIN_NAME)}, &id);
  if (id.toInt() < 0)
    throw std::runtime_error("kwinpp: KWin refused to load the script");
  callKWin("/Scripting/Script" + QString::number(id.toInt()),
           "org.kde.kwin.Script", "run", {});

  std::unique_lock lock(bridge->mutex);
  if (!bridge->cv.wait_for(lock, CALL_TIMEOUT, [] { return bridge->ready; }))
    throw std::runtime_error("kwinpp: the KWin script never connected");
}

/* Why start() failed, if it did. Exceptions can't escape a constructor
 * function, so the error is rethrown from the first call instead. */
std::optional<std::string> startError;

/* Runs when the library is loaded, before main(). This makes kwinpp own the
 * process's QCoreApplication, so programs using it must not create their own. */
__attribute__((constructor)) void startOnLoad() {
  try {
    start();
  } catch (const std::exception &e) {
    startError = e.what();
  }
}

std::mutex handleMutex;
QHash<QString, void *> handles;
QHash<const void *, QString> handleRefs;

} // namespace

namespace kwinpp_internal {

void *handle_for(const QString &ref, void *(*create)()) {
  std::lock_guard lock(handleMutex);
  void *&handle = handles[ref];
  if (!handle) {
    handle = create();
    handleRefs.insert(handle, ref);
  }
  return handle;
}

QString ref_of(const void *handle) {
  if (handle == &KWin::workspace)
    return "workspace";
  std::lock_guard lock(handleMutex);
  return handleRefs.value(handle);
}

QJsonValue call_kwin_func_raw(const QString &target, const QString &func,
                              const QJsonArray &args) {
  if (startError)
    throw std::runtime_error(*startError);

  static std::atomic<qint64> nextId = 0;
  const qint64 id = nextId++;
  const QJsonObject request{
      {"id", id}, {"target", target}, {"func", func}, {"args", args}};

  std::unique_lock lock(bridge->mutex);
  bridge->requests.enqueue(
      QString::fromUtf8(QJsonDocument(request).toJson(QJsonDocument::Compact)));
  bridge->flush();
  if (!bridge->cv.wait_for(lock, CALL_TIMEOUT,
                           [id] { return bridge->results.contains(id); }))
    throw std::runtime_error("kwinpp: KWin didn't answer " +
                             func.toStdString());
  const QJsonObject reply = bridge->results.take(id);
  if (reply.contains("error"))
    throw std::runtime_error("kwinpp: " + func.toStdString() + ": " +
                             reply["error"].toString().toStdString());
  return reply["value"];
}

} // namespace kwinpp_internal
