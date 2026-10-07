#pragma once

/* translation of the APIs listed on
 * https://develop.kde.org/docs/plasma/kwin/api/#global */

#include <Qt>
#include <QtCore/QtCore>
#include <functional>

#include "kwinppi.hpp"

namespace KWin {

class WorkspaceWrapper;
class VirtualDesktop;
class Output;
class Window;
class TileManager;
class Tile;

class WorkspaceWrapper {
public:
  enum class ClientAreaOption {
    PlacementArea, /* window movement snapping area? ignore struts */
    MovementArea,
    MaximizeArea,
    MaximizeFullArea,
    FullScreenArea,
    WorkArea,
    FullArea,
    ScreenArea,
  };
  enum class ElectricBorder {
    ElectricTop,
    ElectricTopRight,
    ElectricRight,
    ElectricBottomRight,
    ElectricBottom,
    ElectricBottomLeft,
    ElectricLeft,
    ElectricTopLeft,
    ELECTRIC_COUNT,
    ElectricNone,
  };

  const QList<KWin::VirtualDesktop *> desktops() {
    return kwinpp_internal::call_kwin_func<const QList<KWin::VirtualDesktop *>>(
        "workspace", "WorkspaceWrapper.desktops");
  }
  const QSize desktopGridSize() {
    return kwinpp_internal::call_kwin_func<const QSize>(
        "workspace", "WorkspaceWrapper.desktopGridSize");
  }
  const int desktopGridWidth() {
    return kwinpp_internal::call_kwin_func<const int>(
        "workspace", "WorkspaceWrapper.desktopGridWidth");
  }
  const int desktopGridHeight() {
    return kwinpp_internal::call_kwin_func<const int>(
        "workspace", "WorkspaceWrapper.desktopGridHeight");
  }
  const int workspaceWidth() {
    return kwinpp_internal::call_kwin_func<const int>(
        "workspace", "WorkspaceWrapper.workspaceWidth");
  }
  const int workspaceHeight() {
    return kwinpp_internal::call_kwin_func<const int>(
        "workspace", "WorkspaceWrapper.workspaceHeight");
  }
  const QSize workspaceSize() {
    return kwinpp_internal::call_kwin_func<const QSize>(
        "workspace", "WorkspaceWrapper.workspaceSize");
  }
  const KWin::Output *activeScreen() {
    return kwinpp_internal::call_kwin_func<const KWin::Output *>(
        "workspace", "WorkspaceWrapper.activeScreen");
  }
  const QList<KWin::Output *> screens() {
    return kwinpp_internal::call_kwin_func<const QList<KWin::Output *>>(
        "workspace", "WorkspaceWrapper.screens");
  }
  const QStringList activities() {
    return kwinpp_internal::call_kwin_func<const QStringList>(
        "workspace", "WorkspaceWrapper.activities");
  }
  /*The bounding size of all screens combined. Overlapping areas are not counted
   * multiple times. */
  const QSize virtualScreenSize() {
    return kwinpp_internal::call_kwin_func<const QSize>(
        "workspace", "WorkspaceWrapper.virtualScreenSize");
  }
  /*The bounding geometry of all screens combined. Always starts at (0,0) and
   * has virtualScreenSize as it's size. */
  const QRect virtualScreenGeometry() {
    return kwinpp_internal::call_kwin_func<const QRect>(
        "workspace", "WorkspaceWrapper.virtualScreenGeometry");
  }
  /* List of Clients currently managed by KWin, orderd by their visibility
   * (later ones cover earlier ones).*/
  const QList<KWin::Window *> stackingOrder() {
    return kwinpp_internal::call_kwin_func<const QList<KWin::Window *>>(
        "workspace", "WorkspaceWrapper.stackingOrder");
  }

  QPoint cursorPos() {
    return kwinpp_internal::call_kwin_func<QPoint>(
        "workspace", "WorkspaceWrapper.cursorPos");
  } /* The current position of the cursor. */

  /* The current virtual desktop on the active screen. */
  KWin::VirtualDesktop *currentDesktop() {
    return kwinpp_internal::call_kwin_func<KWin::VirtualDesktop *>(
        "workspace", "WorkspaceWrapper.currentDesktop");
  }
  /* Set the current virtual desktop on the active screen. */
  void setCurrentDesktop(KWin::VirtualDesktop *val) {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.setCurrentDesktop", val);
  }

  KWin::Window *activeWindow() {
    return kwinpp_internal::call_kwin_func<KWin::Window *>(
        "workspace", "WorkspaceWrapper.activeWindow");
  }
  void setActiveWindow(KWin::Window *val) {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.setActiveWindow", val);
  }

  QString currentActivity() {
    return kwinpp_internal::call_kwin_func<QString>(
        "workspace", "WorkspaceWrapper.currentActivity");
  }
  void setCurrentActivity(QString val) {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.setCurrentActivity", val);
  }

  void onWindowAdded(std::function<void(KWin::Window *window)> callback);
  void onWindowRemoved(std::function<void(KWin::Window *window)> callback);
  void onWindowActivated(std::function<void(KWin::Window *window)> callback);
  /* This signal is emitted when a virtual desktop is added or removed. */
  void onDesktopsChanged(std::function<void()> callback);
  /* Signal emitted whenever the layout of virtual desktops changed. That is
   * desktopGrid(Size/Width/Height) will have new values. 4.11 */
  void onDesktopLayoutChanged(std::function<void()> callback);
  /* Emitted when the output list changes, e.g. an output is connected or
   * removed. */
  void onScreensChanged(std::function<void()> callback);
  /* Signal emitted whenever the current activity changed. id id of the new
   * activity */
  void
  onCurrentActivityChanged(std::function<void(const QString &id)> callback);
  /* Signal emitted whenever the list of activities changed. id id of the new
   * activity */
  void onActivitiesChanged(std::function<void(const QString &id)> callback);
  /* This signal is emitted when a new activity is added id id of the new
   * activity */
  void onActivityAdded(std::function<void(const QString &id)> callback);
  /* This signal is emitted when the activity is removed id id of the removed
   * activity */
  void onActivityRemoved(std::function<void(const QString &id)> callback);
  /* Emitted whenever the virtualScreenSize changes. virtualScreenSize() 5.0 */
  void onVirtualScreenSizeChanged(std::function<void()> callback);
  /* Emitted whenever the virtualScreenGeometry changes.
   * virtualScreenGeometry() 5.0 */
  void onVirtualScreenGeometryChanged(std::function<void()> callback);
  /* This signal is emitted when the current virtual desktop changes. */
  void onCurrentDesktopChanged(
      std::function<void(KWin::VirtualDesktop *previous,
                         KWin::VirtualDesktop *current, KWin::Output *output)>
          callback);
  /* This signal is emitted when the cursor position changes. cursorPos() */
  void onCursorPosChanged(std::function<void()> callback);

