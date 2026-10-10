#pragma once

/* translation of the APIs listed on
 * https://develop.kde.org/docs/plasma/kwin/api/#global */

#define KWINPP_EXPORT __attribute__((visibility("default")))

#include <chrono>
#include <cstdint>
#include <functional>
#include <optional>

#ifdef KWINPP_NO_QT
#include <string>

#include "kwinpp_types.hpp"
#endif

#include "kwinppi.hpp"

namespace kwinpp {
/*
 * if kwinpp is unable to load, this returns the resulting exception, and you
 * should either throw it or disable the kwin codepaths.
 *
 * otherwise it returns {}.
 */
KWINPP_EXPORT std::optional<std::string> get_exception();
}; // namespace kwinpp

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

  KWINPP_EXPORT const List<KWin::VirtualDesktop *> desktops() {
    return kwinpp_internal::call_kwin_func<const List<KWin::VirtualDesktop *>>(
        "workspace", "WorkspaceWrapper.desktops");
  }
  KWINPP_EXPORT const Size desktopGridSize() {
    return kwinpp_internal::call_kwin_func<const Size>(
        "workspace", "WorkspaceWrapper.desktopGridSize");
  }
  KWINPP_EXPORT const int desktopGridWidth() {
    return kwinpp_internal::call_kwin_func<const int>(
        "workspace", "WorkspaceWrapper.desktopGridWidth");
  }
  KWINPP_EXPORT const int desktopGridHeight() {
    return kwinpp_internal::call_kwin_func<const int>(
        "workspace", "WorkspaceWrapper.desktopGridHeight");
  }
  KWINPP_EXPORT const int workspaceWidth() {
    return kwinpp_internal::call_kwin_func<const int>(
        "workspace", "WorkspaceWrapper.workspaceWidth");
  }
  KWINPP_EXPORT const int workspaceHeight() {
    return kwinpp_internal::call_kwin_func<const int>(
        "workspace", "WorkspaceWrapper.workspaceHeight");
  }
  KWINPP_EXPORT const Size workspaceSize() {
    return kwinpp_internal::call_kwin_func<const Size>(
        "workspace", "WorkspaceWrapper.workspaceSize");
  }
  KWINPP_EXPORT const KWin::Output *activeScreen() {
    return kwinpp_internal::call_kwin_func<const KWin::Output *>(
        "workspace", "WorkspaceWrapper.activeScreen");
  }
  KWINPP_EXPORT const List<KWin::Output *> screens() {
    return kwinpp_internal::call_kwin_func<const List<KWin::Output *>>(
        "workspace", "WorkspaceWrapper.screens");
  }
  KWINPP_EXPORT const StringList activities() {
    return kwinpp_internal::call_kwin_func<const StringList>(
        "workspace", "WorkspaceWrapper.activities");
  }
  /*The bounding size of all screens combined. Overlapping areas are not counted
   * multiple times. */
  KWINPP_EXPORT const Size virtualScreenSize() {
    return kwinpp_internal::call_kwin_func<const Size>(
        "workspace", "WorkspaceWrapper.virtualScreenSize");
  }
  /*The bounding geometry of all screens combined. Always starts at (0,0) and
   * has virtualScreenSize as it's size. */
  KWINPP_EXPORT const Rect virtualScreenGeometry() {
    return kwinpp_internal::call_kwin_func<const Rect>(
        "workspace", "WorkspaceWrapper.virtualScreenGeometry");
  }
  /* List of Clients currently managed by KWin, orderd by their visibility
   * (later ones cover earlier ones).*/
  KWINPP_EXPORT const List<KWin::Window *> stackingOrder() {
    return kwinpp_internal::call_kwin_func<const List<KWin::Window *>>(
        "workspace", "WorkspaceWrapper.stackingOrder");
  }

  /* The current position of the cursor. */
  KWINPP_EXPORT Point cursorPos() {
    return kwinpp_internal::call_kwin_func<Point>("workspace",
                                                  "WorkspaceWrapper.cursorPos");
  }

  /* The current virtual desktop on the active screen. */
  KWINPP_EXPORT KWin::VirtualDesktop *currentDesktop() {
    return kwinpp_internal::get_kwin_field<KWin::VirtualDesktop *>(
        "workspace", "currentDesktop");
  }
  /* Set the current virtual desktop on the active screen. */
  KWINPP_EXPORT void setCurrentDesktop(KWin::VirtualDesktop *val) {
    return kwinpp_internal::set_kwin_field("workspace", "currentDesktop", val);
  }

  KWINPP_EXPORT KWin::Window *activeWindow() {
    return kwinpp_internal::get_kwin_field<KWin::Window *>("workspace",
                                                           "activeWindow");
  }
  KWINPP_EXPORT void setActiveWindow(KWin::Window *val) {
    return kwinpp_internal::set_kwin_field("workspace", "activeWindow", val);
  }

  KWINPP_EXPORT String currentActivity() {
    return kwinpp_internal::get_kwin_field<String>("workspace",
                                                   "currentActivity");
  }
  KWINPP_EXPORT void setCurrentActivity(String val) {
    return kwinpp_internal::set_kwin_field("workspace", "currentActivity", val);
  }

  KWINPP_EXPORT kwinpp::Connection
  onWindowAdded(std::function<void(KWin::Window *window)> callback) {

    return kwinpp_internal::connect_kwin_signal("workspace", "windowAdded",

                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onWindowRemoved(std::function<void(KWin::Window *window)> callback) {
    return kwinpp_internal::connect_kwin_signal("workspace", "windowRemoved",
                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onWindowActivated(std::function<void(KWin::Window *window)> callback) {
    return kwinpp_internal::connect_kwin_signal("workspace", "windowActivated",
                                                std::move(callback));
  }
  /* This signal is emitted when a virtual desktop is added or removed. */
  KWINPP_EXPORT kwinpp::Connection
  onDesktopsChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal("workspace", "desktopsChanged",
                                                std::move(callback));
  }
  /* Signal emitted whenever the layout of virtual desktops changed. That is
   * desktopGrid(Size/Width/Height) will have new values. 4.11 */
  KWINPP_EXPORT kwinpp::Connection
  onDesktopLayoutChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(
        "workspace", "desktopLayoutChanged", std::move(callback));
  }
  /* Emitted when the output list changes, e.g. an output is connected or
   * removed. */
  KWINPP_EXPORT kwinpp::Connection
  onScreensChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal("workspace", "screensChanged",
                                                std::move(callback));
  }
  /* Signal emitted whenever the current activity changed. id id of the new
   * activity */
  KWINPP_EXPORT kwinpp::Connection
  onCurrentActivityChanged(std::function<void(const String &id)> callback) {
    return kwinpp_internal::connect_kwin_signal(
        "workspace", "currentActivityChanged", std::move(callback));
  }
  /* Signal emitted whenever the list of activities changed. id id of the new
   * activity */
  KWINPP_EXPORT kwinpp::Connection
  onActivitiesChanged(std::function<void(const String &id)> callback) {
    return kwinpp_internal::connect_kwin_signal(
        "workspace", "activitiesChanged", std::move(callback));
  }
  /* This signal is emitted when a new activity is added id id of the new
   * activity */
  KWINPP_EXPORT kwinpp::Connection
  onActivityAdded(std::function<void(const String &id)> callback) {
    return kwinpp_internal::connect_kwin_signal("workspace", "activityAdded",
                                                std::move(callback));
  }
  /* This signal is emitted when the activity is removed id id of the removed
   * activity */
  KWINPP_EXPORT kwinpp::Connection
  onActivityRemoved(std::function<void(const String &id)> callback) {
    return kwinpp_internal::connect_kwin_signal("workspace", "activityRemoved",
                                                std::move(callback));
  }
  /* Emitted whenever the virtualScreenSize changes. virtualScreenSize() 5.0 */
  KWINPP_EXPORT kwinpp::Connection
  onVirtualScreenSizeChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(
        "workspace", "virtualScreenSizeChanged", std::move(callback));
  }
  /* Emitted whenever the virtualScreenGeometry changes.
   * virtualScreenGeometry() 5.0 */
  KWINPP_EXPORT kwinpp::Connection
  onVirtualScreenGeometryChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(
        "workspace", "virtualScreenGeometryChanged", std::move(callback));
  }
  /* This signal is emitted when the current virtual desktop changes. */
  KWINPP_EXPORT kwinpp::Connection onCurrentDesktopChanged(
      std::function<void(KWin::VirtualDesktop *previous,
                         KWin::VirtualDesktop *current, KWin::Output *output)>
          callback) {
    return kwinpp_internal::connect_kwin_signal(
        "workspace", "currentDesktopChanged", std::move(callback));
  }
  /* This signal is emitted when the cursor position changes. cursorPos() */
  KWINPP_EXPORT kwinpp::Connection
  onCursorPosChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal("workspace", "cursorPosChanged",
                                                std::move(callback));
  }

  KWINPP_EXPORT void slotSwitchDesktopNext() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotSwitchDesktopNext");
  }
  KWINPP_EXPORT void slotSwitchDesktopPrevious() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotSwitchDesktopPrevious");
  }
  KWINPP_EXPORT void slotSwitchDesktopRight() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotSwitchDesktopRight");
  }
  KWINPP_EXPORT void slotSwitchDesktopLeft() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotSwitchDesktopLeft");
  }
  KWINPP_EXPORT void slotSwitchDesktopUp() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotSwitchDesktopUp");
  }
  KWINPP_EXPORT void slotSwitchDesktopDown() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotSwitchDesktopDown");
  }
  KWINPP_EXPORT void slotSwitchToNextScreen() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotSwitchToNextScreen");
  }
  KWINPP_EXPORT void slotSwitchToPrevScreen() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotSwitchToPrevScreen");
  }
  KWINPP_EXPORT void slotSwitchToRightScreen() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotSwitchToRightScreen");
  }
  KWINPP_EXPORT void slotSwitchToLeftScreen() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotSwitchToLeftScreen");
  }
  KWINPP_EXPORT void slotSwitchToAboveScreen() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotSwitchToAboveScreen");
  }
  KWINPP_EXPORT void slotSwitchToBelowScreen() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotSwitchToBelowScreen");
  }
  KWINPP_EXPORT void slotWindowToNextScreen() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowToNextScreen");
  }
  KWINPP_EXPORT void slotWindowToPrevScreen() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowToPrevScreen");
  }
  KWINPP_EXPORT void slotWindowToRightScreen() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowToRightScreen");
  }
  KWINPP_EXPORT void slotWindowToLeftScreen() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowToLeftScreen");
  }
  KWINPP_EXPORT void slotWindowToAboveScreen() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowToAboveScreen");
  }
  KWINPP_EXPORT void slotWindowToBelowScreen() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowToBelowScreen");
  }
  KWINPP_EXPORT void slotToggleShowDesktop() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotToggleShowDesktop");
  }
  KWINPP_EXPORT void slotWindowMaximize() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowMaximize");
  }
  KWINPP_EXPORT void slotWindowMaximizeVertical() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowMaximizeVertical");
  }
  KWINPP_EXPORT void slotWindowMaximizeHorizontal() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowMaximizeHorizontal");
  }
  KWINPP_EXPORT void slotWindowMinimize() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowMinimize");
  }
  KWINPP_EXPORT void slotWindowShade() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowShade");
  }
  KWINPP_EXPORT void slotWindowRaise() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowRaise");
  }
  KWINPP_EXPORT void slotWindowLower() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowLower");
  }
  KWINPP_EXPORT void slotWindowRaiseOrLower() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowRaiseOrLower");
  }
  KWINPP_EXPORT void slotActivateAttentionWindow() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotActivateAttentionWindow");
  }
  KWINPP_EXPORT void slotWindowMoveLeft() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowMoveLeft");
  }
  KWINPP_EXPORT void slotWindowMoveRight() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowMoveRight");
  }
  KWINPP_EXPORT void slotWindowMoveUp() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowMoveUp");
  }
  KWINPP_EXPORT void slotWindowMoveDown() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowMoveDown");
  }
  KWINPP_EXPORT void slotWindowExpandHorizontal() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowExpandHorizontal");
  }
  KWINPP_EXPORT void slotWindowExpandVertical() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowExpandVertical");
  }
  KWINPP_EXPORT void slotWindowShrinkHorizontal() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowShrinkHorizontal");
  }
  KWINPP_EXPORT void slotWindowShrinkVertical() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowShrinkVertical");
  }
  KWINPP_EXPORT void slotWindowQuickTileLeft() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowQuickTileLeft");
  }
  KWINPP_EXPORT void slotWindowQuickTileRight() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowQuickTileRight");
  }
  KWINPP_EXPORT void slotWindowQuickTileTop() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowQuickTileTop");
  }
  KWINPP_EXPORT void slotWindowQuickTileBottom() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowQuickTileBottom");
  }
  KWINPP_EXPORT void slotWindowQuickTileTopLeft() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowQuickTileTopLeft");
  }
  KWINPP_EXPORT void slotWindowQuickTileTopRight() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowQuickTileTopRight");
  }
  KWINPP_EXPORT void slotWindowQuickTileBottomLeft() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowQuickTileBottomLeft");
  }
  KWINPP_EXPORT void slotWindowQuickTileBottomRight() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowQuickTileBottomRight");
  }
  KWINPP_EXPORT void slotSwitchWindowUp() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotSwitchWindowUp");
  }
  KWINPP_EXPORT void slotSwitchWindowDown() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotSwitchWindowDown");
  }
  KWINPP_EXPORT void slotSwitchWindowRight() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotSwitchWindowRight");
  }
  KWINPP_EXPORT void slotSwitchWindowLeft() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotSwitchWindowLeft");
  }
  KWINPP_EXPORT void slotIncreaseWindowOpacity() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotIncreaseWindowOpacity");
  }
  KWINPP_EXPORT void slotLowerWindowOpacity() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotLowerWindowOpacity");
  }
  KWINPP_EXPORT void slotWindowOperations() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowOperations");
  }
  KWINPP_EXPORT void slotWindowClose() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowClose");
  }
  KWINPP_EXPORT void slotWindowMove() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowMove");
  }
  KWINPP_EXPORT void slotWindowResize() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowResize");
  }
  KWINPP_EXPORT void slotWindowAbove() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowAbove");
  }
  KWINPP_EXPORT void slotWindowBelow() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowBelow");
  }
  KWINPP_EXPORT void slotWindowOnAllDesktops() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowOnAllDesktops");
  }
  KWINPP_EXPORT void slotWindowFullScreen() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowFullScreen");
  }
  KWINPP_EXPORT void slotWindowNoBorder() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowNoBorder");
  }
  KWINPP_EXPORT void slotWindowToNextDesktop() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowToNextDesktop");
  }
  KWINPP_EXPORT void slotWindowToPreviousDesktop() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowToPreviousDesktop");
  }
  KWINPP_EXPORT void slotWindowToDesktopRight() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowToDesktopRight");
  }
  KWINPP_EXPORT void slotWindowToDesktopLeft() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowToDesktopLeft");
  }
  KWINPP_EXPORT void slotWindowToDesktopUp() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowToDesktopUp");
  }
  KWINPP_EXPORT void slotWindowToDesktopDown() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.slotWindowToDesktopDown");
  }
  /* Sends the Window to the given output.*/
  KWINPP_EXPORT void sendClientToScreen(KWin::Window *client,
                                        KWin::Output *output) {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.sendClientToScreen", client, output);
  }
  /* Shows an outline at the specified geometry. If an outline is already shown
   * the outline is moved to the new position. Use hideOutline to remove the
   * outline again. */
  KWINPP_EXPORT void showOutline(const Rect &geometry) {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.showOutline", geometry);
  }
  /* Overloaded method for convenience.*/
  KWINPP_EXPORT void showOutline(int x, int y, int width, int height) {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.showOutline", x, y, width, height);
  }
  /* Hides the outline previously shown by showOutline.*/
  KWINPP_EXPORT void hideOutline() {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.hideOutline");
  }
  /* Returns the current desktop on the given screen. */
  KWINPP_EXPORT KWin::VirtualDesktop *
  currentDesktopForScreen(KWin::Output *output) const {
    return kwinpp_internal::call_kwin_func<KWin::VirtualDesktop *>(
        "workspace", "WorkspaceWrapper.currentDesktopForScreen", output);
  }
  /* Sets the current desktop on the given screen.*/
  KWINPP_EXPORT void setCurrentDesktopForScreen(KWin::VirtualDesktop *desktop,
                                                KWin::Output *output) {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.setCurrentDesktopForScreen", desktop,
        output);
  }
  KWINPP_EXPORT KWin::Output *screenAt(const PointF &pos) const {
    return kwinpp_internal::call_kwin_func<KWin::Output *>(
        "workspace", "WorkspaceWrapper.screenAt", pos);
  }
  KWINPP_EXPORT KWin::TileManager *
  tilingForScreen(const String &screenName) const {
    return kwinpp_internal::call_kwin_func<KWin::TileManager *>(
        "workspace", "WorkspaceWrapper.tilingForScreen", screenName);
  }
  KWINPP_EXPORT KWin::TileManager *tilingForScreen(KWin::Output *output) const {
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
  KWINPP_EXPORT RectF clientArea(ClientAreaOption option, KWin::Output *output,
                                 KWin::VirtualDesktop *desktop) const {
    return kwinpp_internal::call_kwin_func<RectF>(
        "workspace", "WorkspaceWrapper.clientArea", option, output, desktop);
  }
  /* Overloaded method for convenience. client The Client for which the area
   * should be retrieved The specified screen geometry */
  KWINPP_EXPORT RectF clientArea(ClientAreaOption option,
                                 KWin::Window *client) const {
    return kwinpp_internal::call_kwin_func<RectF>(
        "workspace", "WorkspaceWrapper.clientArea", option, client);
  }
  KWINPP_EXPORT RectF clientArea(ClientAreaOption option,
                                 const KWin::Window *client) const {
    return kwinpp_internal::call_kwin_func<RectF>(
        "workspace", "WorkspaceWrapper.clientArea", option, client);
  }

  /* Create a new virtual desktop at the requested position. position The
   * position of the desktop. It should be in range [0, count]. name The name
   * for the new desktop, if empty the default name will be used. */
  KWINPP_EXPORT void createDesktop(int position, const String &name) const {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.createDesktop", position, name);
  }
  /* Removes the specified virtual desktop. */
  KWINPP_EXPORT void removeDesktop(KWin::VirtualDesktop *desktop) {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.removeDesktop", desktop);
  }
  /* Provides support information about the currently running KWin instance. */
  KWINPP_EXPORT String supportInformation() const {
    return kwinpp_internal::call_kwin_func<String>(
        "workspace", "WorkspaceWrapper.supportInformation");
  }
  /* Raises a Window above all others on the screen.
   *
   * `window` The Window to raise */
  KWINPP_EXPORT void raiseWindow(KWin::Window *window) {
    return kwinpp_internal::call_kwin_func<void>(
        "workspace", "WorkspaceWrapper.raiseWindow", window);
  }
  /* Finds the Client with the given windowId. windowId The window Id of the
   * Client The found Client or null */
  KWINPP_EXPORT KWin::Window *getClient(std::uint64_t windowId) {
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
  KWINPP_EXPORT List<KWin::Window *> windowAt(const PointF &pos,
                                              int count = 1) const {
    return kwinpp_internal::call_kwin_func<List<KWin::Window *>>(
        "workspace", "WorkspaceWrapper.windowAt", pos, count);
  }

  /* Checks if a specific effect is currently active.
   *
   * `pluginId`: The plugin Id of the effect to check.
   *
   * Returns: true if the effect isloaded and currently active, false
   * otherwise.*/
  KWINPP_EXPORT bool isEffectActive(const String &pluginId) const {
    return kwinpp_internal::call_kwin_func<bool>(
        "workspace", "WorkspaceWrapper.isEffectActive", pluginId);
  }
};

extern WorkspaceWrapper workspace;

class VirtualDesktop {
public:
  KWINPP_EXPORT ~VirtualDesktop() { kwinpp_internal::release_handle(this); }

  KWINPP_EXPORT const String id() {
    return kwinpp_internal::call_kwin_func<const String>(
        kwinpp_internal::ref_of(this), "VirtualDesktop.id");
  }
  KWINPP_EXPORT const unsigned int x11DesktopNumber() {
    return kwinpp_internal::call_kwin_func<const unsigned int>(
        kwinpp_internal::ref_of(this), "VirtualDesktop.x11DesktopNumber");
  }

  KWINPP_EXPORT String name() {
    return kwinpp_internal::get_kwin_field<String>(
        kwinpp_internal::ref_of(this), "name");
  }
  KWINPP_EXPORT void setName(String val) {
    return kwinpp_internal::set_kwin_field(kwinpp_internal::ref_of(this),
                                           "name", val);
  }

  KWINPP_EXPORT kwinpp::Connection
  onNameChanged(std::function<void()> callback) {

    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "nameChanged",

                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onX11DesktopNumberChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "x11DesktopNumberChanged",
                                                std::move(callback));
  }
  /* Emitted just before the desktop gets destroyed. */
  KWINPP_EXPORT kwinpp::Connection
  onAboutToBeDestroyed(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "aboutToBeDestroyed",
                                                std::move(callback));
  }
};

