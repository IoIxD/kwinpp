#pragma once

/* translation of the APIs listed on
 * https://develop.kde.org/docs/plasma/kwin/api/#global */

#include <QWindow>
#include <Qt>
#include <QtCore/QtCore>
#include <functional>
#include <string>

#include "kwinpp.hpp"

namespace KWin {

class WorkspaceWrapper;
class VirtualDesktop;
class Output;
class Window;
class TileManager;
class Tile;
// class EffectsHandlerManager;
// class EffectWindow;
class AnimationEffect;

// This entire class becomes pointless when we don't have QJSValue
// class ScriptedEffect;

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

  const QList<KWin::VirtualDesktop *> desktops();
  const QSize desktopGridSize();
  const int desktopGridWidth();
  const int desktopGridHeight();
  const int workspaceWidth();
  const int workspaceHeight();
  const QSize workspaceSize();
  const KWin::Output *activeScreen();
  const QList<KWin::Output *> screens();
  const QStringList activities();
  /*The bounding size of all screens combined. Overlapping areas are not counted
   * multiple times. */
  const QSize virtualScreenSize();
  /*The bounding geometry of all screens combined. Always starts at (0,0) and
   * has virtualScreenSize as it's size. */
  const QRect virtualScreenGeometry();
  /* List of Clients currently managed by KWin, orderd by their visibility
   * (later ones cover earlier ones).*/
  const QList<KWin::Window *> stackingOrder();

  QPoint cursorPos(); /* The current position of the cursor. */

  /* The current virtual desktop on the active screen. */
  KWin::VirtualDesktop *currentDesktop();
  /* Set the current virtual desktop on the active screen. */
  void setCurrentDesktop(KWin::VirtualDesktop *val);

  KWin::Window *activeWindow();
  void setActiveWindow(KWin::Window *val);

  QString currentActivity();
  void setCurrentActivity(QString val);

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

  void slotSwitchDesktopNext();
  void slotSwitchDesktopPrevious();
  void slotSwitchDesktopRight();
  void slotSwitchDesktopLeft();
  void slotSwitchDesktopUp();
  void slotSwitchDesktopDown();
  void slotSwitchToNextScreen();
  void slotSwitchToPrevScreen();
  void slotSwitchToRightScreen();
  void slotSwitchToLeftScreen();
  void slotSwitchToAboveScreen();
  void slotSwitchToBelowScreen();
  void slotWindowToNextScreen();
  void slotWindowToPrevScreen();
  void slotWindowToRightScreen();
  void slotWindowToLeftScreen();
  void slotWindowToAboveScreen();
  void slotWindowToBelowScreen();
  void slotToggleShowDesktop();
  void slotWindowMaximize();
  void slotWindowMaximizeVertical();
  void slotWindowMaximizeHorizontal();
  void slotWindowMinimize();
  void slotWindowShade();
  void slotWindowRaise();
  void slotWindowLower();
  void slotWindowRaiseOrLower();
  void slotActivateAttentionWindow();
  void slotWindowMoveLeft();
  void slotWindowMoveRight();
  void slotWindowMoveUp();
  void slotWindowMoveDown();
  void slotWindowExpandHorizontal();
  void slotWindowExpandVertical();
  void slotWindowShrinkHorizontal();
  void slotWindowShrinkVertical();
  void slotWindowQuickTileLeft();
  void slotWindowQuickTileRight();
  void slotWindowQuickTileTop();
  void slotWindowQuickTileBottom();
  void slotWindowQuickTileTopLeft();
  void slotWindowQuickTileTopRight();
  void slotWindowQuickTileBottomLeft();
  void slotWindowQuickTileBottomRight();
  void slotSwitchWindowUp();
  void slotSwitchWindowDown();
  void slotSwitchWindowRight();
  void slotSwitchWindowLeft();
  void slotIncreaseWindowOpacity();
  void slotLowerWindowOpacity();
  void slotWindowOperations();
  void slotWindowClose();
  void slotWindowMove();
  void slotWindowResize();
  void slotWindowAbove();
  void slotWindowBelow();
  void slotWindowOnAllDesktops();
  void slotWindowFullScreen();
  void slotWindowNoBorder();
  void slotWindowToNextDesktop();
  void slotWindowToPreviousDesktop();
  void slotWindowToDesktopRight();
  void slotWindowToDesktopLeft();
  void slotWindowToDesktopUp();
  void slotWindowToDesktopDown();
  /* Sends the Window to the given output.*/
  void sendClientToScreen(KWin::Window *client, KWin::Output *output);
  /* Shows an outline at the specified geometry. If an outline is already shown
   * the outline is moved to the new position. Use hideOutline to remove the
   * outline again. */
  void showOutline(const QRect &geometry);
  /* Overloaded method for convenience.*/
  void showOutline(int x, int y, int width, int height);
  /* Hides the outline previously shown by showOutline.*/
  void hideOutline();
  /* Returns the current desktop on the given screen. */
  KWin::VirtualDesktop *currentDesktopForScreen(KWin::Output *output) const;
  /* Sets the current desktop on the given screen.*/
  void setCurrentDesktopForScreen(KWin::VirtualDesktop *desktop,
                                  KWin::Output *output);
  KWin::Output *screenAt(const QPointF &pos) const;
  KWin::TileManager *tilingForScreen(const QString &screenName) const;
  KWin::TileManager *tilingForScreen(KWin::Output *output) const;
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
                    KWin::VirtualDesktop *desktop) const;
  /* Overloaded method for convenience. client The Client for which the area
   * should be retrieved The specified screen geometry */
  QRectF clientArea(ClientAreaOption option, KWin::Window *client) const;
  QRectF clientArea(ClientAreaOption option, const KWin::Window *client) const;

  /* Create a new virtual desktop at the requested position. position The
   * position of the desktop. It should be in range [0, count]. name The name
   * for the new desktop, if empty the default name will be used. */
  void createDesktop(int position, const QString &name) const;
  /* Removes the specified virtual desktop. */
  void removeDesktop(KWin::VirtualDesktop *desktop);
  /* Provides support information about the currently running KWin instance. */
  QString supportInformation() const;
  /* Raises a Window above all others on the screen.
   *
   * `window` The Window to raise */
  void raiseWindow(KWin::Window *window);
  /* Finds the Client with the given windowId. windowId The window Id of the
   * Client The found Client or null */
  KWin::Window *getClient(qulonglong windowId);
  /* Finds up to count windows at a particular location, prioritizing the
   * topmost one first. A negative count returns all matching clients.
   * `pos`: The location to look for
   *
   * `count`: The number of clients to return
   *
   * Returns: A list of Client objects 6.0*/
  QList<KWin::Window *> windowAt(const QPointF &pos, int count = 1) const;

  /* Checks if a specific effect is currently active.
   *
   * `pluginId`: The plugin Id of the effect to check.
   *
   * Returns: true if the effect isloaded and currently active, false
   * otherwise.*/
  bool isEffectActive(const QString &pluginId) const;
};

extern WorkspaceWrapper workspace;

