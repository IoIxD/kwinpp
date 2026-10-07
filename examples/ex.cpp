#include "kwinpp.hpp"

using namespace KWin;

int main() {
  auto win = workspace.activeWindow();
  printf("%0.2f\n", win->size().width());
}