class Output {
public:
  KWINPP_EXPORT ~Output() { kwinpp_internal::release_handle(this); }

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

  KWINPP_EXPORT const Rect geometry() {
    return kwinpp_internal::call_kwin_func<const Rect>(
        kwinpp_internal::ref_of(this), "Output.geometry");
  }
  KWINPP_EXPORT const double devicePixelRatio() {
    return kwinpp_internal::call_kwin_func<const double>(
        kwinpp_internal::ref_of(this), "Output.devicePixelRatio");
  }
  KWINPP_EXPORT const String name() {
    return kwinpp_internal::call_kwin_func<const String>(
        kwinpp_internal::ref_of(this), "Output.name");
  }
  KWINPP_EXPORT const String manufacturer() {
    return kwinpp_internal::call_kwin_func<const String>(
        kwinpp_internal::ref_of(this), "Output.manufacturer");
  }
  KWINPP_EXPORT const String model() {
    return kwinpp_internal::call_kwin_func<const String>(
        kwinpp_internal::ref_of(this), "Output.model");
  }
  KWINPP_EXPORT const String serialNumber() {
    return kwinpp_internal::call_kwin_func<const String>(
        kwinpp_internal::ref_of(this), "Output.serialNumber");
  }

  /* This signal is emitted when the geometry of this output has changed. */
  KWINPP_EXPORT kwinpp::Connection
  onGeometryChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "geometryChanged", std::move(callback));
  }
  /* This signal is emitted when the output has been enabled or disabled. */
  KWINPP_EXPORT kwinpp::Connection
  onEnabledChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "enabledChanged", std::move(callback));
  }
  /* This signal is emitted when the device pixel ratio of the output has
   * changed. */
  KWINPP_EXPORT kwinpp::Connection
  onScaleChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "scaleChanged", std::move(callback));
  }
  /* Notifies that the display will be dimmed in time ms. This allows effects to
   * plan for it and hopefully animate it */
  KWINPP_EXPORT kwinpp::Connection onAboutToTurnOff(
      std::function<void(std::chrono::milliseconds time)> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "aboutToTurnOff", std::move(callback));
  }
  /* Notifies that the output has been turned on and the wake can be decorated.
   */
  KWINPP_EXPORT kwinpp::Connection onWakeUp(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "wakeUp", std::move(callback));
  }

  /* Notifies that the output is about to change configuration based on a user
   * interaction. Be it because it gets a transformation or moved around. Only
   * to be used for effects */
  // undocumented/C++ scripting only type
  // void onAboutToChange(std::function<void(OutputChangeSet *changeSet)>);

  /* Notifies that the output changed based on a user interaction. Be it because
   * it gets a transformation or moved around. Only to be used for effects */
  KWINPP_EXPORT kwinpp::Connection onChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "changed", std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onCurrentModeChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "currentModeChanged",
                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onModesChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "modesChanged", std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onOutputChange(std::function<void(const Region &damagedRegion)> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "outputChange", std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onTransformChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "transformChanged", std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onDpmsModeChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "dpmsModeChanged", std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onCapabilitiesChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "capabilitiesChanged",
                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onOverscanChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "overscanChanged", std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onVrrPolicyChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "vrrPolicyChanged", std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onRgbRangeChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "rgbRangeChanged", std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onWideColorGamutChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "wideColorGamutChanged",
                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onSdrBrightnessChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "sdrBrightnessChanged",
                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onHighDynamicRangeChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "highDynamicRangeChanged",
                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onAutoRotationPolicyChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "autoRotationPolicyChanged",
                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onIccProfileChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "iccProfileChanged",
                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onIccProfilePathChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "iccProfilePathChanged",
                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onBrightnessMetadataChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "brightnessMetadataChanged",
                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onSdrGamutWidenessChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "sdrGamutWidenessChanged",
                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onColorDescriptionChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "colorDescriptionChanged",
                                                std::move(callback));
  }

  KWINPP_EXPORT PointF mapToGlobal(const PointF &pos) const {
    return kwinpp_internal::call_kwin_func<PointF>(
        kwinpp_internal::ref_of(this), "Output.mapToGlobal", pos);
  }
  KWINPP_EXPORT PointF mapFromGlobal(const PointF &pos) const {
    return kwinpp_internal::call_kwin_func<PointF>(
        kwinpp_internal::ref_of(this), "Output.mapFromGlobal", pos);
  }
};
class Window {
public:
  KWINPP_EXPORT ~Window() { kwinpp_internal::release_handle(this); }

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
  KWINPP_EXPORT RectF bufferGeometry() const {
    return kwinpp_internal::call_kwin_func<RectF>(kwinpp_internal::ref_of(this),
                                                  "Window.bufferGeometry");
  }
  /* The geometry of the Window without frame borders. */
  KWINPP_EXPORT RectF clientGeometry() const {
    return kwinpp_internal::call_kwin_func<RectF>(kwinpp_internal::ref_of(this),
                                                  "Window.clientGeometry");
  }
  /* This property holds the position of the Window's frame geometry. */
  KWINPP_EXPORT PointF pos() const {
    return kwinpp_internal::call_kwin_func<PointF>(
        kwinpp_internal::ref_of(this), "Window.pos");
  }
  /* This property holds the size of the Window's frame geometry. */
  KWINPP_EXPORT SizeF size() const {
    return kwinpp_internal::call_kwin_func<SizeF>(kwinpp_internal::ref_of(this),
                                                  "Window.size");
  }
  /* This property holds the x position of the Window's frame geometry. */
  KWINPP_EXPORT double x() const {
    return kwinpp_internal::call_kwin_func<double>(
        kwinpp_internal::ref_of(this), "Window.x");
  }
  /* This property holds the y position of the Window's frame geometry. */
  KWINPP_EXPORT double y() const {
    return kwinpp_internal::call_kwin_func<double>(
        kwinpp_internal::ref_of(this), "Window.y");
  }
  /* This property holds the width of the Window's frame geometry. */
  KWINPP_EXPORT double width() const {
    return kwinpp_internal::call_kwin_func<double>(
        kwinpp_internal::ref_of(this), "Window.width");
  }
  /* This property holds the height of the Window's frame geometry. */
  KWINPP_EXPORT double height() const {
    return kwinpp_internal::call_kwin_func<double>(
        kwinpp_internal::ref_of(this), "Window.height");
  }
  /* The output where the window center is on */
  KWINPP_EXPORT KWin::Output *output() const {
    return kwinpp_internal::call_kwin_func<KWin::Output *>(
        kwinpp_internal::ref_of(this), "Window.output");
  }
  KWINPP_EXPORT RectF rect() const {
    return kwinpp_internal::call_kwin_func<RectF>(kwinpp_internal::ref_of(this),
                                                  "Window.rect");
  }
  KWINPP_EXPORT String resourceName() const {
    return kwinpp_internal::call_kwin_func<String>(
        kwinpp_internal::ref_of(this), "Window.resourceName");
  }
  KWINPP_EXPORT String resourceClass() const {
    return kwinpp_internal::call_kwin_func<String>(
        kwinpp_internal::ref_of(this), "Window.resourceClass");
  }
  KWINPP_EXPORT String windowRole() const {
    return kwinpp_internal::call_kwin_func<String>(
        kwinpp_internal::ref_of(this), "Window.windowRole");
  }
  /* Returns whether the window is a desktop background window (the one with
   * wallpaper). See _NET_WM_WINDOW_TYPE_DESKTOP at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  KWINPP_EXPORT bool desktopWindow() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.desktopWindow");
  }
  /* Returns whether the window is a dock (i.e. a panel). See
   * _NET_WM_WINDOW_TYPE_DOCK at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  KWINPP_EXPORT bool dock() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.dock");
  }
  /* Returns whether the window is a standalone (detached) toolbar window. See
   * _NET_WM_WINDOW_TYPE_TOOLBAR at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  KWINPP_EXPORT bool toolbar() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.toolbar");
  }
  /* Returns whether the window is a torn-off menu. See _NET_WM_WINDOW_TYPE_MENU
   * at https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  KWINPP_EXPORT bool menu() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.menu");
  }
  /* Returns whether the window is a "normal" window, i.e. an application or any
   * other window for which none of the specialized window types fit. See
   * _NET_WM_WINDOW_TYPE_NORMAL at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  KWINPP_EXPORT bool normalWindow() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.normalWindow");
  }
  /* Returns whether the window is a dialog window. See
   * _NET_WM_WINDOW_TYPE_DIALOG at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  KWINPP_EXPORT bool dialog() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.dialog");
  }
  /* Returns whether the window is a splashscreen. Note that many (especially
   * older) applications do not support marking their splash windows with this
   * type. See _NET_WM_WINDOW_TYPE_SPLASH at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  KWINPP_EXPORT bool splash() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.splash");
  }
  /* Returns whether the window is a utility window, such as a tool window. See
   * _NET_WM_WINDOW_TYPE_UTILITY at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  KWINPP_EXPORT bool utility() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.utility");
  }
  /* Returns whether the window is a dropdown menu (i.e. a popup directly or
   * indirectly open from the applications menubar). See
   * _NET_WM_WINDOW_TYPE_DROPDOWN_MENU at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  KWINPP_EXPORT bool dropdownMenu() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.dropdownMenu");
  }
  /* Returns whether the window is a popup menu (that is not a torn-off or
   * dropdown menu). See _NET_WM_WINDOW_TYPE_POPUP_MENU at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  KWINPP_EXPORT bool popupMenu() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.popupMenu");
  }
  /* Returns whether the window is a tooltip. See _NET_WM_WINDOW_TYPE_TOOLTIP at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  KWINPP_EXPORT bool tooltip() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.tooltip");
  }
  /* Returns whether the window is a window with a notification. See
   * _NET_WM_WINDOW_TYPE_NOTIFICATION at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  KWINPP_EXPORT bool notification() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.notification");
  }
  /* Returns whether the window is a window with a critical notification. */
  KWINPP_EXPORT bool criticalNotification() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.criticalNotification");
  }
  /* Returns whether the window is an applet popup. */
  KWINPP_EXPORT bool appletPopup() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.appletPopup");
  }
  /* Returns whether the window is an On Screen Display. */
  KWINPP_EXPORT bool onScreenDisplay() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.onScreenDisplay");
  }
  /* Returns whether the window is a combobox popup. See
   * _NET_WM_WINDOW_TYPE_COMBO at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  KWINPP_EXPORT bool comboBox() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.comboBox");
  }
  /* Returns whether the window is a Drag&Drop icon. See _NET_WM_WINDOW_TYPE_DND
   * at https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  KWINPP_EXPORT bool dndIcon() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.dndIcon");
  }
  /* Returns the NETWM window type See
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  KWINPP_EXPORT int windowType() const {
    return kwinpp_internal::call_kwin_func<int>(kwinpp_internal::ref_of(this),
                                                "Window.windowType");
  }
  /* Whether this Window is managed by KWin (it has control over its placement
   * and other aspects, as opposed to override-redirect windows that are
   * entirely handled by the application). */
  KWINPP_EXPORT bool managed() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.managed");
  }
  /* Whether this Window represents an already deleted window and only kept for
   * the compositor for animations. */
  KWINPP_EXPORT bool deleted() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.deleted");
  }
  /* Whether the window is a popup. */
  KWINPP_EXPORT bool popupWindow() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.popupWindow");
  }
  /* Whether this Window represents the outline. It's always false if
   * compositing is turned off. */
  KWINPP_EXPORT bool outline() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.outline");
  }
  /* This property holds a UUID to uniquely identify this Window. */
  KWINPP_EXPORT Uuid internalId() const {
    return kwinpp_internal::call_kwin_func<Uuid>(kwinpp_internal::ref_of(this),
                                                 "Window.internalId");
  }
  /* The pid of the process owning this window. 5.20 */
  KWINPP_EXPORT int pid() const {
    return kwinpp_internal::call_kwin_func<int>(kwinpp_internal::ref_of(this),
                                                "Window.pid");
  }
  /* The position of this window within Workspace's window stack. */
  KWINPP_EXPORT int stackingOrder() const {
    return kwinpp_internal::call_kwin_func<int>(kwinpp_internal::ref_of(this),
                                                "Window.stackingOrder");
  }
  /* Whether the Window can be set to fullScreen. The property is evaluated each
   * time it is invoked. Because of that there is no notify signal. */
  KWINPP_EXPORT bool fullScreenable() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.fullScreenable");
  }
  /* Whether this Window is active or not. Use Workspace::activateWindow() to
   * activate a Window. Workspace::activateWindow */
  KWINPP_EXPORT bool active() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.active");
  }
  /* Whether the window can be closed by the user. */
  KWINPP_EXPORT bool closeable() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.closeable");
  }

  /* Whether the Window can be shaded. The property is evaluated each time it is
   * invoked. Because of that there is no notify signal. */
  KWINPP_EXPORT bool shadeable() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.shadeable");
  }
  /* Whether the Window can be minimized. The property is evaluated each time it
   * is invoked. Because of that there is no notify signal. */
  KWINPP_EXPORT bool minimizable() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.minimizable");
  }
  /* The optional geometry representing the minimized Window in e.g a taskbar.
   * See _NET_WM_ICON_GEOMETRY at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . The value
   * is evaluated each time the getter is called. Because of that no changed
   * signal is provided. */
  KWINPP_EXPORT RectF iconGeometry() const {
    return kwinpp_internal::call_kwin_func<RectF>(kwinpp_internal::ref_of(this),
                                                  "Window.iconGeometry");
  }
  /* Returns whether the window is any of special windows types (desktop, dock,
   * splash, ...), i.e. window types that usually don't have a window frame and
   * the user does not use window management (moving, raising,...) on them. The
   * value is evaluated each time the getter is called. Because of that no
   * changed signal is provided. */
  KWINPP_EXPORT bool specialWindow() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.specialWindow");
  }
  /* The Caption of the Window. Read from WM_NAME property together with a
   * suffix for hostname and shortcut. To read only the caption as provided by
   * WM_NAME, use the getter with an additional false value. */
  KWINPP_EXPORT String caption() const {
    return kwinpp_internal::call_kwin_func<String>(
        kwinpp_internal::ref_of(this), "Window.caption");
  }
  /* Minimum size as specified in WM_NORMAL_HINTS */
  KWINPP_EXPORT SizeF minSize() const {
    return kwinpp_internal::call_kwin_func<SizeF>(kwinpp_internal::ref_of(this),
                                                  "Window.minSize");
  }
  /* Maximum size as specified in WM_NORMAL_HINTS */
  KWINPP_EXPORT SizeF maxSize() const {
    return kwinpp_internal::call_kwin_func<SizeF>(kwinpp_internal::ref_of(this),
                                                  "Window.maxSize");
  }
  /* Whether the Window can accept keyboard focus. The value is evaluated each
   * time the getter is called. Because of that no changed signal is provided.
   */
  KWINPP_EXPORT bool wantsInput() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.wantsInput");
  }
  /* Whether the Window is a transient Window to another Window. transientFor */
  KWINPP_EXPORT bool transient() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.transient");
  }
  /* The Window to which this Window is a transient if any. */
  KWINPP_EXPORT KWin::Window *transientFor() const {
    return kwinpp_internal::call_kwin_func<KWin::Window *>(
        kwinpp_internal::ref_of(this), "Window.transientFor");
  }
  /* Whether the Window represents a modal window. */
  KWINPP_EXPORT bool modal() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.modal");
  }
  /* Whether the Window is currently being moved by the user. Notify signal is
   * emitted when the Window starts or ends move/resize mode. */
  KWINPP_EXPORT bool move() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.move");
  }
  /* Whether the Window is currently being resized by the user. Notify signal is
   * emitted when the Window starts or ends move/resize mode. */
  KWINPP_EXPORT bool resize() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.resize");
  }
  /* Whether the decoration is currently using an alpha channel. */
  KWINPP_EXPORT bool decorationHasAlpha() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.decorationHasAlpha");
  }
  /* Whether the Window provides context help. Mostly needed by decorations to
   * decide whether to show the help button or not. */
  KWINPP_EXPORT bool providesContextHelp() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.providesContextHelp");
  }
  /* Whether the Window can be maximized both horizontally and vertically. The
   * property is evaluated each time it is invoked. Because of that there is no
   * notify signal. */
  KWINPP_EXPORT bool maximizable() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.maximizable");
  }
  /* Whether the Window is movable. Even if it is not movable, it might be
   * possible to move it to another screen. The property is evaluated each time
   * it is invoked. Because of that there is no notify signal.
   * moveableAcrossScreens */
  KWINPP_EXPORT bool moveable() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.moveable");
  }
  /* Whether the Window can be moved to another screen. The property is
   * evaluated each time it is invoked. Because of that there is no notify
   * signal. moveable */
  KWINPP_EXPORT bool moveableAcrossScreens() const {
    return kwinpp_internal::call_kwin_func<bool>(
        kwinpp_internal::ref_of(this), "Window.moveableAcrossScreens");
  }
  /* Whether the Window can be resized. The property is evaluated each time it
   * is invoked. Because of that there is no notify signal. */
  KWINPP_EXPORT bool resizeable() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.resizeable");
  }
  /* The desktop file name of the application this Window belongs to. This is
   * either the base name without full path and without file extension of the
   * desktop file for the window's application (e.g. "org.kde.foo"). The
   * application's desktop file name can also be the full path to the desktop
   * file (e.g. "/opt/kde/share/org.kde.foo.desktop") in case it's not in a
   * standard location. */
  KWINPP_EXPORT String desktopFileName() const {
    return kwinpp_internal::call_kwin_func<String>(
        kwinpp_internal::ref_of(this), "Window.desktopFileName");
  }
  /* Whether an application menu is available for this Window */
  KWINPP_EXPORT bool hasApplicationMenu() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.hasApplicationMenu");
  }
  /* Whether the application menu for this Window is currently opened */
  KWINPP_EXPORT bool applicationMenuActive() const {
    return kwinpp_internal::call_kwin_func<bool>(
        kwinpp_internal::ref_of(this), "Window.applicationMenuActive");
  }
  /* Whether this window is unresponsive. When an application failed to react on
   * a ping request in time, it is considered unresponsive. This usually
   * indicates that the application froze or crashed. */
  KWINPP_EXPORT bool unresponsive() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.unresponsive");
  }
  /* The color scheme set on this window Absolute file path, or name of palette
   * in the user's config directory following KColorSchemes format. An empty
   * string indicates the default palette from kdeglobals is used. this
   * indicates the colour scheme requested, which might differ from the theme
   * applied if the colorScheme cannot be found */
  KWINPP_EXPORT String colorScheme() const {
    return kwinpp_internal::call_kwin_func<String>(
        kwinpp_internal::ref_of(this), "Window.colorScheme");
  }

  // undocumented/C++ scripting only type
  // KWin::Layer layer() const;

  /* Whether this window is hidden. It's usually the case with auto-hide panels.
   */
  KWINPP_EXPORT bool hidden() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.hidden");
  }
  /* Returns whether this window is a input method window. This is only used for
   * Wayland. */
  KWINPP_EXPORT bool inputMethod() const {
    return kwinpp_internal::call_kwin_func<bool>(kwinpp_internal::ref_of(this),
                                                 "Window.inputMethod");
  }

  KWINPP_EXPORT double opacity() {
    return kwinpp_internal::get_kwin_field<double>(
        kwinpp_internal::ref_of(this), "opacity");
  }
  KWINPP_EXPORT void setOpacity(double value) {
    return kwinpp_internal::set_kwin_field(kwinpp_internal::ref_of(this),
                                           "opacity", value);
  }
  /* Whether the window does not want to be animated on window close. There are
   * legit reasons for this like a screenshot application which does not want
   * it's window being captured. */
  KWINPP_EXPORT bool skipsCloseAnimation() {
    return kwinpp_internal::get_kwin_field<bool>(kwinpp_internal::ref_of(this),
                                                 "skipsCloseAnimation");
  }
  KWINPP_EXPORT void setSkipsCloseAnimation(bool value) {
    return kwinpp_internal::set_kwin_field(kwinpp_internal::ref_of(this),
                                           "skipsCloseAnimation", value);
  }
  /* Whether this Window is fullScreen. A Window might either be fullScreen due
   * to the _NET_WM property or through a legacy support hack. The fullScreen
   * state can only be changed if the Window does not use the legacy hack. To be
   * sure whether the state changed, connect to the notify signal. */
  KWINPP_EXPORT bool fullScreen() {
    return kwinpp_internal::get_kwin_field<bool>(kwinpp_internal::ref_of(this),
                                                 "fullScreen");
  }
  KWINPP_EXPORT void setFullScreen(bool value) {
    return kwinpp_internal::set_kwin_field(kwinpp_internal::ref_of(this),
                                           "fullScreen", value);
  }
  /* The virtual desktops this client is on. If it's on all desktops, the list
   * is empty. */
  KWINPP_EXPORT List<KWin::VirtualDesktop *> desktops() {
    return kwinpp_internal::get_kwin_field<List<KWin::VirtualDesktop *>>(
        kwinpp_internal::ref_of(this), "desktops");
  }
  KWINPP_EXPORT void setDesktops(List<KWin::VirtualDesktop *> value) {
    return kwinpp_internal::set_kwin_field(kwinpp_internal::ref_of(this),
                                           "desktops", value);
  }
  /* Whether the Window is on all desktops. That is desktop is -1. */
  KWINPP_EXPORT bool onAllDesktops() {
    return kwinpp_internal::get_kwin_field<bool>(kwinpp_internal::ref_of(this),
                                                 "onAllDesktops");
  }
  KWINPP_EXPORT void setOnAllDesktops(bool value) {
    return kwinpp_internal::set_kwin_field(kwinpp_internal::ref_of(this),
                                           "onAllDesktops", value);
  }
  /* The activities this client is on. If it's on all activities the property is
   * empty. */
  KWINPP_EXPORT StringList activities() {
    return kwinpp_internal::get_kwin_field<StringList>(
        kwinpp_internal::ref_of(this), "activities");
  }
  KWINPP_EXPORT void setActivities(StringList value) {
    return kwinpp_internal::set_kwin_field(kwinpp_internal::ref_of(this),
                                           "activities", value);
  }
  /* Indicates that the window should not be included on a taskbar. */
  KWINPP_EXPORT bool skipTaskbar() {
    return kwinpp_internal::get_kwin_field<bool>(kwinpp_internal::ref_of(this),
                                                 "skipTaskbar");
  }
  KWINPP_EXPORT void setSkipTaskbar(bool value) {
    return kwinpp_internal::set_kwin_field(kwinpp_internal::ref_of(this),
                                           "skipTaskbar", value);
  }
  /* Indicates that the window should not be included on a Pager. */
  KWINPP_EXPORT bool skipPager() {
    return kwinpp_internal::get_kwin_field<bool>(kwinpp_internal::ref_of(this),
                                                 "skipPager");
  }
  KWINPP_EXPORT void setSkipPager(bool value) {
    return kwinpp_internal::set_kwin_field(kwinpp_internal::ref_of(this),
                                           "skipPager", value);
  }
  /* Whether the Window should be excluded from window switching effects. */
  KWINPP_EXPORT bool skipSwitcher() {
    return kwinpp_internal::get_kwin_field<bool>(kwinpp_internal::ref_of(this),
                                                 "skipSwitcher");
  }
  KWINPP_EXPORT void setSkipSwitcher(bool value) {
    return kwinpp_internal::set_kwin_field(kwinpp_internal::ref_of(this),
                                           "skipSwitcher", value);
  }
  /* Whether the Window is set to be kept above other windows. */
  KWINPP_EXPORT bool keepAbove() {
    return kwinpp_internal::get_kwin_field<bool>(kwinpp_internal::ref_of(this),
                                                 "keepAbove");
  }
  KWINPP_EXPORT void setKeepAbove(bool value) {
    return kwinpp_internal::set_kwin_field(kwinpp_internal::ref_of(this),
                                           "keepAbove", value);
  }
  /* Whether the Window is set to be kept below other windows. */
  KWINPP_EXPORT bool keepBelow() {
    return kwinpp_internal::get_kwin_field<bool>(kwinpp_internal::ref_of(this),
                                                 "keepBelow");
  }
  KWINPP_EXPORT void setKeepBelow(bool value) {
    return kwinpp_internal::set_kwin_field(kwinpp_internal::ref_of(this),
                                           "keepBelow", value);
  }
  /* Whether the Window is shaded. */
  KWINPP_EXPORT bool shade() {
    return kwinpp_internal::get_kwin_field<bool>(kwinpp_internal::ref_of(this),
                                                 "shade");
  }
  KWINPP_EXPORT void setShade(bool value) {
    return kwinpp_internal::set_kwin_field(kwinpp_internal::ref_of(this),
                                           "shade", value);
  }
  /* Whether the Window is minimized. */
  KWINPP_EXPORT bool minimized() {
    return kwinpp_internal::get_kwin_field<bool>(kwinpp_internal::ref_of(this),
                                                 "minimized");
  }
  KWINPP_EXPORT void setMinimized(bool value) {
    return kwinpp_internal::set_kwin_field(kwinpp_internal::ref_of(this),
                                           "minimized", value);
  }
  /* Whether window state _NET_WM_STATE_DEMANDS_ATTENTION is set. This state
   * indicates that some action in or with the window happened. For example, it
   * may be set by the Window Manager if the window requested activation but the
   * Window Manager refused it, or the application may set it if it finished
   * some work. This state may be set by both the Window and the Window Manager.
   * It should be unset by the Window Manager when it decides the window got the
   * required attention (usually, that it got activated). */
  KWINPP_EXPORT bool demandsAttention() {
    return kwinpp_internal::get_kwin_field<bool>(kwinpp_internal::ref_of(this),
                                                 "demandsAttention");
  }
  KWINPP_EXPORT void setDemandsAttention(bool value) {
    return kwinpp_internal::set_kwin_field(kwinpp_internal::ref_of(this),
                                           "demandsAttention", value);
  }
  /* The geometry of this Window. Be aware that depending on resize mode the
   * frameGeometryChanged signal might be emitted at each resize step or only at
   * the end of the resize operation. */
  KWINPP_EXPORT RectF frameGeometry() {
    return kwinpp_internal::get_kwin_field<RectF>(kwinpp_internal::ref_of(this),
                                                  "frameGeometry");
  }
  KWINPP_EXPORT void setFrameGeometry(RectF value) {
    return kwinpp_internal::set_kwin_field(kwinpp_internal::ref_of(this),
                                           "frameGeometry", value);
  }
  /* Whether the window has a decoration or not. This property is not allowed to
   * be set by applications themselves. The decision whether a window has a
   * border or not belongs to the window manager. If this property gets abused
   * by application developers, it will be removed again. */
  KWINPP_EXPORT bool noBorder() {
    return kwinpp_internal::get_kwin_field<bool>(kwinpp_internal::ref_of(this),
                                                 "noBorder");
  }
  KWINPP_EXPORT void setNoBorder(bool value) {
    return kwinpp_internal::set_kwin_field(kwinpp_internal::ref_of(this),
                                           "noBorder", value);
  }
  /* The Tile this window is associated to, if any */
  KWINPP_EXPORT KWin::Tile *tile() {
    return kwinpp_internal::get_kwin_field<KWin::Tile *>(
        kwinpp_internal::ref_of(this), "tile");
  }
  KWINPP_EXPORT void setTile(KWin::Tile *value) {
    return kwinpp_internal::set_kwin_field(kwinpp_internal::ref_of(this),
                                           "tile", value);
  }

  KWINPP_EXPORT kwinpp::Connection
  onStackingOrderChanged(std::function<void()> callback) {

    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "stackingOrderChanged",

                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onShadeChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "shadeChanged", std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection onOpacityChanged(
      std::function<void(KWin::Window *window, double oldOpacity)> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "opacityChanged", std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onDamaged(std::function<void(KWin::Window *window)> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "damaged", std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onInputTransformationChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "inputTransformationChanged",
                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection onClosed(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "closed", std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onWindowShown(std::function<void(KWin::Window *window)> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "windowShown", std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onWindowHidden(std::function<void(KWin::Window *window)> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "windowHidden", std::move(callback));
  }
  /* Emitted whenever the Window's screen changes. This can happen either in
   * consequence to a screen being removed/added or if the Window's geometry
   * changes. */
  KWINPP_EXPORT kwinpp::Connection
  onOutputChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "outputChanged", std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onSkipCloseAnimationChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "skipCloseAnimationChanged",
                                                std::move(callback));
  }
  /* Emitted whenever the window role of the window changes. */
  KWINPP_EXPORT kwinpp::Connection
  onWindowRoleChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "windowRoleChanged",
                                                std::move(callback));
  }
  /* Emitted whenever the window class name or resource name of the window
   * changes.  */
  KWINPP_EXPORT kwinpp::Connection
  onWindowClassChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "windowClassChanged",
                                                std::move(callback));
  }
  /* Emitted whenever the Surface for this Window changes. */
  KWINPP_EXPORT kwinpp::Connection
  onSurfaceChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "surfaceChanged", std::move(callback));
  }
  /* Emitted whenever the window's shadow changes. */
  KWINPP_EXPORT kwinpp::Connection
  onShadowChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "shadowChanged", std::move(callback));
  }
  /* This signal is emitted when the Window's buffer geometry changes. */
  KWINPP_EXPORT kwinpp::Connection onBufferGeometryChanged(
      std::function<void(const RectF &oldGeometry)> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "bufferGeometryChanged",
                                                std::move(callback));
  }
  /* This signal is emitted when the Window's frame geometry changes. */
  KWINPP_EXPORT kwinpp::Connection onFrameGeometryChanged(
      std::function<void(const RectF &oldGeometry)> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "frameGeometryChanged",
                                                std::move(callback));
  }
  /* This signal is emitted when the Window's client geometry has changed. */
  KWINPP_EXPORT kwinpp::Connection onClientGeometryChanged(
      std::function<void(const RectF &oldGeometry)> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "clientGeometryChanged",
                                                std::move(callback));
  }
  /* This signal is emitted when the frame geometry is about to change. the new
   * geometry is not known yet */
  KWINPP_EXPORT kwinpp::Connection
  onFrameGeometryAboutToChange(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "frameGeometryAboutToChange",
                                                std::move(callback));
  }
  /* This signal is emitted when the visible geometry has changed. */
  KWINPP_EXPORT kwinpp::Connection
  onVisibleGeometryChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "visibleGeometryChanged",
                                                std::move(callback));
  }
  /* This signal is emitted when associated tile has changed, including from and
   * to none */
  KWINPP_EXPORT kwinpp::Connection
  onTileChanged(std::function<void(KWin::Tile *tile)> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "tileChanged", std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onFullScreenChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "fullScreenChanged",
                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onSkipTaskbarChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "skipTaskbarChanged",
                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onSkipPagerChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "skipPagerChanged", std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onSkipSwitcherChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "skipSwitcherChanged",
                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onIconChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "iconChanged", std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onActiveChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "activeChanged", std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onKeepAboveChanged(std::function<void(bool)> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "keepAboveChanged", std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onKeepBelowChanged(std::function<void(bool)> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "keepBelowChanged", std::move(callback));
  }
  /* Emitted whenever the demands attention state changes. */
  KWINPP_EXPORT kwinpp::Connection
  onDemandsAttentionChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "demandsAttentionChanged",
                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onDesktopsChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "desktopsChanged", std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onActivitiesChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "activitiesChanged",
                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onMinimizedChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "minimizedChanged", std::move(callback));
  }
