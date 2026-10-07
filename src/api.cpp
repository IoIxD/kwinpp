// Definitions for the API in kwinpp.hpp. Each one forwards to the matching
// entry of the KWin script's api table (see kwinpp.cpp).

#include "kwinpp.hpp"
#include "kwinppi.hpp"

using kwinpp_internal::call_kwin_func;
using kwinpp_internal::ref_of;

namespace KWin {

const QList<KWin::VirtualDesktop *> WorkspaceWrapper::desktops() {
  return call_kwin_func<const QList<KWin::VirtualDesktop *>>(
      "workspace", "WorkspaceWrapper.desktops");
}
const QSize WorkspaceWrapper::desktopGridSize() {
  return call_kwin_func<const QSize>("workspace",
                                     "WorkspaceWrapper.desktopGridSize");
}
const int WorkspaceWrapper::desktopGridWidth() {
  return call_kwin_func<const int>("workspace",
                                   "WorkspaceWrapper.desktopGridWidth");
}
const int WorkspaceWrapper::desktopGridHeight() {
  return call_kwin_func<const int>("workspace",
                                   "WorkspaceWrapper.desktopGridHeight");
}
const int WorkspaceWrapper::workspaceWidth() {
  return call_kwin_func<const int>("workspace",
                                   "WorkspaceWrapper.workspaceWidth");
}
const int WorkspaceWrapper::workspaceHeight() {
  return call_kwin_func<const int>("workspace",
                                   "WorkspaceWrapper.workspaceHeight");
}
const QSize WorkspaceWrapper::workspaceSize() {
  return call_kwin_func<const QSize>("workspace",
                                     "WorkspaceWrapper.workspaceSize");
}
const KWin::Output *WorkspaceWrapper::activeScreen() {
  return call_kwin_func<const KWin::Output *>("workspace",
                                              "WorkspaceWrapper.activeScreen");
}
const QList<KWin::Output *> WorkspaceWrapper::screens() {
  return call_kwin_func<const QList<KWin::Output *>>(
      "workspace", "WorkspaceWrapper.screens");
}
const QStringList WorkspaceWrapper::activities() {
  return call_kwin_func<const QStringList>("workspace",
                                           "WorkspaceWrapper.activities");
}
const QSize WorkspaceWrapper::virtualScreenSize() {
  return call_kwin_func<const QSize>("workspace",
                                     "WorkspaceWrapper.virtualScreenSize");
}
const QRect WorkspaceWrapper::virtualScreenGeometry() {
  return call_kwin_func<const QRect>("workspace",
                                     "WorkspaceWrapper.virtualScreenGeometry");
}
const QList<KWin::Window *> WorkspaceWrapper::stackingOrder() {
  return call_kwin_func<const QList<KWin::Window *>>(
      "workspace", "WorkspaceWrapper.stackingOrder");
}
QPoint WorkspaceWrapper::cursorPos() {
  return call_kwin_func<QPoint>("workspace", "WorkspaceWrapper.cursorPos");
}
KWin::VirtualDesktop *WorkspaceWrapper::currentDesktop() {
  return call_kwin_func<KWin::VirtualDesktop *>(
      "workspace", "WorkspaceWrapper.currentDesktop");
}
void WorkspaceWrapper::setCurrentDesktop(KWin::VirtualDesktop *val) {
  return call_kwin_func<void>("workspace", "WorkspaceWrapper.setCurrentDesktop",
                              val);
}
KWin::Window *WorkspaceWrapper::activeWindow() {
  return call_kwin_func<KWin::Window *>("workspace",
                                        "WorkspaceWrapper.activeWindow");
}
void WorkspaceWrapper::setActiveWindow(KWin::Window *val) {
  return call_kwin_func<void>("workspace", "WorkspaceWrapper.setActiveWindow",
                              val);
}
QString WorkspaceWrapper::currentActivity() {
  return call_kwin_func<QString>("workspace",
                                 "WorkspaceWrapper.currentActivity");
}
void WorkspaceWrapper::setCurrentActivity(QString val) {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.setCurrentActivity", val);
}
void WorkspaceWrapper::slotSwitchDesktopNext() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotSwitchDesktopNext");
}
void WorkspaceWrapper::slotSwitchDesktopPrevious() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotSwitchDesktopPrevious");
}
void WorkspaceWrapper::slotSwitchDesktopRight() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotSwitchDesktopRight");
}
void WorkspaceWrapper::slotSwitchDesktopLeft() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotSwitchDesktopLeft");
}
void WorkspaceWrapper::slotSwitchDesktopUp() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotSwitchDesktopUp");
}
void WorkspaceWrapper::slotSwitchDesktopDown() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotSwitchDesktopDown");
}
void WorkspaceWrapper::slotSwitchToNextScreen() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotSwitchToNextScreen");
}
void WorkspaceWrapper::slotSwitchToPrevScreen() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotSwitchToPrevScreen");
}
void WorkspaceWrapper::slotSwitchToRightScreen() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotSwitchToRightScreen");
}
void WorkspaceWrapper::slotSwitchToLeftScreen() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotSwitchToLeftScreen");
}
void WorkspaceWrapper::slotSwitchToAboveScreen() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotSwitchToAboveScreen");
}
void WorkspaceWrapper::slotSwitchToBelowScreen() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotSwitchToBelowScreen");
}
void WorkspaceWrapper::slotWindowToNextScreen() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotWindowToNextScreen");
}
void WorkspaceWrapper::slotWindowToPrevScreen() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotWindowToPrevScreen");
}
void WorkspaceWrapper::slotWindowToRightScreen() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotWindowToRightScreen");
}
void WorkspaceWrapper::slotWindowToLeftScreen() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotWindowToLeftScreen");
}
void WorkspaceWrapper::slotWindowToAboveScreen() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotWindowToAboveScreen");
}
void WorkspaceWrapper::slotWindowToBelowScreen() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotWindowToBelowScreen");
}
void WorkspaceWrapper::slotToggleShowDesktop() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotToggleShowDesktop");
}
void WorkspaceWrapper::slotWindowMaximize() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotWindowMaximize");
}
void WorkspaceWrapper::slotWindowMaximizeVertical() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotWindowMaximizeVertical");
}
void WorkspaceWrapper::slotWindowMaximizeHorizontal() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotWindowMaximizeHorizontal");
}
void WorkspaceWrapper::slotWindowMinimize() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotWindowMinimize");
}
void WorkspaceWrapper::slotWindowShade() {
  return call_kwin_func<void>("workspace", "WorkspaceWrapper.slotWindowShade");
}
void WorkspaceWrapper::slotWindowRaise() {
  return call_kwin_func<void>("workspace", "WorkspaceWrapper.slotWindowRaise");
}
void WorkspaceWrapper::slotWindowLower() {
  return call_kwin_func<void>("workspace", "WorkspaceWrapper.slotWindowLower");
}
void WorkspaceWrapper::slotWindowRaiseOrLower() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotWindowRaiseOrLower");
}
void WorkspaceWrapper::slotActivateAttentionWindow() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotActivateAttentionWindow");
}
void WorkspaceWrapper::slotWindowMoveLeft() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotWindowMoveLeft");
}
void WorkspaceWrapper::slotWindowMoveRight() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotWindowMoveRight");
}
void WorkspaceWrapper::slotWindowMoveUp() {
  return call_kwin_func<void>("workspace", "WorkspaceWrapper.slotWindowMoveUp");
}
void WorkspaceWrapper::slotWindowMoveDown() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotWindowMoveDown");
}
void WorkspaceWrapper::slotWindowExpandHorizontal() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotWindowExpandHorizontal");
}
void WorkspaceWrapper::slotWindowExpandVertical() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotWindowExpandVertical");
}
void WorkspaceWrapper::slotWindowShrinkHorizontal() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotWindowShrinkHorizontal");
}
void WorkspaceWrapper::slotWindowShrinkVertical() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotWindowShrinkVertical");
}
void WorkspaceWrapper::slotWindowQuickTileLeft() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotWindowQuickTileLeft");
}
void WorkspaceWrapper::slotWindowQuickTileRight() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotWindowQuickTileRight");
}
void WorkspaceWrapper::slotWindowQuickTileTop() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotWindowQuickTileTop");
}
void WorkspaceWrapper::slotWindowQuickTileBottom() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotWindowQuickTileBottom");
}
void WorkspaceWrapper::slotWindowQuickTileTopLeft() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotWindowQuickTileTopLeft");
}
void WorkspaceWrapper::slotWindowQuickTileTopRight() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotWindowQuickTileTopRight");
}
void WorkspaceWrapper::slotWindowQuickTileBottomLeft() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotWindowQuickTileBottomLeft");
}
void WorkspaceWrapper::slotWindowQuickTileBottomRight() {
  return call_kwin_func<void>(
      "workspace", "WorkspaceWrapper.slotWindowQuickTileBottomRight");
}
void WorkspaceWrapper::slotSwitchWindowUp() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotSwitchWindowUp");
}
void WorkspaceWrapper::slotSwitchWindowDown() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotSwitchWindowDown");
}
void WorkspaceWrapper::slotSwitchWindowRight() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotSwitchWindowRight");
}
void WorkspaceWrapper::slotSwitchWindowLeft() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotSwitchWindowLeft");
}
void WorkspaceWrapper::slotIncreaseWindowOpacity() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotIncreaseWindowOpacity");
}
void WorkspaceWrapper::slotLowerWindowOpacity() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotLowerWindowOpacity");
}
void WorkspaceWrapper::slotWindowOperations() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotWindowOperations");
}
void WorkspaceWrapper::slotWindowClose() {
  return call_kwin_func<void>("workspace", "WorkspaceWrapper.slotWindowClose");
}
void WorkspaceWrapper::slotWindowMove() {
  return call_kwin_func<void>("workspace", "WorkspaceWrapper.slotWindowMove");
}
void WorkspaceWrapper::slotWindowResize() {
  return call_kwin_func<void>("workspace", "WorkspaceWrapper.slotWindowResize");
}
void WorkspaceWrapper::slotWindowAbove() {
  return call_kwin_func<void>("workspace", "WorkspaceWrapper.slotWindowAbove");
}
void WorkspaceWrapper::slotWindowBelow() {
  return call_kwin_func<void>("workspace", "WorkspaceWrapper.slotWindowBelow");
}
void WorkspaceWrapper::slotWindowOnAllDesktops() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotWindowOnAllDesktops");
}
void WorkspaceWrapper::slotWindowFullScreen() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotWindowFullScreen");
}
void WorkspaceWrapper::slotWindowNoBorder() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotWindowNoBorder");
}
void WorkspaceWrapper::slotWindowToNextDesktop() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotWindowToNextDesktop");
}
void WorkspaceWrapper::slotWindowToPreviousDesktop() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotWindowToPreviousDesktop");
}
void WorkspaceWrapper::slotWindowToDesktopRight() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotWindowToDesktopRight");
}
void WorkspaceWrapper::slotWindowToDesktopLeft() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotWindowToDesktopLeft");
}
void WorkspaceWrapper::slotWindowToDesktopUp() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotWindowToDesktopUp");
}
void WorkspaceWrapper::slotWindowToDesktopDown() {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.slotWindowToDesktopDown");
}
void WorkspaceWrapper::sendClientToScreen(KWin::Window *client,
                                          KWin::Output *output) {
  return call_kwin_func<void>(
      "workspace", "WorkspaceWrapper.sendClientToScreen", client, output);
}
void WorkspaceWrapper::showOutline(const QRect &geometry) {
  return call_kwin_func<void>("workspace", "WorkspaceWrapper.showOutline",
                              geometry);
}
void WorkspaceWrapper::showOutline(int x, int y, int width, int height) {
  return call_kwin_func<void>("workspace", "WorkspaceWrapper.showOutline", x, y,
                              width, height);
}
void WorkspaceWrapper::hideOutline() {
  return call_kwin_func<void>("workspace", "WorkspaceWrapper.hideOutline");
}
KWin::VirtualDesktop *
WorkspaceWrapper::currentDesktopForScreen(KWin::Output *output) const {
  return call_kwin_func<KWin::VirtualDesktop *>(
      "workspace", "WorkspaceWrapper.currentDesktopForScreen", output);
}
void WorkspaceWrapper::setCurrentDesktopForScreen(KWin::VirtualDesktop *desktop,
                                                  KWin::Output *output) {
  return call_kwin_func<void>("workspace",
                              "WorkspaceWrapper.setCurrentDesktopForScreen",
                              desktop, output);
}
KWin::Output *WorkspaceWrapper::screenAt(const QPointF &pos) const {
  return call_kwin_func<KWin::Output *>("workspace",
                                        "WorkspaceWrapper.screenAt", pos);
}
KWin::TileManager *
WorkspaceWrapper::tilingForScreen(const QString &screenName) const {
  return call_kwin_func<KWin::TileManager *>(
      "workspace", "WorkspaceWrapper.tilingForScreen", screenName);
}
KWin::TileManager *
WorkspaceWrapper::tilingForScreen(KWin::Output *output) const {
  return call_kwin_func<KWin::TileManager *>(
      "workspace", "WorkspaceWrapper.tilingForScreen", output);
}
QRectF WorkspaceWrapper::clientArea(ClientAreaOption option,
                                    KWin::Output *output,
                                    KWin::VirtualDesktop *desktop) const {
  return call_kwin_func<QRectF>("workspace", "WorkspaceWrapper.clientArea",
                                option, output, desktop);
}
QRectF WorkspaceWrapper::clientArea(ClientAreaOption option,
                                    KWin::Window *client) const {
  return call_kwin_func<QRectF>("workspace", "WorkspaceWrapper.clientArea",
                                option, client);
}
QRectF WorkspaceWrapper::clientArea(ClientAreaOption option,
                                    const KWin::Window *client) const {
  return call_kwin_func<QRectF>("workspace", "WorkspaceWrapper.clientArea",
                                option, client);
}
void WorkspaceWrapper::createDesktop(int position, const QString &name) const {
  return call_kwin_func<void>("workspace", "WorkspaceWrapper.createDesktop",
                              position, name);
}
void WorkspaceWrapper::removeDesktop(KWin::VirtualDesktop *desktop) {
  return call_kwin_func<void>("workspace", "WorkspaceWrapper.removeDesktop",
                              desktop);
}
QString WorkspaceWrapper::supportInformation() const {
  return call_kwin_func<QString>("workspace",
                                 "WorkspaceWrapper.supportInformation");
}
void WorkspaceWrapper::raiseWindow(KWin::Window *window) {
  return call_kwin_func<void>("workspace", "WorkspaceWrapper.raiseWindow",
                              window);
}
KWin::Window *WorkspaceWrapper::getClient(qulonglong windowId) {
  return call_kwin_func<KWin::Window *>("workspace",
                                        "WorkspaceWrapper.getClient", windowId);
}
QList<KWin::Window *> WorkspaceWrapper::windowAt(const QPointF &pos,
                                                 int count) const {
  return call_kwin_func<QList<KWin::Window *>>(
      "workspace", "WorkspaceWrapper.windowAt", pos, count);
}
bool WorkspaceWrapper::isEffectActive(const QString &pluginId) const {
  return call_kwin_func<bool>("workspace", "WorkspaceWrapper.isEffectActive",
                              pluginId);
}