class VirtualDesktop {
public:
  const QString id();
  const uint x11DesktopNumber();

  QString name();
  void setName(QString val);

  void onNameChanged(std::function<void> callback);
  void onX11DesktopNumberChanged(std::function<void> callback);
  /* Emitted just before the desktop gets destroyed. */
  void onAboutToBeDestroyed(std::function<void> callback);
};

class Output {
public:
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

  const QRect geometry();
  const qreal devicePixelRatio();
  const QString name();
  const QString manufacturer();
  const QString model();
  const QString serialNumber();

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

  QPointF mapToGlobal(const QPointF &pos) const;
  QPointF mapFromGlobal(const QPointF &pos) const;
};
class Window {
public:
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
  QRectF bufferGeometry() const;
  /* The geometry of the Window without frame borders. */
  QRectF clientGeometry() const;
  /* This property holds the position of the Window's frame geometry. */
  QPointF pos() const;
  /* This property holds the size of the Window's frame geometry. */
  QSizeF size() const;
  /* This property holds the x position of the Window's frame geometry. */
  qreal x() const;
  /* This property holds the y position of the Window's frame geometry. */
  qreal y() const;
  /* This property holds the width of the Window's frame geometry. */
  qreal width() const;
  /* This property holds the height of the Window's frame geometry. */
  qreal height() const;
  /* The output where the window center is on */
  KWin::Output *output() const;
  QRectF rect() const;
  QString resourceName() const;
  QString resourceClass() const;
  QString windowRole() const;
  /* Returns whether the window is a desktop background window (the one with
   * wallpaper). See _NET_WM_WINDOW_TYPE_DESKTOP at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  bool desktopWindow() const;
  /* Returns whether the window is a dock (i.e. a panel). See
   * _NET_WM_WINDOW_TYPE_DOCK at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  bool dock() const;
  /* Returns whether the window is a standalone (detached) toolbar window. See
   * _NET_WM_WINDOW_TYPE_TOOLBAR at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  bool toolbar() const;
  /* Returns whether the window is a torn-off menu. See _NET_WM_WINDOW_TYPE_MENU
   * at https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  bool menu() const;
  /* Returns whether the window is a "normal" window, i.e. an application or any
   * other window for which none of the specialized window types fit. See
   * _NET_WM_WINDOW_TYPE_NORMAL at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  bool normalWindow() const;
  /* Returns whether the window is a dialog window. See
   * _NET_WM_WINDOW_TYPE_DIALOG at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  bool dialog() const;
  /* Returns whether the window is a splashscreen. Note that many (especially
   * older) applications do not support marking their splash windows with this
   * type. See _NET_WM_WINDOW_TYPE_SPLASH at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  bool splash() const;
  /* Returns whether the window is a utility window, such as a tool window. See
   * _NET_WM_WINDOW_TYPE_UTILITY at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  bool utility() const;
  /* Returns whether the window is a dropdown menu (i.e. a popup directly or
   * indirectly open from the applications menubar). See
   * _NET_WM_WINDOW_TYPE_DROPDOWN_MENU at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  bool dropdownMenu() const;
  /* Returns whether the window is a popup menu (that is not a torn-off or
   * dropdown menu). See _NET_WM_WINDOW_TYPE_POPUP_MENU at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  bool popupMenu() const;
  /* Returns whether the window is a tooltip. See _NET_WM_WINDOW_TYPE_TOOLTIP at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  bool tooltip() const;
  /* Returns whether the window is a window with a notification. See
   * _NET_WM_WINDOW_TYPE_NOTIFICATION at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  bool notification() const;
  /* Returns whether the window is a window with a critical notification. */
  bool criticalNotification() const;
  /* Returns whether the window is an applet popup. */
  bool appletPopup() const;
  /* Returns whether the window is an On Screen Display. */
  bool onScreenDisplay() const;
  /* Returns whether the window is a combobox popup. See
   * _NET_WM_WINDOW_TYPE_COMBO at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  bool comboBox() const;
  /* Returns whether the window is a Drag&Drop icon. See _NET_WM_WINDOW_TYPE_DND
   * at https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  bool dndIcon() const;
  /* Returns the NETWM window type See
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
  int windowType() const;
  /* Whether this Window is managed by KWin (it has control over its placement
   * and other aspects, as opposed to override-redirect windows that are
   * entirely handled by the application). */
  bool managed() const;
  /* Whether this Window represents an already deleted window and only kept for
   * the compositor for animations. */
  bool deleted() const;
  /* Whether the window is a popup. */
  bool popupWindow() const;
  /* Whether this Window represents the outline. It's always false if
   * compositing is turned off. */
  bool outline() const;
  /* This property holds a UUID to uniquely identify this Window. */
  QUuid internalId() const;
  /* The pid of the process owning this window. 5.20 */
  int pid() const;
  /* The position of this window within Workspace's window stack. */
  int stackingOrder() const;
  /* Whether the Window can be set to fullScreen. The property is evaluated each
   * time it is invoked. Because of that there is no notify signal. */
  bool fullScreenable() const;
  /* Whether this Window is active or not. Use Workspace::activateWindow() to
   * activate a Window. Workspace::activateWindow */
  bool active() const;
  /* Whether the window can be closed by the user. */
  bool closeable() const;
  QIcon icon() const;
  /* Whether the Window can be shaded. The property is evaluated each time it is
   * invoked. Because of that there is no notify signal. */
  bool shadeable() const;
  /* Whether the Window can be minimized. The property is evaluated each time it
   * is invoked. Because of that there is no notify signal. */
  bool minimizable() const;
  /* The optional geometry representing the minimized Window in e.g a taskbar.
   * See _NET_WM_ICON_GEOMETRY at
   * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . The value
   * is evaluated each time the getter is called. Because of that no changed
   * signal is provided. */
  QRectF iconGeometry() const;
  /* Returns whether the window is any of special windows types (desktop, dock,
   * splash, ...), i.e. window types that usually don't have a window frame and
   * the user does not use window management (moving, raising,...) on them. The
   * value is evaluated each time the getter is called. Because of that no
   * changed signal is provided. */
  bool specialWindow() const;
  /* The Caption of the Window. Read from WM_NAME property together with a
   * suffix for hostname and shortcut. To read only the caption as provided by
   * WM_NAME, use the getter with an additional false value. */
  QString caption() const;
  /* Minimum size as specified in WM_NORMAL_HINTS */
  QSizeF minSize() const;
  /* Maximum size as specified in WM_NORMAL_HINTS */
  QSizeF maxSize() const;
  /* Whether the Window can accept keyboard focus. The value is evaluated each
   * time the getter is called. Because of that no changed signal is provided.
   */
  bool wantsInput() const;
  /* Whether the Window is a transient Window to another Window. transientFor */
  bool transient() const;
  /* The Window to which this Window is a transient if any. */
  KWin::Window *transientFor() const;
  /* Whether the Window represents a modal window. */
  bool modal() const;
  /* Whether the Window is currently being moved by the user. Notify signal is
   * emitted when the Window starts or ends move/resize mode. */
  bool move() const;
  /* Whether the Window is currently being resized by the user. Notify signal is
   * emitted when the Window starts or ends move/resize mode. */
  bool resize() const;
  /* Whether the decoration is currently using an alpha channel. */
  bool decorationHasAlpha() const;
  /* Whether the Window provides context help. Mostly needed by decorations to
   * decide whether to show the help button or not. */
  bool providesContextHelp() const;
  /* Whether the Window can be maximized both horizontally and vertically. The
   * property is evaluated each time it is invoked. Because of that there is no
   * notify signal. */
  bool maximizable() const;
  /* Whether the Window is movable. Even if it is not movable, it might be
   * possible to move it to another screen. The property is evaluated each time
   * it is invoked. Because of that there is no notify signal.
   * moveableAcrossScreens */
  bool moveable() const;
  /* Whether the Window can be moved to another screen. The property is
   * evaluated each time it is invoked. Because of that there is no notify
   * signal. moveable */
  bool moveableAcrossScreens() const;
  /* Whether the Window can be resized. The property is evaluated each time it
   * is invoked. Because of that there is no notify signal. */
  bool resizeable() const;
  /* The desktop file name of the application this Window belongs to. This is
   * either the base name without full path and without file extension of the
   * desktop file for the window's application (e.g. "org.kde.foo"). The
   * application's desktop file name can also be the full path to the desktop
   * file (e.g. "/opt/kde/share/org.kde.foo.desktop") in case it's not in a
   * standard location. */
  QString desktopFileName() const;
  /* Whether an application menu is available for this Window */
  bool hasApplicationMenu() const;
  /* Whether the application menu for this Window is currently opened */
  bool applicationMenuActive() const;
  /* Whether this window is unresponsive. When an application failed to react on
   * a ping request in time, it is considered unresponsive. This usually
   * indicates that the application froze or crashed. */
  bool unresponsive() const;
  /* The color scheme set on this window Absolute file path, or name of palette
   * in the user's config directory following KColorSchemes format. An empty
   * string indicates the default palette from kdeglobals is used. this
   * indicates the colour scheme requested, which might differ from the theme
   * applied if the colorScheme cannot be found */
  QString colorScheme() const;