#ifndef KWINPP_NO_QT // no std equivalent for QPalette
  KWINPP_EXPORT kwinpp::Connection
  onPaletteChanged(std::function<void(const QPalette &p)> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "paletteChanged", std::move(callback));
  }
#endif
  KWINPP_EXPORT kwinpp::Connection
  onColorSchemeChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "colorSchemeChanged",
                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onCaptionChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "captionChanged", std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onCaptionNormalChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "captionNormalChanged",
                                                std::move(callback));
  }
  // void onMaximizedAboutToChange(std::function<void(MaximizeMode mode)>
  // callback);
  KWINPP_EXPORT kwinpp::Connection
  onMaximizedChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "maximizedChanged", std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onTransientChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "transientChanged", std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onModalChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "modalChanged", std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onQuickTileModeChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "quickTileModeChanged",
                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onMoveResizedChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "moveResizedChanged",
                                                std::move(callback));
  }
  // void onMoveResizeCursorChanged(std::function<void(CursorShape)> callback);
  KWINPP_EXPORT kwinpp::Connection
  onInteractiveMoveResizeStarted(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "interactiveMoveResizeStarted",
                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection onInteractiveMoveResizeStepped(
      std::function<void(const RectF &geometry)> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "interactiveMoveResizeStepped",
                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onInteractiveMoveResizeFinished(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "interactiveMoveResizeFinished",
                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onCloseableChanged(std::function<void(bool)> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "closeableChanged", std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onMinimizeableChanged(std::function<void(bool)> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "minimizeableChanged",
                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onShadeableChanged(std::function<void(bool)> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "shadeableChanged", std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onMaximizeableChanged(std::function<void(bool)> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "maximizeableChanged",
                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onDesktopFileNameChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "desktopFileNameChanged",
                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onApplicationMenuChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "applicationMenuChanged",
                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onHasApplicationMenuChanged(std::function<void(bool)> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "hasApplicationMenuChanged",
                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onApplicationMenuActiveChanged(std::function<void(bool)> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "applicationMenuActiveChanged",
                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onUnresponsiveChanged(std::function<void(bool)> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "unresponsiveChanged",
                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onDecorationChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "decorationChanged",
                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onHiddenChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "hiddenChanged", std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onHiddenByShowDesktopChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "hiddenByShowDesktopChanged",
                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onLockScreenOverlayChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "lockScreenOverlayChanged",
                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onReadyForPaintingChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "readyForPaintingChanged",
                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onMaximizeGeometryRestoreChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "maximizeGeometryRestoreChanged",
        std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onFullscreenGeometryRestoreChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "fullscreenGeometryRestoreChanged",
        std::move(callback));
  }

  KWINPP_EXPORT void closeWindow() {
    return kwinpp_internal::call_kwin_func<void>(kwinpp_internal::ref_of(this),
                                                 "Window.closeWindow");
  }
  /* Sets the maximization according to vertically and horizontally. */
  KWINPP_EXPORT void setMaximize(bool vertically, bool horizontally) {
    return kwinpp_internal::call_kwin_func<void>(kwinpp_internal::ref_of(this),
                                                 "Window.setMaximize",
                                                 vertically, horizontally);
  }
};

class TileManager {
public:
  KWINPP_EXPORT ~TileManager() { kwinpp_internal::release_handle(this); }

  KWINPP_EXPORT KWin::Tile *rootTile() {
    return kwinpp_internal::call_kwin_func<KWin::Tile *>(
        kwinpp_internal::ref_of(this), "TileManager.rootTile");
  }

  // undocumented/C++ scripting only type
  // TileModel *model();

  KWINPP_EXPORT kwinpp::Connection
  onTileRemoved(std::function<void(KWin::Tile *tile)> callback) {

    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "tileRemoved",

                                                std::move(callback));
  }

  KWINPP_EXPORT KWin::Tile *bestTileForPosition(double x, double y) {
    return kwinpp_internal::call_kwin_func<KWin::Tile *>(
        kwinpp_internal::ref_of(this), "TileManager.bestTileForPosition", x, y);
  }
};
class Tile {
public:
  KWINPP_EXPORT ~Tile() { kwinpp_internal::release_handle(this); }

  enum class LayoutDirection {
    Floating,
    Horizontal,
    Vertical,
  };

  KWINPP_EXPORT const RectF absoluteGeometry() {
    return kwinpp_internal::call_kwin_func<const RectF>(
        kwinpp_internal::ref_of(this), "Tile.absoluteGeometry");
  }
  KWINPP_EXPORT const RectF absoluteGeometryInScreen() {
    return kwinpp_internal::call_kwin_func<const RectF>(
        kwinpp_internal::ref_of(this), "Tile.absoluteGeometryInScreen");
  }
  KWINPP_EXPORT const int positionInLayout() {
    return kwinpp_internal::call_kwin_func<const int>(
        kwinpp_internal::ref_of(this), "Tile.positionInLayout");
  }
  KWINPP_EXPORT const Tile *parent() {
    return kwinpp_internal::call_kwin_func<const Tile *>(
        kwinpp_internal::ref_of(this), "Tile.parent");
  }
  KWINPP_EXPORT const List<KWin::Tile *> tiles() {
    return kwinpp_internal::call_kwin_func<const List<KWin::Tile *>>(
        kwinpp_internal::ref_of(this), "Tile.tiles");
  }
  KWINPP_EXPORT const List<KWin::Window *> windows() {
    return kwinpp_internal::call_kwin_func<const List<KWin::Window *>>(
        kwinpp_internal::ref_of(this), "Tile.windows");
  }
  KWINPP_EXPORT const bool isLayout() {
    return kwinpp_internal::call_kwin_func<const bool>(
        kwinpp_internal::ref_of(this), "Tile.isLayout");
  }
  KWINPP_EXPORT const bool canBeRemoved() {
    return kwinpp_internal::call_kwin_func<const bool>(
        kwinpp_internal::ref_of(this), "Tile.canBeRemoved");
  }

  KWINPP_EXPORT RectF relativeGeometry() {
    return kwinpp_internal::get_kwin_field<RectF>(kwinpp_internal::ref_of(this),
                                                  "relativeGeometry");
  }
  KWINPP_EXPORT void setRelativeGeometry(RectF value) {
    return kwinpp_internal::set_kwin_field(kwinpp_internal::ref_of(this),
                                           "relativeGeometry", value);
  }
  KWINPP_EXPORT double padding() {
    return kwinpp_internal::get_kwin_field<double>(
        kwinpp_internal::ref_of(this), "padding");
  }
  KWINPP_EXPORT void setPadding(double value) {
    return kwinpp_internal::set_kwin_field(kwinpp_internal::ref_of(this),
                                           "padding", value);
  }

  KWINPP_EXPORT kwinpp::Connection
  onRelativeGeometryChanged(std::function<void()> callback) {

    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "relativeGeometryChanged",

                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onAbsoluteGeometryChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "absoluteGeometryChanged",
                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onWindowGeometryChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "windowGeometryChanged",
                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onPaddingChanged(std::function<void(double padding)> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "paddingChanged", std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onRowChanged(std::function<void(int row)> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "rowChanged", std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onIsLayoutChanged(std::function<void(bool isLayout)> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "isLayoutChanged", std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onChildTilesChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(kwinpp_internal::ref_of(this),
                                                "childTilesChanged",
                                                std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onWindowAdded(std::function<void(Window *window)> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "windowAdded", std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onWindowRemoved(std::function<void(Window *window)> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "windowRemoved", std::move(callback));
  }
  KWINPP_EXPORT kwinpp::Connection
  onWindowsChanged(std::function<void()> callback) {
    return kwinpp_internal::connect_kwin_signal(
        kwinpp_internal::ref_of(this), "windowsChanged", std::move(callback));
  }

  KWINPP_EXPORT void resizeByPixels(double delta, Edge edge) {
    return kwinpp_internal::call_kwin_func<void>(
        kwinpp_internal::ref_of(this), "Tile.resizeByPixels", delta, edge);
  }
};
} // namespace KWin