const QString VirtualDesktop::id() {
  return call_kwin_func<const QString>(ref_of(this), "VirtualDesktop.id");
}
const uint VirtualDesktop::x11DesktopNumber() {
  return call_kwin_func<const uint>(ref_of(this),
                                    "VirtualDesktop.x11DesktopNumber");
}
QString VirtualDesktop::name() {
  return call_kwin_func<QString>(ref_of(this), "VirtualDesktop.name");
}
void VirtualDesktop::setName(QString val) {
  return call_kwin_func<void>(ref_of(this), "VirtualDesktop.setName", val);
}

const QRect Output::geometry() {
  return call_kwin_func<const QRect>(ref_of(this), "Output.geometry");
}
const qreal Output::devicePixelRatio() {
  return call_kwin_func<const qreal>(ref_of(this), "Output.devicePixelRatio");
}
const QString Output::name() {
  return call_kwin_func<const QString>(ref_of(this), "Output.name");
}
const QString Output::manufacturer() {
  return call_kwin_func<const QString>(ref_of(this), "Output.manufacturer");
}
const QString Output::model() {
  return call_kwin_func<const QString>(ref_of(this), "Output.model");
}
const QString Output::serialNumber() {
  return call_kwin_func<const QString>(ref_of(this), "Output.serialNumber");
}
QPointF Output::mapToGlobal(const QPointF &pos) const {
  return call_kwin_func<QPointF>(ref_of(this), "Output.mapToGlobal", pos);
}
QPointF Output::mapFromGlobal(const QPointF &pos) const {
  return call_kwin_func<QPointF>(ref_of(this), "Output.mapFromGlobal", pos);
}