  // undocumented/C++ scripting only type
  // KWin::Layer layer() const;

  /* Whether this window is hidden. It's usually the case with auto-hide panels.
   */
  bool hidden() const;
  /* Returns whether this window is a input method window. This is only used for
   * Wayland. */
  bool inputMethod() const;

  qreal opacity();
  void setOpacity(qreal);
  /* Whether the window does not want to be animated on window close. There are
   * legit reasons for this like a screenshot application which does not want
   * it's window being captured. */
  bool skipsCloseAnimation();
  void setSkipsCloseAnimation(bool);
  /* Whether this Window is fullScreen. A Window might either be fullScreen due
   * to the _NET_WM property or through a legacy support hack. The fullScreen
   * state can only be changed if the Window does not use the legacy hack. To be
   * sure whether the state changed, connect to the notify signal. */
  bool fullScreen();
  void setFullScreen(bool);
  /* The virtual desktops this client is on. If it's on all desktops, the list
   * is empty. */
  QList<KWin::VirtualDesktop *> desktops();
  void setDesktops(QList<KWin::VirtualDesktop *>);
  /* Whether the Window is on all desktops. That is desktop is -1. */
  bool onAllDesktops();
  void setOnAllDesktops(bool);
  /* The activities this client is on. If it's on all activities the property is
   * empty. */
  QStringList activities();
  void setActivities(QStringList);
  /* Indicates that the window should not be included on a taskbar. */
  bool skipTaskbar();
  void setSkipTaskbar(bool);
  /* Indicates that the window should not be included on a Pager. */
  bool skipPager();
  void setSkipPager(bool);
  /* Whether the Window should be excluded from window switching effects. */
  bool skipSwitcher();
  void setSkipSwitcher(bool);
  /* Whether the Window is set to be kept above other windows. */
  bool keepAbove();
  void setKeepAbove(bool);
  /* Whether the Window is set to be kept below other windows. */
  bool keepBelow();
  void setKeepBelow(bool);
  /* Whether the Window is shaded. */
  bool shade();
  void setShade(bool);
  /* Whether the Window is minimized. */
  bool minimized();
  void setMinimized(bool);
  /* Whether window state _NET_WM_STATE_DEMANDS_ATTENTION is set. This state
   * indicates that some action in or with the window happened. For example, it
   * may be set by the Window Manager if the window requested activation but the
   * Window Manager refused it, or the application may set it if it finished
   * some work. This state may be set by both the Window and the Window Manager.
   * It should be unset by the Window Manager when it decides the window got the
   * required attention (usually, that it got activated). */
  bool demandsAttention();
  void setDemandsAttention(bool);
  /* The geometry of this Window. Be aware that depending on resize mode the
   * frameGeometryChanged signal might be emitted at each resize step or only at
   * the end of the resize operation. */
  QRectF frameGeometry();
  void setFrameGeometry(QRectF);
  /* Whether the window has a decoration or not. This property is not allowed to
   * be set by applications themselves. The decision whether a window has a
   * border or not belongs to the window manager. If this property gets abused
   * by application developers, it will be removed again. */
  bool noBorder();
  void setNoBorder(bool);
  /* The Tile this window is associated to, if any */
  KWin::Tile *tile();
  void setTile(KWin::Tile *);

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

  void closeWindow();
  /* Sets the maximization according to vertically and horizontally. */
  void setMaximize(bool vertically, bool horizontally);
};

class TileManager {
public:
  KWin::Tile *rootTile();

  // undocumented/C++ scripting only type
  // TileModel *model();

  void onTileRemoved(std::function<void(KWin::Tile *tile)> callback);

  KWin::Tile *bestTileForPosition(qreal x, qreal y);
};
class Tile {
public:
  enum class LayoutDirection {
    Floating,
    Horizontal,
    Vertical,
  };

  const QRectF absoluteGeometry();
  const QRectF absoluteGeometryInScreen();
  const int positionInLayout();
  const Tile *parent();
  const QList<KWin::Tile *> tiles();
  const QList<KWin::Window *> windows();
  const bool isLayout();
  const bool canBeRemoved();

  QRectF relativeGeometry();
  void setRelativeGeometry(QRectF);
  qreal padding();
  void setPadding(qreal);

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

