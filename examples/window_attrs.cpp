#include "kwinpp.hpp"
#include <print>

using namespace KWin;

int main() {
  Window *win = workspace.activeWindow();

  auto geom = win->bufferGeometry();
  std::println("bufferGeometry: ({},{},{},{})", geom.x(), geom.y(),
               geom.width(), geom.height());
  geom = win->clientGeometry();
  std::println("clientGeometry: ({},{},{},{})", geom.x(), geom.y(),
               geom.width(), geom.height());
  std::println("x: {}", win->x());
  std::println("y: {}", win->y());
  std::println("width: {}", win->width());
  std::println("height: {}", win->height());
  std::println("resourceName: {}", win->resourceName().toStdString());
  std::println("resourceClass: {}", win->resourceClass().toStdString());
  std::println("windowRole: {}", win->windowRole().toStdString());
  std::println("desktopWindow: {}", win->desktopWindow());
  std::println("dock: {}", win->dock());
  std::println("toolbar: {}", win->toolbar());
  std::println("menu: {}", win->menu());
  std::println("normalWindow: {}", win->normalWindow());
  std::println("dialog: {}", win->dialog());
  std::println("splash: {}", win->splash());
  std::println("utility: {}", win->utility());
  std::println("dropdownMenu: {}", win->dropdownMenu());
  std::println("popupMenu: {}", win->popupMenu());
  std::println("tooltip: {}", win->tooltip());
  std::println("notification: {}", win->notification());
  std::println("criticalNotification: {}", win->criticalNotification());
  std::println("appletPopup: {}", win->appletPopup());
  std::println("onScreenDisplay: {}", win->onScreenDisplay());
  std::println("comboBox: {}", win->comboBox());
  std::println("dndIcon: {}", win->dndIcon());
  std::println("windowType: {}", win->windowType());
  std::println("managed: {}", win->managed());
  std::println("deleted: {}", win->deleted());
  std::println("popupWindow: {}", win->popupWindow());
  std::println("outline: {}", win->outline());
  std::println("internalId: {}", win->internalId().toString().toStdString());
  std::println("pid: {}", win->pid());
  std::println("stackingOrder: {}", win->stackingOrder());
  std::println("fullScreenable: {}", win->fullScreenable());
  std::println("active: {}", win->active());
  std::println("closeable: {}", win->closeable());
  std::println("shadeable: {}", win->shadeable());
  std::println("minimizable: {}", win->minimizable());
  std::println("specialWindow: {}", win->specialWindow());
  std::println("caption: {}", win->caption().toStdString());
  std::println("minSize: ({}, {})", win->minSize().width(),
               win->minSize().height());
  std::println("maxSize: ({}, {})", win->maxSize().width(),
               win->maxSize().height());
  std::println("wantsInput: {}", win->wantsInput());
  std::println("transient: {}", win->transient());
  std::println("modal: {}", win->modal());
  std::println("move: {}", win->move());
  std::println("resize: {}", win->resize());
  std::println("decorationHasAlpha: {}", win->decorationHasAlpha());
  std::println("providesContextHelp: {}", win->providesContextHelp());
  std::println("maximizable: {}", win->maximizable());
  std::println("moveable: {}", win->moveable());
  std::println("moveableAcrossScreens: {}", win->moveableAcrossScreens());
  std::println("resizeable: {}", win->resizeable());
  std::println("desktopFileName: {}", win->desktopFileName().toStdString());
  std::println("hasApplicationMenu: {}", win->hasApplicationMenu());
  std::println("applicationMenuActive: {}", win->applicationMenuActive());
  std::println("unresponsive: {}", win->unresponsive());
  std::println("colorScheme: {}", win->colorScheme().toStdString());

  delete win;
}