  void slotSwitchDesktopNext() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotSwitchDesktopNext");
  }
  void slotSwitchDesktopPrevious() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotSwitchDesktopPrevious");
  }
  void slotSwitchDesktopRight() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotSwitchDesktopRight");
  }
  void slotSwitchDesktopLeft() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotSwitchDesktopLeft");
  }
  void slotSwitchDesktopUp() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotSwitchDesktopUp");
  }
  void slotSwitchDesktopDown() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotSwitchDesktopDown");
  }
  void slotSwitchToNextScreen() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotSwitchToNextScreen");
  }
  void slotSwitchToPrevScreen() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotSwitchToPrevScreen");
  }
  void slotSwitchToRightScreen() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotSwitchToRightScreen");
  }
  void slotSwitchToLeftScreen() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotSwitchToLeftScreen");
  }
  void slotSwitchToAboveScreen() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotSwitchToAboveScreen");
  }
  void slotSwitchToBelowScreen() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotSwitchToBelowScreen");
  }
  void slotWindowToNextScreen() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowToNextScreen");
  }
  void slotWindowToPrevScreen() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowToPrevScreen");
  }
  void slotWindowToRightScreen() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowToRightScreen");
  }
  void slotWindowToLeftScreen() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowToLeftScreen");
  }
  void slotWindowToAboveScreen() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowToAboveScreen");
  }
  void slotWindowToBelowScreen() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowToBelowScreen");
  }
  void slotToggleShowDesktop() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotToggleShowDesktop");
  }
  void slotWindowMaximize() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowMaximize");
  }
  void slotWindowMaximizeVertical() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowMaximizeVertical");
  }
  void slotWindowMaximizeHorizontal() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowMaximizeHorizontal");
  }
  void slotWindowMinimize() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowMinimize");
  }
  void slotWindowShade() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowShade");
  }
  void slotWindowRaise() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowRaise");
  }
  void slotWindowLower() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowLower");
  }
  void slotWindowRaiseOrLower() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowRaiseOrLower");
  }
  void slotActivateAttentionWindow() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotActivateAttentionWindow");
  }
  void slotWindowMoveLeft() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowMoveLeft");
  }
  void slotWindowMoveRight() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowMoveRight");
  }
  void slotWindowMoveUp() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowMoveUp");
  }
  void slotWindowMoveDown() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowMoveDown");
  }
  void slotWindowExpandHorizontal() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowExpandHorizontal");
  }
  void slotWindowExpandVertical() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowExpandVertical");
  }
  void slotWindowShrinkHorizontal() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowShrinkHorizontal");
  }
  void slotWindowShrinkVertical() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowShrinkVertical");
  }
  void slotWindowQuickTileLeft() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowQuickTileLeft");
  }
  void slotWindowQuickTileRight() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowQuickTileRight");
  }
  void slotWindowQuickTileTop() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowQuickTileTop");
  }
  void slotWindowQuickTileBottom() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowQuickTileBottom");
  }
  void slotWindowQuickTileTopLeft() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowQuickTileTopLeft");
  }
  void slotWindowQuickTileTopRight() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowQuickTileTopRight");
  }
  void slotWindowQuickTileBottomLeft() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowQuickTileBottomLeft");
  }
  void slotWindowQuickTileBottomRight() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowQuickTileBottomRight");
  }
  void slotSwitchWindowUp() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotSwitchWindowUp");
  }
  void slotSwitchWindowDown() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotSwitchWindowDown");
  }
  void slotSwitchWindowRight() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotSwitchWindowRight");
  }
  void slotSwitchWindowLeft() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotSwitchWindowLeft");
  }
  void slotIncreaseWindowOpacity() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotIncreaseWindowOpacity");
  }
  void slotLowerWindowOpacity() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotLowerWindowOpacity");
  }
  void slotWindowOperations() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowOperations");
  }
  void slotWindowClose() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowClose");
  }
  void slotWindowMove() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowMove");
  }
  void slotWindowResize() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowResize");
  }
  void slotWindowAbove() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowAbove");
  }
  void slotWindowBelow() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowBelow");
  }
  void slotWindowOnAllDesktops() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowOnAllDesktops");
  }
  void slotWindowFullScreen() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowFullScreen");
  }
  void slotWindowNoBorder() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowNoBorder");
  }
  void slotWindowToNextDesktop() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowToNextDesktop");
  }
  void slotWindowToPreviousDesktop() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowToPreviousDesktop");
  }
  void slotWindowToDesktopRight() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowToDesktopRight");
  }
  void slotWindowToDesktopLeft() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowToDesktopLeft");
  }
  void slotWindowToDesktopUp() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowToDesktopUp");
  }
  void slotWindowToDesktopDown() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowToDesktopDown");
  }
  /* Sends the Window to the given output.*/
  void sendClientToScreen(KWin::Window *client, KWin::Output *output) {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.sendClientToScreen", client, output);
  }
  /* Shows an outline at the specified geometry. If an outline is already shown
   * the outline is moved to the new position. Use hideOutline to remove the
   * outline again. */
  void showOutline(const QRect &geometry) {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.showOutline", geometry);
  }
  /* Overloaded method for convenience.*/
  void showOutline(int x, int y, int width, int height) {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.showOutline", x, y, width, height);
  }
  /* Hides the outline previously shown by showOutline.*/
  void hideOutline() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.hideOutline");
  }
  /* Returns the current desktop on the given screen. */
  KWin::VirtualDesktop *currentDesktopForScreen(KWin::Output *output) const {
    return kwinpp_internal::call_kwin_func<KWin::VirtualDesktop *>(
        "workspace", "WorkspaceWrapper.currentDesktopForScreen", output);
  }
  /* Sets the current desktop on the given screen.*/
  void setCurrentDesktopForScreen(KWin::VirtualDesktop *desktop,
                                  KWin::Output *output) {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.setCurrentDesktopForScreen", desktop,
        output);
  }
  KWin::Output *screenAt(const QPointF &pos) const {
    return kwinpp_internal::call_kwin_func<KWin::Output *>(
        "workspace", "WorkspaceWrapper.screenAt", pos);
  }
  KWin::TileManager *tilingForScreen(const QString &screenName) const {
    return kwinpp_internal::call_kwin_func<KWin::TileManager *>(
        "workspace", "WorkspaceWrapper.tilingForScreen", screenName);
  }
  KWin::TileManager *tilingForScreen(KWin::Output *output) const {
    return kwinpp_internal::call_kwin_func<KWin::TileManager *>(
        "workspace", "WorkspaceWrapper.tilingForScreen", output);
  }
  /* Returns the geometry a Client can use with the specified option. This
   * method should be preferred over other methods providing screen sizes as the
   * various options take constraints such as struts set on panels into account.
   * This method is also multi screen aware, but there are also options to get
   * full areas.
   *
   * `option` The type of area which should be considered
   *
   * `screen` The screen for which the area should be considered
   *
   * `desktop` The desktop for which the area should be considered, in general
   * there should not be a difference
   *
   * Returns: The specified screen geometry
   * */
  QRectF clientArea(ClientAreaOption option, KWin::Output *output,
                    KWin::VirtualDesktop *desktop) const {
    return kwinpp_internal::call_kwin_func<QRectF>(
        "workspace", "WorkspaceWrapper.clientArea", option, output, desktop);
  }
  /* Overloaded method for convenience. client The Client for which the area
   * should be retrieved The specified screen geometry */
  QRectF clientArea(ClientAreaOption option, KWin::Window *client) const {
    return kwinpp_internal::call_kwin_func<QRectF>(
        "workspace", "WorkspaceWrapper.clientArea", option, client);
  }
  QRectF clientArea(ClientAreaOption option, const KWin::Window *client) const {
    return kwinpp_internal::call_kwin_func<QRectF>(
        "workspace", "WorkspaceWrapper.clientArea", option, client);
  }

  /* Create a new virtual desktop at the requested position. position The
   * position of the desktop. It should be in range [0, count]. name The name
   * for the new desktop, if empty the default name will be used. */
  void createDesktop(int position, const QString &name) const {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.createDesktop", position, name);
  }
  /* Removes the specified virtual desktop. */
  void removeDesktop(KWin::VirtualDesktop *desktop) {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.removeDesktop", desktop);
  }
  /* Provides support information about the currently running KWin instance. */
  QString supportInformation() const {
    return kwinpp_internal::call_kwin_func<QString>(
        "workspace", "WorkspaceWrapper.supportInformation");
  }
  /* Raises a Window above all others on the screen.
   *
   * `window` The Window to raise */
  void raiseWindow(KWin::Window *window) {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.raiseWindow", window);
  }
  /* Finds the Client with the given windowId. windowId The window Id of the
   * Client The found Client or null */
  KWin::Window *getClient(qulonglong windowId) {
    return kwinpp_internal::call_kwin_func<KWin::Window *>(
        "workspace", "WorkspaceWrapper.getClient", windowId);
  }
  /* Finds up to count windows at a particular location, prioritizing the
   * topmost one first. A negative count returns all matching clients.
   * `pos`: The location to look for
   *
   * `count`: The number of clients to return
   *
   * Returns: A list of Client objects 6.0*/
  QList<KWin::Window *> windowAt(const QPointF &pos, int count = 1) const {
    return kwinpp_internal::call_kwin_func<QList<KWin::Window *>>(
        "workspace", "WorkspaceWrapper.windowAt", pos, count);
  }

  /* Checks if a specific effect is currently active.
   *
   * `pluginId`: The plugin Id of the effect to check.
   *
   * Returns: true if the effect isloaded and currently active, false
   * otherwise.*/
  bool isEffectActive(const QString &pluginId) const {
    return kwinpp_internal::call_kwin_func<bool>(
        "workspace", "WorkspaceWrapper.isEffectActive", pluginId);
  }
};