QRectF Window::bufferGeometry() const {
  return call_kwin_func<QRectF>(ref_of(this), "Window.bufferGeometry");
}
QRectF Window::clientGeometry() const {
  return call_kwin_func<QRectF>(ref_of(this), "Window.clientGeometry");
}
QPointF Window::pos() const {
  return call_kwin_func<QPointF>(ref_of(this), "Window.pos");
}
QSizeF Window::size() const {
  return call_kwin_func<QSizeF>(ref_of(this), "Window.size");
}
qreal Window::x() const {
  return call_kwin_func<qreal>(ref_of(this), "Window.x");
}
qreal Window::y() const {
  return call_kwin_func<qreal>(ref_of(this), "Window.y");
}
qreal Window::width() const {
  return call_kwin_func<qreal>(ref_of(this), "Window.width");
}
qreal Window::height() const {
  return call_kwin_func<qreal>(ref_of(this), "Window.height");
}
KWin::Output *Window::output() const {
  return call_kwin_func<KWin::Output *>(ref_of(this), "Window.output");
}
QRectF Window::rect() const {
  return call_kwin_func<QRectF>(ref_of(this), "Window.rect");
}
QString Window::resourceName() const {
  return call_kwin_func<QString>(ref_of(this), "Window.resourceName");
}
QString Window::resourceClass() const {
  return call_kwin_func<QString>(ref_of(this), "Window.resourceClass");
}
QString Window::windowRole() const {
  return call_kwin_func<QString>(ref_of(this), "Window.windowRole");
}
bool Window::desktopWindow() const {
  return call_kwin_func<bool>(ref_of(this), "Window.desktopWindow");
}
bool Window::dock() const {
  return call_kwin_func<bool>(ref_of(this), "Window.dock");
}
bool Window::toolbar() const {
  return call_kwin_func<bool>(ref_of(this), "Window.toolbar");
}
bool Window::menu() const {
  return call_kwin_func<bool>(ref_of(this), "Window.menu");
}
bool Window::normalWindow() const {
  return call_kwin_func<bool>(ref_of(this), "Window.normalWindow");
}
bool Window::dialog() const {
  return call_kwin_func<bool>(ref_of(this), "Window.dialog");
}
bool Window::splash() const {
  return call_kwin_func<bool>(ref_of(this), "Window.splash");
}
bool Window::utility() const {
  return call_kwin_func<bool>(ref_of(this), "Window.utility");
}
bool Window::dropdownMenu() const {
  return call_kwin_func<bool>(ref_of(this), "Window.dropdownMenu");
}
bool Window::popupMenu() const {
  return call_kwin_func<bool>(ref_of(this), "Window.popupMenu");
}
bool Window::tooltip() const {
  return call_kwin_func<bool>(ref_of(this), "Window.tooltip");
}
bool Window::notification() const {
  return call_kwin_func<bool>(ref_of(this), "Window.notification");
}
bool Window::criticalNotification() const {
  return call_kwin_func<bool>(ref_of(this), "Window.criticalNotification");
}
bool Window::appletPopup() const {
  return call_kwin_func<bool>(ref_of(this), "Window.appletPopup");
}
bool Window::onScreenDisplay() const {
  return call_kwin_func<bool>(ref_of(this), "Window.onScreenDisplay");
}
bool Window::comboBox() const {
  return call_kwin_func<bool>(ref_of(this), "Window.comboBox");
}
bool Window::dndIcon() const {
  return call_kwin_func<bool>(ref_of(this), "Window.dndIcon");
}
int Window::windowType() const {
  return call_kwin_func<int>(ref_of(this), "Window.windowType");
}
bool Window::managed() const {
  return call_kwin_func<bool>(ref_of(this), "Window.managed");
}
bool Window::deleted() const {
  return call_kwin_func<bool>(ref_of(this), "Window.deleted");
}
bool Window::popupWindow() const {
  return call_kwin_func<bool>(ref_of(this), "Window.popupWindow");
}
bool Window::outline() const {
  return call_kwin_func<bool>(ref_of(this), "Window.outline");
}
QUuid Window::internalId() const {
  return call_kwin_func<QUuid>(ref_of(this), "Window.internalId");
}
int Window::pid() const {
  return call_kwin_func<int>(ref_of(this), "Window.pid");
}
int Window::stackingOrder() const {
  return call_kwin_func<int>(ref_of(this), "Window.stackingOrder");
}
bool Window::fullScreenable() const {
  return call_kwin_func<bool>(ref_of(this), "Window.fullScreenable");
}
bool Window::active() const {
  return call_kwin_func<bool>(ref_of(this), "Window.active");
}
bool Window::closeable() const {
  return call_kwin_func<bool>(ref_of(this), "Window.closeable");
}
QIcon Window::icon() const {
  return call_kwin_func<QIcon>(ref_of(this), "Window.icon");
}
bool Window::shadeable() const {
  return call_kwin_func<bool>(ref_of(this), "Window.shadeable");
}
bool Window::minimizable() const {
  return call_kwin_func<bool>(ref_of(this), "Window.minimizable");
}
QRectF Window::iconGeometry() const {
  return call_kwin_func<QRectF>(ref_of(this), "Window.iconGeometry");
}
bool Window::specialWindow() const {
  return call_kwin_func<bool>(ref_of(this), "Window.specialWindow");
}
QString Window::caption() const {
  return call_kwin_func<QString>(ref_of(this), "Window.caption");
}
QSizeF Window::minSize() const {
  return call_kwin_func<QSizeF>(ref_of(this), "Window.minSize");
}
QSizeF Window::maxSize() const {
  return call_kwin_func<QSizeF>(ref_of(this), "Window.maxSize");
}
bool Window::wantsInput() const {
  return call_kwin_func<bool>(ref_of(this), "Window.wantsInput");
}
bool Window::transient() const {
  return call_kwin_func<bool>(ref_of(this), "Window.transient");
}
KWin::Window *Window::transientFor() const {
  return call_kwin_func<KWin::Window *>(ref_of(this), "Window.transientFor");
}
bool Window::modal() const {
  return call_kwin_func<bool>(ref_of(this), "Window.modal");
}
bool Window::move() const {
  return call_kwin_func<bool>(ref_of(this), "Window.move");
}
bool Window::resize() const {
  return call_kwin_func<bool>(ref_of(this), "Window.resize");
}
bool Window::decorationHasAlpha() const {
  return call_kwin_func<bool>(ref_of(this), "Window.decorationHasAlpha");
}
bool Window::providesContextHelp() const {
  return call_kwin_func<bool>(ref_of(this), "Window.providesContextHelp");
}
bool Window::maximizable() const {
  return call_kwin_func<bool>(ref_of(this), "Window.maximizable");
}
bool Window::moveable() const {
  return call_kwin_func<bool>(ref_of(this), "Window.moveable");
}
bool Window::moveableAcrossScreens() const {
  return call_kwin_func<bool>(ref_of(this), "Window.moveableAcrossScreens");
}
bool Window::resizeable() const {
  return call_kwin_func<bool>(ref_of(this), "Window.resizeable");
}
QString Window::desktopFileName() const {
  return call_kwin_func<QString>(ref_of(this), "Window.desktopFileName");
}
bool Window::hasApplicationMenu() const {
  return call_kwin_func<bool>(ref_of(this), "Window.hasApplicationMenu");
}
bool Window::applicationMenuActive() const {
  return call_kwin_func<bool>(ref_of(this), "Window.applicationMenuActive");
}
bool Window::unresponsive() const {
  return call_kwin_func<bool>(ref_of(this), "Window.unresponsive");
}
QString Window::colorScheme() const {
  return call_kwin_func<QString>(ref_of(this), "Window.colorScheme");
}
bool Window::hidden() const {
  return call_kwin_func<bool>(ref_of(this), "Window.hidden");
}
bool Window::inputMethod() const {
  return call_kwin_func<bool>(ref_of(this), "Window.inputMethod");
}
qreal Window::opacity() {
  return call_kwin_func<qreal>(ref_of(this), "Window.opacity");
}
void Window::setOpacity(qreal value) {
  return call_kwin_func<void>(ref_of(this), "Window.setOpacity", value);
}
bool Window::skipsCloseAnimation() {
  return call_kwin_func<bool>(ref_of(this), "Window.skipsCloseAnimation");
}
void Window::setSkipsCloseAnimation(bool value) {
  return call_kwin_func<void>(ref_of(this), "Window.setSkipsCloseAnimation",
                              value);
}
bool Window::fullScreen() {
  return call_kwin_func<bool>(ref_of(this), "Window.fullScreen");
}
void Window::setFullScreen(bool value) {
  return call_kwin_func<void>(ref_of(this), "Window.setFullScreen", value);
}
QList<KWin::VirtualDesktop *> Window::desktops() {
  return call_kwin_func<QList<KWin::VirtualDesktop *>>(ref_of(this),
                                                       "Window.desktops");
}
void Window::setDesktops(QList<KWin::VirtualDesktop *> value) {
  return call_kwin_func<void>(ref_of(this), "Window.setDesktops", value);
}
bool Window::onAllDesktops() {
  return call_kwin_func<bool>(ref_of(this), "Window.onAllDesktops");
}
void Window::setOnAllDesktops(bool value) {
  return call_kwin_func<void>(ref_of(this), "Window.setOnAllDesktops", value);
}
QStringList Window::activities() {
  return call_kwin_func<QStringList>(ref_of(this), "Window.activities");
}
void Window::setActivities(QStringList value) {
  return call_kwin_func<void>(ref_of(this), "Window.setActivities", value);
}
bool Window::skipTaskbar() {
  return call_kwin_func<bool>(ref_of(this), "Window.skipTaskbar");
}
void Window::setSkipTaskbar(bool value) {
  return call_kwin_func<void>(ref_of(this), "Window.setSkipTaskbar", value);
}
bool Window::skipPager() {
  return call_kwin_func<bool>(ref_of(this), "Window.skipPager");
}
void Window::setSkipPager(bool value) {
  return call_kwin_func<void>(ref_of(this), "Window.setSkipPager", value);
}
bool Window::skipSwitcher() {
  return call_kwin_func<bool>(ref_of(this), "Window.skipSwitcher");
}
void Window::setSkipSwitcher(bool value) {
  return call_kwin_func<void>(ref_of(this), "Window.setSkipSwitcher", value);
}
bool Window::keepAbove() {
  return call_kwin_func<bool>(ref_of(this), "Window.keepAbove");
}
void Window::setKeepAbove(bool value) {
  return call_kwin_func<void>(ref_of(this), "Window.setKeepAbove", value);
}
bool Window::keepBelow() {
  return call_kwin_func<bool>(ref_of(this), "Window.keepBelow");
}
void Window::setKeepBelow(bool value) {
  return call_kwin_func<void>(ref_of(this), "Window.setKeepBelow", value);
}
bool Window::shade() {
  return call_kwin_func<bool>(ref_of(this), "Window.shade");
}
void Window::setShade(bool value) {
  return call_kwin_func<void>(ref_of(this), "Window.setShade", value);
}
bool Window::minimized() {
  return call_kwin_func<bool>(ref_of(this), "Window.minimized");
}
void Window::setMinimized(bool value) {
  return call_kwin_func<void>(ref_of(this), "Window.setMinimized", value);
}
bool Window::demandsAttention() {
  return call_kwin_func<bool>(ref_of(this), "Window.demandsAttention");
}
void Window::setDemandsAttention(bool value) {
  return call_kwin_func<void>(ref_of(this), "Window.setDemandsAttention",
                              value);
}
QRectF Window::frameGeometry() {
  return call_kwin_func<QRectF>(ref_of(this), "Window.frameGeometry");
}
void Window::setFrameGeometry(QRectF value) {
  return call_kwin_func<void>(ref_of(this), "Window.setFrameGeometry", value);
}
bool Window::noBorder() {
  return call_kwin_func<bool>(ref_of(this), "Window.noBorder");
}
void Window::setNoBorder(bool value) {
  return call_kwin_func<void>(ref_of(this), "Window.setNoBorder", value);
}
KWin::Tile *Window::tile() {
  return call_kwin_func<KWin::Tile *>(ref_of(this), "Window.tile");
}
void Window::setTile(KWin::Tile *value) {
  return call_kwin_func<void>(ref_of(this), "Window.setTile", value);
}
void Window::closeWindow() {
  return call_kwin_func<void>(ref_of(this), "Window.closeWindow");
}
void Window::setMaximize(bool vertically, bool horizontally) {
  return call_kwin_func<void>(ref_of(this), "Window.setMaximize", vertically,
                              horizontally);
}

