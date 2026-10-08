# kwinpp

Small library for using the KWin scripting API via C++, allowing people to write apps that use KDE-specific information like window size/positioning and cursor position (without having to go through KWin's Javascript API directly). It works by registering a KWin script (via dbus) that bridges a set of dbus calls to functions inside the script that dispatch the results.

The API mirrors mostly mirrors that of KWin scripting:

```c++
#include <kwinpp.hpp>
#include <print>

using namespace KWin;

int main() {
  Window *win = workspace.activeWindow();

  std::println("window x: {}", win->x());
  std::println("window y: {}", win->y());
  std::println("window width: {}", win->width());
  std::println("window height: {}", win->height());
}
```

Signals are exposed as `on<Signal>()` functions taking a callback:

```c++
kwinpp::Connection c = workspace.onWindowActivated([](Window *win) {
  if (win)
    std::println("activated: {}", win->caption());
});
// ...
c.disconnect();
```

The library dynloads the one dependency it actually has (libdbus) and, by default, uses C++20 (+ nlohmann::json) to avoid actually linking to Qt.
However, it does support linking to Qt if one is actually building a Qt application, at which point it just needs C++17.