extern WorkspaceWrapper workspace;

class VirtualDesktop {
public:
  ~VirtualDesktop() { kwinpp_internal::release_handle(this); }

  const QString id() {
    return kwinpp_internal::call_kwin_func<const QString>(
        kwinpp_internal::ref_of(this), "VirtualDesktop.id");
  }
  const uint x11DesktopNumber() {
    return kwinpp_internal::call_kwin_func<const uint>(
        kwinpp_internal::ref_of(this), "VirtualDesktop.x11DesktopNumber");
  }

  QString name() {
    return kwinpp_internal::call_kwin_func<QString>(
        kwinpp_internal::ref_of(this), "VirtualDesktop.name");
  }
  void setName(QString val) {
    return kwinpp_internal::call_kwin_func<void>(kwinpp_internal::ref_of(this),
                                                 "VirtualDesktop.setName", val);
  }

  void onNameChanged(std::function<void> callback);
  void onX11DesktopNumberChanged(std::function<void> callback);
  /* Emitted just before the desktop gets destroyed. */
  void onAboutToBeDestroyed(std::function<void> callback);
};

class Output {
public:
  ~Output() { kwinpp_internal::release_handle(this); }

  enum class DpmsMode {
    On,
    Standby,
    Suspend,
    Off,
  };
  enum class Capability {
    Dpms,
    Overscan,
    Vrr,
    RgbRange,
    HighDynamicRange,
    WideColorGamut,
    AutoRotation,
    IccProfile,
    Tearing,
  };
  enum class SubPixel {
    Unknown,
    None,
    Horizontal_RGB,
    Horizontal_BGR,
    Vertical_RGB,
    Vertical_BGR,
  };
  enum class RgbRange {
    Automatic,
    Full,
    Limited,
  };
  enum class AutoRotationPolicy {
    Never,
    InTabletMode,
    Always,
  };

  const QRect geometry() {
    return kwinpp_internal::call_kwin_func<const QRect>(
        kwinpp_internal::ref_of(this), "Output.geometry");
  }
  const qreal devicePixelRatio() {
    return kwinpp_internal::call_kwin_func<const qreal>(
        kwinpp_internal::ref_of(this), "Output.devicePixelRatio");
  }
  const QString name() {
    return kwinpp_internal::call_kwin_func<const QString>(
        kwinpp_internal::ref_of(this), "Output.name");
  }
  const QString manufacturer() {
    return kwinpp_internal::call_kwin_func<const QString>(
        kwinpp_internal::ref_of(this), "Output.manufacturer");
  }
  const QString model() {
    return kwinpp_internal::call_kwin_func<const QString>(
        kwinpp_internal::ref_of(this), "Output.model");
  }
  const QString serialNumber() {
    return kwinpp_internal::call_kwin_func<const QString>(
        kwinpp_internal::ref_of(this), "Output.serialNumber");
  }