  void resizeByPixels(qreal delta, Qt::Edge edge);
};
// class EffectsHandlerManager {
// public:
//   enum class OnScreenMessageHideFlag {
//     /* The on-screen-message should skip the close window animation. */
//     SkipsCloseAnimation,
//   };
//
//   const QStringList activeEffects();
//   const QStringList loadedEffects();
//   const QStringList listOfEffects();
//   const QString currentActivity();
//   const QSize desktopGridSize();
//   const int desktopGridWidth();
//   const int desktopGridHeight();
//   const int workspaceWidth();
//   const int workspaceHeight();
//   const QList<KWin::VirtualDesktop *> desktops();
//   const bool optionRollOverDesktops();
//   const KWin::Output *activeScreen();
//   /* Factor by which animation speed in the effect should be modified
//    * (multiplied). If configurable in the effect itself, the option should
//    have
//    * also 'default' animation speed. The actual value should be determined
//    using
//    * animationTime(). Note: The factor can be also 0, so make sure your code
//    can
//    * cope with 0ms time if used manually. */
//   const qreal animationTimeFactor();
//   const QList<EffectWindow *> stackingOrder();
//   /* Whether window decorations use the alpha channel. */
//   const bool decorationsHaveAlpha();
//
//   const QPointF cursorPos();
//   const QSize virtualScreenSize();
//   const QRect virtualScreenGeometry();
//   const bool hasActiveFullScreenEffect();
//   const KWin::EffectWindow *inputPanel();
//
//   // undocumented/C++ scripting only type
//   // CompositingType compositingType();
//
//   /* The status of the session i.e if the user is logging out 5.18 */
//   // undocumented/C++ scripting only type
//   // KWin::SessionState sessionState();
//
//   /* The current virtual desktop on the active screen. */
//   KWin::VirtualDesktop *currentDesktop();
//   void setCurrentDesktop(KWin::VirtualDesktop *);
//   KWin::EffectWindow *activeWindow();
//   void setActiveWindow(KWin::EffectWindow *);
//
//   /* This signal is emitted whenever a new screen is added to the system. */
//   void onScreenAdded(std::function<void(KWin::Output *screen)>);
//   /* This signal is emitted whenever a screen is removed from the system. */
//   void onScreenRemoved(std::function<void(KWin::Output *screen)>);
//   /* Signal emitted when the current desktop changed. oldDesktop is the
//    * previously current desktop. newDesktop is the new current desktop. with
//    is
//    * the window which is taken over to the new desktop, can be NULL
//    (since 4.9).
//    * output is the screen where the change happened (since 6.7). */
//   void onDesktopChanged(
//       std::function<void(KWin::VirtualDesktop *oldDesktop,
//                          KWin::VirtualDesktop *newDesktop,
//                          KWin::EffectWindow *with, KWin::Output *output)>);
//   /* Signal emmitted while desktop is changing for animation. currentDesktop
//   is
//    * the current desktop. offset is the current desktop offset. offset.x() =
//    .6
//    * means 60% of the way to the desktop to the right. Positive Values means
//    Up
//    * and Right. output is the screen where the change is happening
//    (since 6.7).
//    */
//   void onDesktopChanging(
//       std::function<void(KWin::VirtualDesktop *currentDesktop, QPointF
//       offset,
//                          KWin::EffectWindow *with, KWin::Output *output)>);
//   void onDesktopChangingCancelled(std::function<void()>);
//   void onDesktopAdded(std::function<void(KWin::VirtualDesktop *desktop)>);
//   void onDesktopRemoved(std::function<void(KWin::VirtualDesktop *desktop)>);
//   /* Emitted when the virtual desktop grid layout changes size new size */
//   void onDesktopGridSizeChanged(std::function<void(const QSize &size)>);
//   /* Emitted when the virtual desktop grid layout changes width new width */
//   void onDesktopGridWidthChanged(std::function<void(int width)>);
//   /* Emitted when the virtual desktop grid layout changes height new height
//   */ void onDesktopGridHeightChanged(std::function<void(int height)>);
//   /* Signal emitted when the desktop showing ("dashboard") state changed The
//    * desktop is risen to the keepAbove layer, you may want to elevate windows
//    or
//    * such. */
//   void onShowingDesktopChanged(std::function<void(bool)>);
//   /* Signal emitted when a new window has been added to the Workspace.
//    *
//    * `w` The added window */
//   void onWindowAdded(std::function<void(KWin::EffectWindow *w)>);
//   /* Signal emitted when a window is being removed from the Workspace. An
//   effect
//    * which wants to animate the window closing should connect to this signal
//    and
//    * reference the window by using refWindow
//    *
//    * `w` The window which is being closed */
//   void onWindowClosed(std::function<void(KWin::EffectWindow *w)>);
//   /* Signal emitted when a window gets activated.
//    *
//    * `w` The new active window, or NULL if there is no active window. */
//   void onWindowActivated(std::function<void(KWin::EffectWindow *w)>);
//   /* Signal emitted when a window is deleted. This means that a closed window
//   is
//    * not referenced any more. An effect bookkeeping the closed windows should
//    * connect to this signal to clean up the internal references.
//    *
//    * `w` The window which is going to be deleted. */
//   void onWindowDeleted(std::function<void(KWin::EffectWindow *w)>);
//   /* Signal emitted when a tabbox is added. An effect who wants to replace
//   the
//    * tabbox with itself should use refTabBox.
//    *
//    * `mode`: The TabBoxMode. */
//   void onTabBoxAdded(std::function<void(int mode)>);
//   /* Signal emitted when the TabBox was closed by KWin core. An effect which
//    * referenced the TabBox should use unrefTabBox to unref again. unrefTabBox
//    * tabBoxAdded 4.7 */
//   void onTabBoxClosed(std::function<void()>);
//   /* Signal emitted when the selected TabBox window changed or the TabBox
//   List
//    * changed. An effect should only response to this signal if it referenced
//    the
//    * TabBox with refTabBox. */
//   void onTabBoxUpdated(std::function<void()>);
//   /* Signal emitted when a key event, which is not handled by TabBox directly
//    * is, happens while TabBox is active. An effect might use the key event to
//    * e.g. change the selected window. An effect should only response to this
//    * signal if it referenced the TabBox with refTabBox.
//    *
//    * `event`: The key event not handled by TabBox directly */
//   void onTabBoxKeyEvent(std::function<void(QKeyEvent *event)>);
//   /* Signal emitted when mouse changed. If an effect needs to get updated
//   mouse
//    * positions, it needs to first call startMousePolling. For a fullscreen
//    * effect it is better to use an input window and react on
//    * windowInputMouseEvent.
//    *
//    * `pos`: The new mouse position
//    *
//    * `oldpos`: The previously mouse position
//    *
//    * `buttons`: The pressed mouse buttons
//    *
//    * `oldbuttons`: The previously pressed mouse buttons
//    *
//    * `modifiers`: Pressed keyboard modifiers
//    *
//    * `oldmodifiers`: Previously pressed keyboard modifiers. */
//   void onMouseChanged(
//       std::function<void(const QPointF &pos, const QPointF &oldpos,
//                          Qt::MouseButtons buttons, Qt::MouseButtons
//                          oldbuttons, Qt::KeyboardModifiers modifiers,
//                          Qt::KeyboardModifiers oldmodifiers)>);
//   /* Signal emitted when the cursor shape changed. You'll likely want to
//   query
//    * the current cursor as reaction: xcb_xfixes_get_cursor_image_unchecked
//    * Connection to this signal is tracked, so if you don't need it anymore,
//    * disconnect from it to stop cursor event filtering */
//   void onCursorShapeChanged(std::function<void()>);
//   /* Receives events registered for using registerPropertyType. Use
//    * readProperty() to get the property data. Note that the property may be
//    * already set on the window, so doing the same processing from
//    windowAdded()
//    * (e.g. simply calling propertyNotify() from it) is usually needed.
//    *
//    * `w`: The window whose property changed, is null if it is a root window
//    * property
//    *
//    * `atom`: The property */
//   void onPropertyNotify(std::function<void(KWin::EffectWindow *w, long
//   atom)>);
//   /* This signal is emitted when the global activity is changed id id of the
//   new
//    * current activity */
//   void onCurrentActivityChanged(std::function<void(const QString &id)>);
//   /* This signal is emitted when a new activity is added id id of the new
//    * activity */
//   void onActivityAdded(std::function<void(const QString &id)>);
//   /* This signal is emitted when the activity is removed id id of the removed
//    * activity */
//   void onActivityRemoved(std::function<void(const QString &id)>);
//   /* This signal is emitted when the screen got locked or unlocked.
//    *
//    * `locked`: true if the screen is now locked, false if it is now unlocked
//    */
//   void onScreenLockingChanged(std::function<void(bool locked)>);
//   /* This signal is emitted just before the screen locker tries to grab keys
//   and
//    * lock the screen Effects should release any grabs immediately */
//   void onScreenAboutToLock(std::function<void()>);
//   /* This signels is emitted when ever the stacking order is change, ie. a
//    * window is risen or lowered */
//   void onStackingOrderChanged(std::function<void()>);
//   /* This signal is emitted when the user starts to approach the border with
//   the
//    * mouse. The factor describes how far away the mouse is in a relative
//    mean.
//    * The values are in [0.0, 1.0] with 0.0 being emitted when first entered
//    and
//    * on leaving. The value 1.0 means that the border is reached with the
//    mouse.
//    * So the values are well suited for animations. The signal is always
//    emitted
//    * when the mouse cursor position changes.
//    *
//    * `border`: The screen edge which is being approached
//    *
//    * `factor`: Value in range [0.0,1.0] to describe how close the mouse is to
//    * the border
//    *
//    * `geometry`: The geometry of the edge which is being approached */
//   void onScreenEdgeApproaching(
//       std::function<void(WorkspaceWrapper::ElectricBorder border, qreal
//       factor,
//                          const QRect &geometry)>);
//   /* Emitted whenever the virtualScreenSize changes.*/
//   void onVirtualScreenSizeChanged(std::function<void()>);
//   /* Emitted whenever the virtualScreenGeometry changes. */
//   void onVirtualScreenGeometryChanged(std::function<void()>);
//   /* This signal gets emitted when the data on EffectWindow w for role
//   changed.
//    * An Effect can connect to this signal to read the new value and react on
//    it.
//    * E.g. an Effect which does not operate on windows grabbed by another
//    Effect
//    * wants to cancel the already scheduled animation if another Effect adds a
//    * grab.
//    *
//    * `w`: The EffectWindow for which the data changed
//    *
//    * `role`: The data role which changed */
//   void
//       onWindowDataChanged(std::function<void(KWin::EffectWindow *w, int
//       role)>);
//   /* The xcb connection changed, either a new xcbConnection got created or
//   the
//    * existing one got destroyed. Effects can use this to refetch the
//    properties
//    * they want to set. When the xcbConnection changes also the x11RootWindow
//    * becomes invalid. */
//   void onXcbConnectionChanged(std::function<void()>);
//   /* This signal is emitted when active fullscreen effect changed.*/
//   void onActiveFullScreenEffectChanged(std::function<void()>);
//   /* This signal is emitted when active fullscreen effect changed to being
//   set
//    * or unset activeFullScreenEffect */
//   void onHasActiveFullScreenEffectChanged(std::function<void()>);
//   /* This signal is emitted when the session state was changed */
//   void onSessionStateChanged(std::function<void()>);
//   void
//       onStartupAdded(std::function<void(const QString &id, const QIcon
//       &icon)>);
//   void onStartupChanged(
//       std::function<void(const QString &id, const QIcon &icon)>);
//   void onStartupRemoved(std::function<void(const QString &id)>);
//   void onInputPanelChanged(std::function<void()>);
//
//   void reconfigureEffect(const QString &name);
//   bool loadEffect(const QString &name);
//   void toggleEffect(const QString &name);
//   void unloadEffect(const QString &name);
//   bool isEffectLoaded(const QString &name) const;
//   bool isEffectSupported(const QString &name);
//   QList<bool> areEffectsSupported(const QStringList &names);
//   QString supportInformation(const QString &name) const;
//   QString debug(const QString &name,
//                 const QString &parameter = QString()) const;
//   void moveWindow(KWin::EffectWindow *w, const QPoint &pos, bool snap =
//   false,
//                   double snapAdjust = 1.0);
//   /* Moves a window to the given desktops On X11, the window will end up on
//   the
//    * last window in the list Setting this to an empty list will set the
//    window
//    * on all desktops */
//   void windowToDesktops(KWin::EffectWindow *w,
//                         const QList<KWin::VirtualDesktop *> &desktops);
//   void windowToScreen(KWin::EffectWindow *w, Output *screen);
//   /* The desktop above the given desktop. Wraps around to the bottom of the
//    * layout if wrap is set. If id is not set use the current one. */
//   KWin::VirtualDesktop *desktopAbove(KWin::VirtualDesktop *desktop = nullptr,
//                                      bool wrap = true) const;
//   /* The desktop to the right of the given desktop. Wraps around to the left
//   of
//    * the layout if wrap is set. If id is not set use the current one. */
//   KWin::VirtualDesktop *desktopToRight(KWin::VirtualDesktop *desktop =
//   nullptr,
//                                        bool wrap = true) const;
//   /* The desktop below the given desktop. Wraps around to the top of the
//   layout
//    * if wrap is set. If id is not set use the current one. */
//   KWin::VirtualDesktop *desktopBelow(KWin::VirtualDesktop *desktop = nullptr,
//                                      bool wrap = true) const;
//   /* The desktop to the left of the given desktop. Wraps around to the right
//   of
//    * the layout if wrap is set. If id is not set use the current one. */
//   KWin::VirtualDesktop *desktopToLeft(KWin::VirtualDesktop *desktop =
//   nullptr,
//                                       bool wrap = true) const;
//   QString desktopName(KWin::VirtualDesktop *desktop) const;
//
//   /* Finds the EffectWindow for the Window with KWin internal id. If there is
//   no
//    * such window null is returned. */
//   KWin::EffectWindow *findWindow(const QUuid &id) const;
//
//   void setElevatedWindow(KWin::EffectWindow *w, bool set);
//   /* Schedules the entire workspace to be repainted next time. If you call it
//    * during painting (including prepaint) then it does not affect the current
//    * painting. */
//   void addRepaintFull();
//   void addRepaint(const QRectF &r);
//   void addRepaint(const QRect &r);
//   void addRepaint(const QRegion &r);
//   void addRepaint(int x, int y, int w, int h);
// };
// class EffectWindow {
// public:
//   enum {
//     /* Window will not be painted*/
//     PAINT_DISABLED,
//     /* Window will not be painted because of which desktop it's on*/
//     PAINT_DISABLED_BY_DESKTOP,
//     /* Window will not be painted because it is minimized*/
//     PAINT_DISABLED_BY_MINIMIZE,
//     /* Window will not be painted because it's not on the current activity*/
//     PAINT_DISABLED_BY_ACTIVITY,
//   };
//
//   QRectF geometry() const;
//   QRectF expandedGeometry() const;
//   qreal height() const;
//   qreal opacity() const;
//   QPointF pos() const;
//   KWin::Output *screen() const;
//   QSizeF size() const;
//   qreal width() const;
//   qreal x() const;
//   qreal y() const;
//   QList<KWin::VirtualDesktop *> desktops() const;
//   bool onAllDesktops() const;
//   bool onCurrentDesktop() const;
//   QRectF rect() const;
//   QString windowClass() const;
//   QString windowRole() const;
//   /* Returns whether the window is a desktop background window (the one with
//    * wallpaper). See _NET_WM_WINDOW_TYPE_DESKTOP at
//    * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
//   bool desktopWindow() const;
//   /* Returns whether the window is a dock (i.e. a panel). See
//    * _NET_WM_WINDOW_TYPE_DOCK at
//    * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
//   bool dock() const;
//   /* Returns whether the window is a standalone (detached) toolbar window.
//   See
//    * _NET_WM_WINDOW_TYPE_TOOLBAR at
//    * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
//   bool toolbar() const;
//   /* Returns whether the window is a torn-off menu. See
//   _NET_WM_WINDOW_TYPE_MENU
//    * at https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
//   bool menu() const;
//   /* Returns whether the window is a "normal" window, i.e. an application or
//   any
//    * other window for which none of the specialized window types fit. See
//    * _NET_WM_WINDOW_TYPE_NORMAL at
//    * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
//   bool normalWindow() const;
//   /* Returns whether the window is a dialog window. See
//    * _NET_WM_WINDOW_TYPE_DIALOG at
//    * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
//   bool dialog() const;
//   /* Returns whether the window is a splashscreen. Note that many (especially
//    * older) applications do not support marking their splash windows with
//    this
//    * type. See _NET_WM_WINDOW_TYPE_SPLASH at
//    * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
//   bool splash() const;
//   /* Returns whether the window is a utility window, such as a tool window.
//   See
//    * _NET_WM_WINDOW_TYPE_UTILITY at
//    * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
//   bool utility() const;
//   /* Returns whether the window is a dropdown menu (i.e. a popup directly or
//    * indirectly open from the applications menubar). See
//    * _NET_WM_WINDOW_TYPE_DROPDOWN_MENU at
//    * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
//   bool dropdownMenu() const;
//   /* Returns whether the window is a popup menu (that is not a torn-off or
//    * dropdown menu). See _NET_WM_WINDOW_TYPE_POPUP_MENU at
//    * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
//   bool popupMenu() const;
//   /* Returns whether the window is a tooltip. See _NET_WM_WINDOW_TYPE_TOOLTIP
//   at
//    * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
//   bool tooltip() const;
//   /* Returns whether the window is a window with a notification. See
//    * _NET_WM_WINDOW_TYPE_NOTIFICATION at
//    * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
//   bool notification() const;
//   /* Returns whether the window is a window with a critical notification.
//   using
//    * the non-standard _KDE_NET_WM_WINDOW_TYPE_CRITICAL_NOTIFICATION */
//   bool criticalNotification() const;
//   /* Returns whether the window is an on screen display window using the
//    * non-standard _KDE_NET_WM_WINDOW_TYPE_ON_SCREEN_DISPLAY */
//   bool onScreenDisplay() const;
//   /* Returns whether the window is a combobox popup. See
//    * _NET_WM_WINDOW_TYPE_COMBO at
//    * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
//   bool comboBox() const;
//   /* Returns whether the window is a Drag&Drop icon. See
//   _NET_WM_WINDOW_TYPE_DND
//    * at https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
//   bool dndIcon() const;
//   /* Returns the NETWM window type See
//    * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
//   int windowType() const;
//   /* Whether this EffectWindow represents an already deleted window and only
//    * kept for the compositor for animations. */
//   bool deleted() const;
//   /* The Caption of the window. Read from WM_NAME property together with a
//    * suffix for hostname and shortcut. */
//   QString caption() const;
//   /* Whether the window is set to be kept above other windows. */
//   bool keepAbove() const;
//   /* Whether the window is set to be kept below other windows. */
//   bool keepBelow() const;
//   /* Whether the window represents a modal window. */
//   bool modal() const;
//   /* Whether the window is moveable. Even if it is not moveable, it might be
//    * possible to move it to another screen. moveableAcrossScreens */
//   bool moveable() const;
//   /* Whether the window can be moved to another screen. moveable */
//   bool moveableAcrossScreens() const;
//   /* By how much the window wishes to grow/shrink at least. Usually
//   QSize(1,1).
//    * MAY BE DISOBEYED BY THE WM! It's only for information, do NOT rely on it
//    at
//    * all. */
//   QSizeF basicUnit() const;
//   /* Whether the window is currently being moved by the user. */
//   bool move() const;
//   /* Whether the window is currently being resized by the user. */
//   bool resize() const;
//   /* The optional geometry representing the minimized Client in e.g a
//   taskbar.
//    * See _NET_WM_ICON_GEOMETRY at
//    * https://standards.freedesktop.org/wm-spec/wm-spec-latest.html . */
//   QRectF iconGeometry() const;
//   /* Returns whether the window is any of special windows types (desktop,
//   dock,
//    * splash, ...), i.e. window types that usually don't have a window frame
//    and
//    * the user does not use window management (moving, raising,...) on them.
//    */
//   bool specialWindow() const;
//   QIcon icon() const;
//   /* Whether the window should be excluded from window switching effects. */
//   bool skipSwitcher() const;
//   /* Geometry of the actual window contents inside the whole (including
//    * decorations) window. */
//   QRectF contentsRect() const;
//   /* Geometry of the transparent rect in the decoration. May be different
//   from
//    * contentsRect if the decoration is extended into the client area. */
//   QRectF decorationInnerRect() const;
//   bool hasDecoration() const;
//   QStringList activities() const;
//   bool onCurrentActivity() const;
//   bool onAllActivities() const;
//   /* Whether the decoration currently uses an alpha channel. 4.10 */
//   bool decorationHasAlpha() const;
//   /* Whether the window is currently visible to the user, that is: Not
//   minimized
//    * On current desktop On current activity 4.11 */
//   bool visible() const;
//   /* Whether the window does not want to be animated on window close. In case
//    * this property is true it is not useful to start an animation on window
//    * close. The window will not be visible, but the animation hooks are
//    * executed. 5.0 */
//   bool skipsCloseAnimation() const;
//   /* Whether the window is fullscreen. 5.6 */
//   bool fullScreen() const;
//   /* Whether this client is unresponsive. When an application failed to react
//   on
//    * a ping request in time, it is considered unresponsive. This usually
//    * indicates that the application froze or crashed. 5.10 */
//   bool unresponsive() const;
//   /* Whether this is a Wayland client. 5.15 */
//   bool waylandClient() const;
//   /* Whether this is an X11 client. 5.15 */
//   bool x11Client() const;
//   /* Whether the window is a popup. A popup is a window that can be used to
//    * implement tooltips, combo box popups, popup menus and other similar user
//    * interface concepts. 5.15 */
//   bool popupWindow() const;
//
//   /* KWin internal window. Specific to Wayland platform. If the EffectWindow
//    * does not reference an internal window, this property is null. 5.16 */
//   QWindow *internalWindow() const;
//
//   /* Whether this EffectWindow represents the outline. When compositing is
//    * turned on, the outline is an actual window. 5.16 */
//   bool outline() const;
//   /* The PID of the application this window belongs to. 5.18 */
//   pid_t pid() const;
//   /* Whether this EffectWindow represents the screenlocker greeter. 5.22 */
//   bool lockScreen() const;
//   /* Whether this EffectWindow is hidden because the show desktop mode is
//    * active. */
//   bool hiddenByShowDesktop() const;
//
//   bool minimized();
//   void setMinimized(bool);
//
//   /* Signal emitted when a user begins a window move or resize operation. To
//    * figure out whether the user resizes or moves the window use isUserMove
//    or
//    * isUserResize. Whenever the geometry is updated the signal
//    * windowStepUserMovedResized is emitted with the current geometry. The
//    * move/resize operation ends with the signal windowFinishUserMovedResized.
//    * Only one window can be moved/resized by the user at the same time!
//    *
//    * `w`: The window which is being moved/resized*/
//   void
//       onWindowStartUserMovedResized(std::function<void(KWin::EffectWindow
//       *w)>);
//
//   /* Signal emitted during a move/resize operation when the user changed the
//    * geometry. Please note: KWin supports two operation modes. In one mode
//    all
//    * changes are applied instantly. This means the window's geometry matches
//    the
//    * passed in geometry. In the other mode the geometry is changed after the
//    * user ended the move/resize mode. The geometry differs from the window's
//    * geometry. Also the window's pixmap still has the same size as before.
//    * Depending what the effect wants to do it would be recommended to
//    * scale/translate the window.
//    *
//    * `w`: The window which is being moved/resized
//    *
//    * `geometry`: The geometry of the window in the current move/resize step.
//    */
//   void onWindowStepUserMovedResized(
//       std::function<void(KWin::EffectWindow *w, const QRectF &geometry)>);
//
//   /* Signal emitted when the user finishes move/resize of window w.
//    *
//    * `w`: The window which has been moved/resized */
//   void onWindowFinishUserMovedResized(
//       std::function<void(KWin::EffectWindow *w)>);
//
//   /* Signal emitted when the maximized state of the window w changed. A
//   window
//    * can be in one of four states: restored: both horizontal and vertical are
//    * false horizontally maximized: horizontal is true and vertical is false
//    * vertically maximized: horizontal is false and vertical is true
//    completely
//    * maximized: both horizontal and vertical are true w The window whose
//    * maximized state changed horizontal If true maximized horizontally
//    vertical
//    * If true maximized vertically */
//   void onWindowMaximizedStateChanged(
//       std::function<void(KWin::EffectWindow *w, bool horizontal,
//                          bool vertical)>);
//
//   /* Signal emitted when the maximized state of the window w is about to
//   change,
//    * but before windowMaximizedStateChanged is emitted or any geometry
//    change.
//    * Useful for OffscreenEffect to grab a window image before any actual
//    change
//    * happens A window can be in one of four states: restored: both horizontal
//    * and vertical are false horizontally maximized: horizontal is true and
//    * vertical is false vertically maximized: horizontal is false and vertical
//    is
//    * true completely maximized: both horizontal and vertical are true w The
//    * window whose maximized state changed horizontal If true maximized
//    * horizontally vertical If true maximized vertically */
//   void onWindowMaximizedStateAboutToChange(
//       std::function<void(KWin::EffectWindow *w, bool horizontal,
//                          bool vertical)>);
//
//   /* This signal is emitted when the frame geometry of a window changed.
//    *
//    * `window`: The window whose geometry changed
//    *
//    * `oldGeometry`: The previous geometry */
//   void onWindowFrameGeometryChanged(
//       std::function<void(KWin::EffectWindow *window,
//                          const QRectF &oldGeometry)>);
//
//   /* This signal is emitted when the frame geometry is about to change, the
//   new
//    * one is not known yet. Useful for OffscreenEffect to grab a window image
//    * before any actual change happens.
//    *
//    * `window`: The window whose geometry is about to change */
//   void onWindowFrameGeometryAboutToChange(
//       std::function<void(KWin::EffectWindow *window)>);
//
//   /* Signal emitted when the windows opacity is changed.
//    *
//    * `w`: The window whose opacity level is changed.
//    *
//    * `oldOpacity`: The previous opacity level
//    *
//    * `newOpacity`: The new opacity level */
//   void onWindowOpacityChanged(
//       std::function<void(KWin::EffectWindow *w, qreal oldOpacity,
//                          qreal newOpacity)>);
//
//   /* Signal emitted when a window is minimized or unminimized.
//    *
//    * `w`: The window whose minimized state has changed */
//   void onMinimizedChanged(std::function<void(KWin::EffectWindow *w)>);
//
//   /* Signal emitted when a window either becomes modal (ie. blocking for its
//    * main client) or looses that state.
//    *
//    * `w`: The window which was unminimized */
//   void onWindowModalityChanged(std::function<void(KWin::EffectWindow *w)>);
//
//   /* Signal emitted when a window either became unresponsive (eg. app froze
//   or
//    * crashed) or responsive
//    *
//    * `w`: The window that became (un)responsive
//    *
//    * `unresponsive`: Whether the window is responsive or unresponsive */
//   void onWindowUnresponsiveChanged(
//       std::function<void(KWin::EffectWindow *w, bool unresponsive)>);
//
//   /* Signal emitted when an area of a window is scheduled for repainting. Use
//    * this signal in an effect if another area needs to be synced as well.
//    *
//    * `w` The window which is scheduled for repainting */
//   void onWindowDamaged(std::function<void(KWin::EffectWindow *w)>);
//
//   /* This signal is emitted when the keep above state of w was changed. w The
//    * window whose the keep above state was changed. */
//   void onWindowKeepAboveChanged(std::function<void(KWin::EffectWindow *w)>);
//
//   /* This signal is emitted when the keep below state of was changed. w The
//    * window whose the keep below state was changed. */
//   void onWindowKeepBelowChanged(std::function<void(KWin::EffectWindow *w)>);
//
//   /* This signal is emitted when the full screen state of w was changed. w
//   The
//    * window whose the full screen state was changed. */
//   void onWindowFullScreenChanged(std::function<void(KWin::EffectWindow *w)>);
//
//   /* This signal is emitted when decoration of was changed. w The window for
//    * which decoration changed */
//   void onWindowDecorationChanged(
//       std::function<void(KWin::EffectWindow *window)>);
//
//   /* This signal is emitted when the visible geometry of a window changed. */
//   void onWindowExpandedGeometryChanged(
//       std::function<void(KWin::EffectWindow *window)>);
//
//   /* This signal is emitted when a window enters or leaves a virtual desktop.
//   */ void onWindowDesktopsChanged(std::function<void(KWin::EffectWindow
//   *window)>);
//
//   /* The window w gets shown again. The window was previously initially shown
//    * with windowAdded and hidden with windowHidden. */
//   void onWindowShown(std::function<void(KWin::EffectWindow *w)>);
//
//   /* The window w got hidden but not yet closed. This can happen when a
//   window
//    * is still being used and is supposed to be shown again with windowShown.
//    On
//    * X11 an example is autohiding panels. On Wayland every window first goes
//    * through the window hidden state and might get shown again, or might get
//    * closed the normal way. */
//   void onWindowHidden(std::function<void(KWin::EffectWindow *w)>);
// };
// class AnimationEffect {
// public:
//   enum class Anchor {
//     Left,
//     Top,
//     Right,
//     Bottom,
//     Horizontal,
//     Vertical,
//     Mouse,
//   };
//   enum class Attribute {
//     Opacity,
//     Brightness,
//     Saturation,
//     Scale,
//     Rotation,
//     Position,
//     Size,
//     Translation,
//     Clip,
//     Generic,
//     CrossFadePrevious,
//     /* Performs an animation with a provided shader. The float uniform
//        animationProgress is set to the current progress of the animation. */
//     Shader,
//     /* Like Shader, but additionally allows to animate a float uniform passed
//     to
//        the shader. The uniform location must be provided as metadata. */
//     ShaderUniform,
//     NonFloatBase
//   };
//   enum class MetaType {
//     SourceAnchor,
//     TargetAnchor,
//     RelativeSourceX,
//     RelativeSourceY,
//     RelativeTargetX,
//     RelativeTargetY,
//     Axis,
//   };
//   enum class Direction {
//     Forward,
//     Backward,
//   };
//   enum class TerminationFlag {
//     /* Don't terminate the animation when it reaches source or target
//        position. */
//     DontTerminate,
//     /* Terminate the animation when it reaches the source position. An
//        animation can reach the source position if its direction was changed
//        to go backward (from target to source). */
//     TerminateAtSource,
//     /* Terminate the animation when it reaches the target position. If this
//        flag is not set, then the animation will be persistent. */
//     TerminateAtTarget,
//   };
// };
//
// class ScriptedEffect {
// public:
//   enum class DataRole {
//     WindowAddedGrabRole,
//     WindowClosedGrabRole,
//     WindowMinimizedGrabRole,
//     WindowUnminimizedGrabRole,
//     WindowForceBlurRole,
//     WindowBlurBehindRole,
//     WindowForceBackgroundContrastRole,
//     WindowBackgroundContrastRole,
//   };
//   enum class EasingCurve {
//     GaussianCurve,
//   };
//   enum class ShaderTrait {
//     MapTexture,
//     UniformColor,
//     Modulate,
//     AdjustSaturation,
//   };
//
//   /* The plugin ID of the effect */
//   QString pluginId() const;
//   /* True if we are the active fullscreen effect */
//   bool isActiveFullScreenEffect();
//
//   bool borderActivated(ElectricBorder border) override;
//
//   /* Whether another effect has grabbed the w with the given grabRole. w The
//    * window to check grabRole The grab role to check true if another window
//    has
//    * grabbed the effect, false otherwise */
//   bool isGrabbed(KWin::EffectWindow *w, DataRole grabRole);
//   /* Grabs the window with the specified role. w The window. grabRole The
//   grab
//    * role. force By default, if the window is already grabbed by another
//    effect,
//    * then that window won't be grabbed by effect that called this method. If
//    you
//    * would like to grab a window even if it's grabbed by another effect, then
//    * pass true. true if the window was grabbed successfully, otherwise false.
//    */
//   bool grab(KWin::EffectWindow *w, DataRole grabRole, bool force = false);
//   /* Ungrabs the window with the specified role. w The window. grabRole The
//   grab
//    * role. true if the window was ungrabbed successfully, otherwise false. */
//   bool ungrab(KWin::EffectWindow *w, DataRole grabRole);
//   /* Reads the value from the configuration data for the given key. key The
//   key
//    * to search for defaultValue The value to return if the key is not found
//    The
//    * config value if present */
//   QJSValue readConfig(const QString &key,
//                       const QJSValue &defaultValue = QJSValue());
//   int displayWidth() const;
//   int displayHeight() const;
//   int animationTime(int defaultTime) const;
//   registerShortcut(const QString &objectName, const QString &text,
//                    const QString &keySequence, const QJSValue &callback);
//   bool registerScreenEdge(int edge, const QJSValue &callback);
//   bool registerRealtimeScreenEdge(int edge, const QJSValue &callback);
//   bool unregisterScreenEdge(int edge);
//   bool registerTouchScreenEdge(int edge, const QJSValue &callback);
//   bool unregisterTouchScreenEdge(int edge);
//   quint64 animate(KWin::EffectWindow *window, Attribute attribute, int ms,
//                   const QJSValue &to, const QJSValue &from = QJSValue(),
//                   uint metaData = 0, int curve = QEasingCurve::Linear,
//                   int delay = 0, bool fullScreen = false, bool keepAlive =
//                   true, uint shaderId = 0);
//   QJSValue animate(const QJSValue &object);
//   quint64 set(KWin::EffectWindow *window, Attribute attribute, int ms,
//               const QJSValue &to, const QJSValue &from = QJSValue(),
//               uint metaData = 0, int curve = QEasingCurve::Linear,
//               int delay = 0, bool fullScreen = false, bool keepAlive = true,
//               uint shaderId = 0);
//   QJSValue set(const QJSValue &object);
//   bool retarget(quint64 animationId, const QJSValue &newTarget,
//                 int newRemainingTime = -1);
//   bool retarget(const QList<quint64> &animationIds, const QJSValue
//   &newTarget,
//                 int newRemainingTime = -1);
//   bool freezeInTime(quint64 animationId, qint64 frozenTime);
//   bool freezeInTime(const QList<quint64> &animationIds, qint64 frozenTime);
//   bool redirect(quint64 animationId, Direction direction,
//                 TerminationFlags terminationFlags = TerminateAtSource);
//   bool redirect(const QList<quint64> &animationIds, Direction direction,
//                 TerminationFlags terminationFlags = TerminateAtSource);
//   bool complete(quint64 animationId);
//   bool complete(const QList<quint64> &animationIds);
//   bool cancel(quint64 animationId);
//   bool cancel(const QList<quint64> &animationIds);
//   QList<int> touchEdgesForAction(const QString &action) const;
//   uint addFragmentShader(ShaderTrait traits,
//                          const QString &fragmentShaderFile = {});
//   setUniform(uint shaderId, const QString &name, const QJSValue &value)
// };

} // namespace KWin