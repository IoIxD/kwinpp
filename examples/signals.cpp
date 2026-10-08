#include "kwinpp.hpp"
#include <print>

#ifdef __x86_64__
#include <emmintrin.h>
#endif

using namespace KWin;

int main() {
  kwinpp::Connection c = workspace.onWindowActivated([](Window *win) {
    if (win)
      std::println("activated: {}", win->caption());
  });

  for (;;) {
#ifdef __x86_64__
    _mm_pause();
#endif
  }
  c.disconnect();
}