  /* This signal is emitted when the geometry of this output has changed. */
  void onGeometryChanged(std::function<void>);
  /* This signal is emitted when the output has been enabled or disabled. */
  void onEnabledChanged(std::function<void>);
  /* This signal is emitted when the device pixel ratio of the output has
   * changed. */
  void onScaleChanged(std::function<void>);
  /* Notifies that the display will be dimmed in time ms. This allows effects to
   * plan for it and hopefully animate it */
  void onAboutToTurnOff(std::function<void(std::chrono::milliseconds time)>);
  /* Notifies that the output has been turned on and the wake can be decorated.
   */
  void onWakeUp(std::function<void>);

  /* Notifies that the output is about to change configuration based on a user
   * interaction. Be it because it gets a transformation or moved around. Only
   * to be used for effects */
  // undocumented/C++ scripting only type
  // void onAboutToChange(std::function<void(OutputChangeSet *changeSet)>);

  /* Notifies that the output changed based on a user interaction. Be it because
   * it gets a transformation or moved around. Only to be used for effects */
  void onChanged(std::function<void>);
  void onCurrentModeChanged(std::function<void>);
  void onModesChanged(std::function<void>);
  void onOutputChange(std::function<void(const QRegion &damagedRegion)>);
  void onTransformChanged(std::function<void>);
  void onDpmsModeChanged(std::function<void>);
  void onCapabilitiesChanged(std::function<void>);
  void onOverscanChanged(std::function<void>);
  void onVrrPolicyChanged(std::function<void>);
  void onRgbRangeChanged(std::function<void>);
  void onWideColorGamutChanged(std::function<void>);
  void onSdrBrightnessChanged(std::function<void>);
  void onHighDynamicRangeChanged(std::function<void>);
  void onAutoRotationPolicyChanged(std::function<void>);
  void onIccProfileChanged(std::function<void>);
  void onIccProfilePathChanged(std::function<void>);
  void onBrightnessMetadataChanged(std::function<void>);
  void onSdrGamutWidenessChanged(std::function<void>);
  void onColorDescriptionChanged(std::function<void>);

  QPointF mapToGlobal(const QPointF &pos) const {
    return kwinpp_internal::call_kwin_func<QPointF>(
        kwinpp_internal::ref_of(this), "Output.mapToGlobal", pos);
  }
  QPointF mapFromGlobal(const QPointF &pos) const {
    return kwinpp_internal::call_kwin_func<QPointF>(
        kwinpp_internal::ref_of(this), "Output.mapFromGlobal", pos);
  }
};
class Window {
public:
  ~Window() { kwinpp_internal::release_handle(this); }

  enum class SizeMode {
    SizeModeAny,
    SizeModeFixedW,
    SizeModeFixedH,
    SizeModeMax,
  };

  enum class SameApplicationCheck {
    RelaxedForActive,
    AllowCrossProcesses,
  };