KWin::Tile *TileManager::rootTile() {
  return call_kwin_func<KWin::Tile *>(ref_of(this), "TileManager.rootTile");
}
KWin::Tile *TileManager::bestTileForPosition(qreal x, qreal y) {
  return call_kwin_func<KWin::Tile *>(ref_of(this),
                                      "TileManager.bestTileForPosition", x, y);
}

const QRectF Tile::absoluteGeometry() {
  return call_kwin_func<const QRectF>(ref_of(this), "Tile.absoluteGeometry");
}
const QRectF Tile::absoluteGeometryInScreen() {
  return call_kwin_func<const QRectF>(ref_of(this),
                                      "Tile.absoluteGeometryInScreen");
}
const int Tile::positionInLayout() {
  return call_kwin_func<const int>(ref_of(this), "Tile.positionInLayout");
}
const Tile *Tile::parent() {
  return call_kwin_func<const Tile *>(ref_of(this), "Tile.parent");
}
const QList<KWin::Tile *> Tile::tiles() {
  return call_kwin_func<const QList<KWin::Tile *>>(ref_of(this), "Tile.tiles");
}
const QList<KWin::Window *> Tile::windows() {
  return call_kwin_func<const QList<KWin::Window *>>(ref_of(this),
                                                     "Tile.windows");
}
const bool Tile::isLayout() {
  return call_kwin_func<const bool>(ref_of(this), "Tile.isLayout");
}
const bool Tile::canBeRemoved() {
  return call_kwin_func<const bool>(ref_of(this), "Tile.canBeRemoved");
}
QRectF Tile::relativeGeometry() {
  return call_kwin_func<QRectF>(ref_of(this), "Tile.relativeGeometry");
}
void Tile::setRelativeGeometry(QRectF value) {
  return call_kwin_func<void>(ref_of(this), "Tile.setRelativeGeometry", value);
}
qreal Tile::padding() {
  return call_kwin_func<qreal>(ref_of(this), "Tile.padding");
}
void Tile::setPadding(qreal value) {
  return call_kwin_func<void>(ref_of(this), "Tile.setPadding", value);
}
void Tile::resizeByPixels(qreal delta, Qt::Edge edge) {
  return call_kwin_func<void>(ref_of(this), "Tile.resizeByPixels", delta, edge);
}

} // namespace KWin
