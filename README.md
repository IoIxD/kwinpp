# kwinpp

Small library for using the KWin scripting API via C++, allowing people to write apps that use KDE-specific information like window size/positioning and cursor position. It works by registering a KWin script (via dbus) that bridges a set of dbus calls to functions inside the script that dispatch the results.

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