  /* This property holds rectangle that the pixmap or buffer of this Window
   * occupies on the screen. This rectangle includes invisible portions of the
   * window, e.g. client-side drop shadows, etc. */
  QRectF bufferGeometry() const {
    return kwinpp_internal::call_kwin_func<QRectF>(
        kwinpp_internal::ref_of(this), "Window.bufferGeometry");
  }
  /* The geometry of the Window without frame borders. */
  QRectF clientGeometry() const {
    return kwinpp_internal::call_kwin_func<QRectF>(
        kwinpp_internal::ref_of(this), "Window.clientGeometry");
  }
  /* This property holds the position of the Window's frame geometry. */
  QPointF pos() const {
    return kwinpp_internal::call_kwin_func<QPointF>(
        kwinpp_internal::ref_of(this), "Window.pos");
  }
  /* This property holds the size of the Window's frame geometry. */
  QSizeF size() const {
    return kwinpp_internal::call_kwin_func<QSizeF>(
        kwinpp_internal::ref_of(this), "Window.size");
  }
  /* This property holds the x position of the Window's frame geometry. */
  qreal x() const {
    return kwinpp_internal::call_kwin_func<qreal>(kwinpp_internal::ref_of(this),
                                                  "Window.x");
  }
  /* This property holds the y position of the Window's frame geometry. */
  qreal y() const {
    return kwinpp_internal::call_kwin_func<qreal>(kwinpp_internal::ref_of(this),
                                                  "Window.y");
  }
  /* This property holds the width of the Window's frame geometry. */
  qreal width() const {
    return kwinpp_internal::call_kwin_func<qreal>(kwinpp_internal::ref_of(this),
                                                  "Window.width");
  }
  /* This property holds the height of the Window's frame geometry. */
  qreal height() const {
    return kwinpp_internal::call_kwin_func<qreal>(kwinpp_internal::ref_of(this),
                                                  "Window.height");
  }
  /* The output where the window center is on */
  KWin::Output *output() const {
    return kwinpp_internal::call_kwin_func<KWin::Output *>(
        kwinpp_internal::ref_of(this), "Window.output");
  }
  QRectF rect() const {
    return kwinpp_internal::call_kwin_func<QRectF>(
        kwinpp_internal::ref_of(this), "Window.rect");
  }
  QString resourceName() const {
    return kwinpp_internal::call_kwin_func<QString>(
        kwinpp_internal::ref_of(this), "Window.resourceName");
  }
  QString resourceClass() const {
    return kwinpp_internal::call_kwin_func<QString>(
        kwinpp_internal::ref_of(this), "Window.resourceClass");
  }
  QString windowRole() const {
    return kwinpp_internal::call_kwin_func<QString>(
        kwinpp_internal::ref_of(this), "Window.windowRole");
  }
  /* Returns whether the window is a desktop background window (the one with
   * wallpaper). See _NET_WM_WINDOW_TYPE_DESKTOP at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  bool desktopWindow() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.desktopWindow");
  }
  /* Returns whether the window is a dock (i.e. a panel). See
   * _NET_WM_WINDOW_TYPE_DOCK at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  bool dock() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.dock");
  }
  /* Returns whether the window is a standalone (detached) toolbar window. See
   * _NET_WM_WINDOW_TYPE_TOOLBAR at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  bool toolbar() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.toolbar");
  }
  /* Returns whether the window is a torn-off menu. See _NET_WM_WINDOW_TYPE_MENU
   * at https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  bool menu() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.menu");
  }
  /* Returns whether the window is a "normal" window, i.e. an application or any
   * other window for which none of the specialized window types fit. See
   * _NET_WM_WINDOW_TYPE_NORMAL at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  bool normalWindow() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.normalWindow");
  }
  /* Returns whether the window is a dialog window. See
   * _NET_WM_WINDOW_TYPE_DIALOG at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  bool dialog() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.dialog");
  }
  /* Returns whether the window is a splashscreen. Note that many (especially
   * older) applications do not support marking their splash windows with this
   * type. See _NET_WM_WINDOW_TYPE_SPLASH at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  bool splash() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.splash");
  }
  /* Returns whether the window is a utility window, such as a tool window. See
   * _NET_WM_WINDOW_TYPE_UTILITY at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  bool utility() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.utility");
  }
  /* Returns whether the window is a dropdown menu (i.e. a popup directly or
   * indirectly open from the applications menubar). See
   * _NET_WM_WINDOW_TYPE_DROPDOWN_MENU at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  bool dropdownMenu() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.dropdownMenu");
  }
  /* Returns whether the window is a popup menu (that is not a torn-off or
   * dropdown menu). See _NET_WM_WINDOW_TYPE_POPUP_MENU at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  bool popupMenu() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.popupMenu");
  }
  /* Returns whether the window is a tooltip. See _NET_WM_WINDOW_TYPE_TOOLTIP at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  bool tooltip() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.tooltip");
  }
  /* Returns whether the window is a window with a notification. See
   * _NET_WM_WINDOW_TYPE_NOTIFICATION at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  bool notification() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.notification");
  }
  /* Returns whether the window is a window with a critical notification. */
  bool criticalNotification() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.criticalNotification");
  }
  /* Returns whether the window is an applet popup. */
  bool appletPopup() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.appletPopup");
  }
  /* Returns whether the window is an On Screen Display. */
  bool onScreenDisplay() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.onScreenDisplay");
  }
  /* Returns whether the window is a combobox popup. See
   * _NET_WM_WINDOW_TYPE_COMBO at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  bool comboBox() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.comboBox");
  }
  /* Returns whether the window is a Drag&Drop icon. See _NET_WM_WINDOW_TYPE_DND
   * at https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  bool dndIcon() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.dndIcon");
  }
  /* Returns the NETWM window type See
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  int windowType() const {
    return kwinpp_internal::call_kwin_func<int>(kwinpp_internal::ref_of(this),
                                                "Window.windowType");
  }
  /* Whether this Window is managed by KWin (it has control over its placement
   * and other aspects, as opposed to override-redirect windows that are
   * entirely handled by the application). */
  bool managed() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.managed");
  }
  /* Whether this Window represents an already deleted window and only kept for
   * the compositor for animations. */
  bool deleted() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.deleted");
  }
  /* Whether the window is a popup. */
  bool popupWindow() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.popupWindow");
  }
  /* Whether this Window represents the outline. It's always false if
   * compositing is turned off. */
  bool outline() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.outline");
  }
  /* This property holds a UUID to uniquely identify this Window. */
  QUuid internalId() const {
    return kwinpp_internal::call_kwin_func<QUuid>(kwinpp_internal::ref_of(this),
                                                  "Window.internalId");
  }
  /* The pid of the process owning this window. 5.20 */
  int pid() const {
    return kwinpp_internal::call_kwin_func<int>(kwinpp_internal::ref_of(this),
                                                "Window.pid");
  }
  /* The position of this window within Workspace's window stack. */
  int stackingOrder() const {
    return kwinpp_internal::call_kwin_func<int>(kwinpp_internal::ref_of(this),
                                                "Window.stackingOrder");
  }
  /* Whether the Window can be set to fullScreen. The property is evaluated each
   * time it is invoked. Because of that there is no notify signal. */
  bool fullScreenable() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.fullScreenable");
  }
  /* Whether this Window is active or not. Use Workspace::activateWindow() to
   * activate a Window. Workspace::activateWindow */
  bool active() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.active");
  }
  /* Whether the window can be closed by the user. */
  bool closeable() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.closeable");
  }
  QIcon icon() const {
    return kwinpp_internal::call_kwin_func<QIcon>(kwinpp_internal::ref_of(this),
                                                  "Window.icon");
  }
  /* Whether the Window can be shaded. The property is evaluated each time it is
   * invoked. Because of that there is no notify signal. */
  bool shadeable() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.shadeable");
  }
  /* Whether the Window can be minimized. The property is evaluated each time it
   * is invoked. Because of that there is no notify signal. */
  bool minimizable() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.minimizable");
  }
  /* The optional geometry representing the minimized Window in e.g a taskbar.
   * See _NET_WM_ICON_GEOMETRY at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . The value
   * is evaluated each time the getter is called. Because of that no changed
   * signal is provided. */
  QRectF iconGeometry() const {
    return kwinpp_internal::call_kwin_func<QRectF>(
        kwinpp_internal::ref_of(this), "Window.iconGeometry");
  }
  /* Returns whether the window is any of special windows types (desktop, dock,
   * splash, ...), i.e. window types that usually don't have a window frame and
   * the user does not use window management (moving, raising,...) on them. The
   * value is evaluated each time the getter is called. Because of that no
   * changed signal is provided. */
  bool specialWindow() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.specialWindow");
  }
  /* The Caption of the Window. Read from WM_NAME property together with a
   * suffix for hostname and shortcut. To read only the caption as provided by
   * WM_NAME, use the getter with an additional false value. */
  QString caption() const {
    return kwinpp_internal::call_kwin_func<QString>(
        kwinpp_internal::ref_of(this), "Window.caption");
  }
  /* Minimum size as specified in WM_NORMAL_HINTS */
  QSizeF minSize() const {
    return kwinpp_internal::call_kwin_func<QSizeF>(
        kwinpp_internal::ref_of(this), "Window.minSize");
  }
  /* Maximum size as specified in WM_NORMAL_HINTS */
  QSizeF maxSize() const {
    return kwinpp_internal::call_kwin_func<QSizeF>(
        kwinpp_internal::ref_of(this), "Window.maxSize");
  }
  /* Whether the Window can accept keyboard focus. The value is evaluated each
   * time the getter is called. Because of that no changed signal is provided.
   */
  bool wantsInput() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.wantsInput");
  }
  /* Whether the Window is a transient Window to another Window. transientFor */
  bool transient() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.transient");
  }
  /* The Window to which this Window is a transient if any. */
  KWin::Window *transientFor() const {
    return kwinpp_internal::call_kwin_func<KWin::Window *>(
        kwinpp_internal::ref_of(this), "Window.transientFor");
  }
  /* Whether the Window represents a modal window. */
  bool modal() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.modal");
  }
  /* Whether the Window is currently being moved by the user. Notify signal is
   * emitted when the Window starts or ends move/resize mode. */
  bool move() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.move");
  }
  /* Whether the Window is currently being resized by the user. Notify signal is
   * emitted when the Window starts or ends move/resize mode. */
  bool resize() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.resize");
  }
  /* Whether the decoration is currently using an alpha channel. */
  bool decorationHasAlpha() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.decorationHasAlpha");
  }
  /* Whether the Window provides context help. Mostly needed by decorations to
   * decide whether to show the help button or not. */
  bool providesContextHelp() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.providesContextHelp");
  }
  /* Whether the Window can be maximized both horizontally and vertically. The
   * property is evaluated each time it is invoked. Because of that there is no
   * notify signal. */
  bool maximizable() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.maximizable");
  }
  /* Whether the Window is movable. Even if it is not movable, it might be
   * possible to move it to another screen. The property is evaluated each time
   * it is invoked. Because of that there is no notify signal.
   * moveableAcrossScreens */
  bool moveable() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.moveable");
  }
  /* Whether the Window can be moved to another screen. The property is
   * evaluated each time it is invoked. Because of that there is no notify
   * signal. moveable */
  bool moveableAcrossScreens() const {
    return kwinpp_internal::call_kwin_func<bool>(
        kwinpp_internal::ref_of(this), "Window.moveableAcrossScreens");
  }
  /* Whether the Window can be resized. The property is evaluated each time it
   * is invoked. Because of that there is no notify signal. */
  bool resizeable() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.resizeable");
  }
  /* The desktop file name of the application this Window belongs to. This is
   * either the base name without full path and without file extension of the
   * desktop file for the window's application (e.g. "org.kde.foo"). The
   * application's desktop file name can also be the full path to the desktop
   * file (e.g. "/opt/kde/share/org.kde.foo.desktop") in case it's not in a
   * standard location. */
  QString desktopFileName() const {
    return kwinpp_internal::call_kwin_func<QString>(
        kwinpp_internal::ref_of(this), "Window.desktopFileName");
  }
  /* Whether an application menu is available for this Window */
  bool hasApplicationMenu() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.hasApplicationMenu");
  }
  /* Whether the application menu for this Window is currently opened */
  bool applicationMenuActive() const {
    return kwinpp_internal::call_kwin_func<bool>(
        kwinpp_internal::ref_of(this), "Window.applicationMenuActive");
  }
  /* Whether this window is unresponsive. When an application failed to react on
   * a ping request in time, it is considered unresponsive. This usually
   * indicates that the application froze or crashed. */
  bool unresponsive() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.unresponsive");
  }
  /* The color scheme set on this window Absolute file path, or name of palette
   * in the user's config directory following KColorSchemes format. An empty
   * string indicates the default palette from kdeglobals is used. this
   * indicates the colour scheme requested, which might differ from the theme
   * applied if the colorScheme cannot be found */
  QString colorScheme() const {
    return kwinpp_internal::call_kwin_func<QString>(
        kwinpp_internal::ref_of(this), "Window.colorScheme");
  }

  // undocumented/C++ scripting only type
  // KWin::Layer layer() const;

  /* Whether this window is hidden. It's usually the case with auto-hide panels.
   */
  bool hidden() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.hidden");
  }
  /* Returns whether this window is a input method window. This is only used for
   * Wayland. */
  bool inputMethod() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.inputMethod");
  }

  qreal opacity() {
    return kwinpp_internal::call_kwin_func<qreal>(kwinpp_internal::ref_of(this),
                                                  "Window.opacity");
  }
  void setOpacity(qreal value) {
    return kwinpp_internal::call_kwin_func<void>(kwinpp_internal::ref_of(this),
                                                 "Window.setOpacity", value);
  }
  /* Whether the window does not want to be animated on window close. There are
   * legit reasons for this like a screenshot application which does not want
   * it's window being captured. */
  bool skipsCloseAnimation() {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.skipsCloseAnimation");
  }
  void setSkipsCloseAnimation(bool value) {
    return kwinpp_internal::call_kwin_func<void>(
        kwinpp_internal::ref_of(this), "Window.setSkipsCloseAnimation", value);
  }
  /* Whether this Window is fullScreen. A Window might either be fullScreen due
   * to the _NET_WM property or through a legacy support hack. The fullScreen
   * state can only be changed if the Window does not use the legacy hack. To be
   * sure whether the state changed, connect to the notify signal. */
  bool fullScreen() {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.fullScreen");
  }
  void setFullScreen(bool value) {
    return kwinpp_internal::call_kwin_func<void>(kwinpp_internal::ref_of(this),
                                                 "Window.setFullScreen", value);
  }
  /* The virtual desktops this client is on. If it's on all desktops, the list
   * is empty. */
  QList<KWin::VirtualDesktop *> desktops() {
    return kwinpp_internal::call_kwin_func<QList<KWin::VirtualDesktop *>>(
        kwinpp_internal::ref_of(this), "Window.desktops");
  }
  void setDesktops(QList<KWin::VirtualDesktop *> value) {
    return kwinpp_internal::call_kwin_func<void>(kwinpp_internal::ref_of(this),
                                                 "Window.setDesktops", value);
  }
  /* Whether the Window is on all desktops. That is desktop is -1. */
  bool onAllDesktops() {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.onAllDesktops");
  }
  void setOnAllDesktops(bool value) {
    return kwinpp_internal::call_kwin_func<void>(
        kwinpp_internal::ref_of(this), "Window.setOnAllDesktops", value);
  }
  /* The activities this client is on. If it's on all activities the property is
   * empty. */
  QStringList activities() {
    return kwinpp_internal::call_kwin_func<QStringList>(
        kwinpp_internal::ref_of(this), "Window.activities");
  }
  void setActivities(QStringList value) {
    return kwinpp_internal::call_kwin_func<void>(kwinpp_internal::ref_of(this),
                                                 "Window.setActivities", value);
  }
  /* Indicates that the window should not be included on a taskbar. */
  bool skipTaskbar() {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.skipTaskbar");
  }
  void setSkipTaskbar(bool value) {
    return kwinpp_internal::call_kwin_func<void>(
        kwinpp_internal::ref_of(this), "Window.setSkipTaskbar", value);
  }
  /* Indicates that the window should not be included on a Pager. */
  bool skipPager() {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.skipPager");
  }
  void setSkipPager(bool value) {
    return kwinpp_internal::call_kwin_func<void>(kwinpp_internal::ref_of(this),
                                                 "Window.setSkipPager", value);
  }
  /* Whether the Window should be excluded from window switching effects. */
  bool skipSwitcher() {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.skipSwitcher");
  }
  void setSkipSwitcher(bool value) {
    return kwinpp_internal::call_kwin_func<void>(
        kwinpp_internal::ref_of(this), "Window.setSkipSwitcher", value);
  }
  /* Whether the Window is set to be kept above other windows. */
  bool keepAbove() {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.keepAbove");
  }
  void setKeepAbove(bool value) {
    return kwinpp_internal::call_kwin_func<void>(kwinpp_internal::ref_of(this),
                                                 "Window.setKeepAbove", value);
  }
  /* Whether the Window is set to be kept below other windows. */
  bool keepBelow() {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.keepBelow");
  }
  void setKeepBelow(bool value) {
    return kwinpp_internal::call_kwin_func<void>(kwinpp_internal::ref_of(this),
                                                 "Window.setKeepBelow", value);
  }
  /* Whether the Window is shaded. */
  bool shade() {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.shade");
  }
  void setShade(bool value) {
    return kwinpp_internal::call_kwin_func<void>(kwinpp_internal::ref_of(this),
                                                 "Window.setShade", value);
  }
  /* Whether the Window is minimized. */
  bool minimized() {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.minimized");
  }
  void setMinimized(bool value) {
    return kwinpp_internal::call_kwin_func<void>(kwinpp_internal::ref_of(this),
                                                 "Window.setMinimized", value);
  }
  /* Whether window state _NET_WM_STATE_DEMANDS_ATTENTION is set. This state
   * indicates that some action in or with the window happened. For example, it
   * may be set by the Window Manager if the window requested activation but the
   * Window Manager refused it, or the application may set it if it finished
   * some work. This state may be set by both the Window and the Window Manager.
   * It should be unset by the Window Manager when it decides the window got the
   * required attention (usually, that it got activated). */
  bool demandsAttention() {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.demandsAttention");
  }
  void setDemandsAttention(bool value) {
    return kwinpp_internal::call_kwin_func<void>(
        kwinpp_internal::ref_of(this), "Window.setDemandsAttention", value);
  }
  /* The geometry of this Window. Be aware that depending on resize mode the
   * frameGeometryChanged signal might be emitted at each resize step or only at
   * the end of the resize operation. */
  QRectF frameGeometry() {
    return kwinpp_internal::call_kwin_func<QRectF>(
        kwinpp_internal::ref_of(this), "Window.frameGeometry");
  }
  void setFrameGeometry(QRectF value) {
    return kwinpp_internal::call_kwin_func<void>(
        kwinpp_internal::ref_of(this), "Window.setFrameGeometry", value);
  }
  /* Whether the window has a decoration or not. This property is not allowed to
   * be set by applications themselves. The decision whether a window has a
   * border or not belongs to the window manager. If this property gets abused
   * by application developers, it will be removed again. */
  bool noBorder() {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.noBorder");
  }
  void setNoBorder(bool value) {
    return kwinpp_internal::call_kwin_func<void>(kwinpp_internal::ref_of(this),
                                                 "Window.setNoBorder", value);
  }
  /* The Tile this window is associated to, if any */
  KWin::Tile *tile() {
    return kwinpp_internal::call_kwin_func<KWin::Tile *>(
        kwinpp_internal::ref_of(this), "Window.tile");
  }
  void setTile(KWin::Tile *value) {
    return kwinpp_internal::call_kwin_func<void>(kwinpp_internal::ref_of(this),
                                                 "Window.setTile", value);
  }

  void onStackingOrderChanged(std::function<void()> callback);
  void onShadeChanged(std::function<void()> callback);
  void onOpacityChanged(
      std::function<void(KWin::Window *window, qreal oldOpacity)> callback);
  void onDamaged(std::function<void(KWin::Window *window)> callback);
  void onInputTransformationChanged(std::function<void()> callback);
  void onClosed(std::function<void()> callback);
  void onWindowShown(std::function<void(KWin::Window *window)> callback);
  void onWindowHidden(std::function<void(KWin::Window *window)> callback);
  /* Emitted whenever the Window's screen changes. This can happen either in
   * consequence to a screen being removed/added or if the Window's geometry
   * changes. */
  void onOutputChanged(std::function<void()> callback);
  void onSkipCloseAnimationChanged(std::function<void()> callback);
  /* Emitted whenever the window role of the window changes. */
  void onWindowRoleChanged(std::function<void()> callback);
  /* Emitted whenever the window class name or resource name of the window
   * changes.  */
  void onWindowClassChanged(std::function<void()> callback);
  /* Emitted whenever the Surface for this Window changes. */
  void onSurfaceChanged(std::function<void()> callback);
  /* Emitted whenever the window's shadow changes. */
  void onShadowChanged(std::function<void()> callback);
  /* This signal is emitted when the Window's buffer geometry changes. */
  void onBufferGeometryChanged(
      std::function<void(const QRectF &oldGeometry)> callback);
  /* This signal is emitted when the Window's frame geometry changes. */
  void onFrameGeometryChanged(
      std::function<void(const QRectF &oldGeometry)> callback);
  /* This signal is emitted when the Window's client geometry has changed. */
  void onClientGeometryChanged(
      std::function<void(const QRectF &oldGeometry)> callback);
  /* This signal is emitted when the frame geometry is about to change. the new
   * geometry is not known yet */
  void onFrameGeometryAboutToChange(std::function<void()> callback);
  /* This signal is emitted when the visible geometry has changed. */
  void onVisibleGeometryChanged(std::function<void()> callback);
  /* This signal is emitted when associated tile has changed, including from and
   * to none */
  void onTileChanged(std::function<void(KWin::Tile *tile)> callback);
  void onFullScreenChanged(std::function<void()> callback);
  void onSkipTaskbarChanged(std::function<void()> callback);
  void onSkipPagerChanged(std::function<void()> callback);
  void onSkipSwitcherChanged(std::function<void()> callback);
  void onIconChanged(std::function<void()> callback);
  void onActiveChanged(std::function<void()> callback);
  void onKeepAboveChanged(std::function<void(bool)> callback);
  void onKeepBelowChanged(std::function<void(bool)> callback);
  /* Emitted whenever the demands attention state changes. */
  void onDemandsAttentionChanged(std::function<void()> callback);
  void onDesktopsChanged(std::function<void()> callback);
  void onActivitiesChanged(std::function<void()> callback);
  void onMinimizedChanged(std::function<void()> callback);
  void onPaletteChanged(std::function<void(const QPalette &p)> callback);
  void onColorSchemeChanged(std::function<void()> callback);
  void onCaptionChanged(std::function<void()> callback);
  void onCaptionNormalChanged(std::function<void()> callback);
  // void onMaximizedAboutToChange(std::function<void(MaximizeMode mode)>
  // callback);
  void onMaximizedChanged(std::function<void()> callback);
  void onTransientChanged(std::function<void()> callback);
  void onModalChanged(std::function<void()> callback);
  void onQuickTileModeChanged(std::function<void()> callback);
  void onMoveResizedChanged(std::function<void()> callback);
  // void onMoveResizeCursorChanged(std::function<void(CursorShape)> callback);
  void onInteractiveMoveResizeStarted(std::function<void()> callback);
  void onInteractiveMoveResizeStepped(
      std::function<void(const QRectF &geometry)> callback);
  void onInteractiveMoveResizeFinished(std::function<void()> callback);
  void onCloseableChanged(std::function<void(bool)> callback);
  void onMinimizeableChanged(std::function<void(bool)> callback);
  void onShadeableChanged(std::function<void(bool)> callback);
  void onMaximizeableChanged(std::function<void(bool)> callback);
  void onDesktopFileNameChanged(std::function<void()> callback);
  void onApplicationMenuChanged(std::function<void()> callback);
  void onHasApplicationMenuChanged(std::function<void(bool)> callback);
  void onApplicationMenuActiveChanged(std::function<void(bool)> callback);
  void onUnresponsiveChanged(std::function<void(bool)> callback);
  void onDecorationChanged(std::function<void()> callback);
  void onHiddenChanged(std::function<void()> callback);
  void onHiddenByShowDesktopChanged(std::function<void()> callback);
  void onLockScreenOverlayChanged(std::function<void()> callback);
  void onReadyForPaintingChanged(std::function<void()> callback);
  void onMaximizeGeometryRestoreChanged(std::function<void()> callback);
  void onFullscreenGeometryRestoreChanged(std::function<void()> callback);

  void closeWindow() {
    return kwinpp_internal::call_kwin_func<void>(kwinpp_internal::ref_of(this),
                                                 "Window.closeWindow");
  }
  /* Sets the maximization according to vertically and horizontally. */
  void setMaximize(bool vertically, bool horizontally) {
    return kwinpp_internal::call_kwin_func<void>(kwinpp_internal::ref_of(this),
                                                 "Window.setMaximize",
                                                 vertically, horizontally);
  }
};

class TileManager {
public:
  ~TileManager() { kwinpp_internal::release_handle(this); }

  KWin::Tile *rootTile() {
    return kwinpp_internal::call_kwin_func<KWin::Tile *>(
        kwinpp_internal::ref_of(this), "TileManager.rootTile");
  }

  // undocumented/C++ scripting only type
  // TileModel *model();

  void onTileRemoved(std::function<void(KWin::Tile *tile)> callback);

  KWin::Tile *bestTileForPosition(qreal x, qreal y) {
    return kwinpp_internal::call_kwin_func<KWin::Tile *>(
        kwinpp_internal::ref_of(this), "TileManager.bestTileForPosition", x, y);
  }
};
class Tile {
public:
  ~Tile() { kwinpp_internal::release_handle(this); }

  enum class LayoutDirection {
    Floating,
    Horizontal,
    Vertical,
  };

  const QRectF absoluteGeometry() {
    return kwinpp_internal::call_kwin_func<const QRectF>(
        kwinpp_internal::ref_of(this), "Tile.absoluteGeometry");
  }
  const QRectF absoluteGeometryInScreen() {
    return kwinpp_internal::call_kwin_func<const QRectF>(
        kwinpp_internal::ref_of(this), "Tile.absoluteGeometryInScreen");
  }
  const int positionInLayout() {
    return kwinpp_internal::call_kwin_func<const int>(
        kwinpp_internal::ref_of(this), "Tile.positionInLayout");
  }
  const Tile *parent() {
    return kwinpp_internal::call_kwin_func<const Tile *>(
        kwinpp_internal::ref_of(this), "Tile.parent");
  }
  const QList<KWin::Tile *> tiles() {
    return kwinpp_internal::call_kwin_func<const QList<KWin::Tile *>>(
        kwinpp_internal::ref_of(this), "Tile.tiles");
  }
  const QList<KWin::Window *> windows() {
    return kwinpp_internal::call_kwin_func<const QList<KWin::Window *>>(
        kwinpp_internal::ref_of(this), "Tile.windows");
  }
  const bool isLayout() {
    return kwinpp_internal::call_kwin_func<const bool>(
        kwinpp_internal::ref_of(this), "Tile.isLayout");
  }
  const bool canBeRemoved() {
    return kwinpp_internal::call_kwin_func<const bool>(
        kwinpp_internal::ref_of(this), "Tile.canBeRemoved");
  }

  QRectF relativeGeometry() {
    return kwinpp_internal::call_kwin_func<QRectF>(
        kwinpp_internal::ref_of(this), "Tile.relativeGeometry");
  }
  void setRelativeGeometry(QRectF value) {
    return kwinpp_internal::call_kwin_func<void>(
        kwinpp_internal::ref_of(this), "Tile.setRelativeGeometry", value);
  }
  qreal padding() {
    return kwinpp_internal::call_kwin_func<qreal>(kwinpp_internal::ref_of(this),
                                                  "Tile.padding");
  }
  void setPadding(qreal value) {
    return kwinpp_internal::call_kwin_func<void>(kwinpp_internal::ref_of(this),
                                                 "Tile.setPadding", value);
  }

  void onRelativeGeometryChanged(std::function<void()>);
  void onAbsoluteGeometryChanged(std::function<void()>);
  void onWindowGeometryChanged(std::function<void()>);
  void onPaddingChanged(std::function<void(qreal padding)>);
  void onRowChanged(std::function<void(int row)>);
  void onIsLayoutChanged(std::function<void(bool isLayout)>);
  void onChildTilesChanged(std::function<void()>);
  void onWindowAdded(std::function<void(Window *window)>);
  void onWindowRemoved(std::function<void(Window *window)>);
  void onWindowsChanged(std::function<void()>);

  void resizeByPixels(qreal delta, Qt::Edge edge) {
    return kwinpp_internal::call_kwin_func<void>(
        kwinpp_internal::ref_of(this), "Tile.resizeByPixels", delta, edge);
  }
};
} // namespace KWin
