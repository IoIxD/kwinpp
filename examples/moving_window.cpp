#include "kwinpp.hpp"

using namespace KWin;

#include <SDL3/SDL.h>
#include <chrono>

int main() {
  SDL_Window *window = NULL;
  SDL_Surface *screenSurface = NULL;
  SDL_Event ev;
  Window *ourWin = nullptr;
  Point p;
  std::chrono::system_clock::time_point timer =
      std::chrono::system_clock::now();

  workspace.onWindowAdded([&](Window *win) {
    if (win->caption() == std::string("___moving_window___")) {
      ourWin = win;
    }
  });

  if (SDL_Init(SDL_INIT_VIDEO) == 0) {
    fprintf(stderr, "could not initialize sdl3: %s\n", SDL_GetError());
    return 1;
  }
  window =
      SDL_CreateWindow("___moving_window___", 32, 32, SDL_WINDOW_BORDERLESS);
  if (window == NULL) {
    fprintf(stderr, "could not create window: %s\n", SDL_GetError());
    return 1;
  }
  screenSurface = SDL_GetWindowSurface(window);

  auto details = SDL_GetPixelFormatDetails(screenSurface->format);
  SDL_FillSurfaceRect(screenSurface, NULL,
                      SDL_MapRGB(details, NULL, 0xFF, 0xFF, 0xFF));

  SDL_UpdateWindowSurface(window);

  for (;;) {
    while (SDL_PollEvent(&ev)) {
      if (ev.type == SDL_EVENT_QUIT) {
        goto exit;
      }
    }

    if (ourWin) {
      std::chrono::system_clock::time_point now =
          std::chrono::system_clock::now();
      p = workspace.cursorPos();

      if ((now - timer).count() >= 2000000) {
        auto rect = ourWin->frameGeometry();
        if (rect.x() > p.x() + 32) {
          rect.setX(rect.x() - 1);
        } else if (rect.x() < p.x() - 64) {
          rect.setX(rect.x() + 1);
        }
        if (rect.y() > p.y() + 32) {
          rect.setY(rect.y() - 1);
        } else if (rect.y() < p.y() - 64) {
          rect.setY(rect.y() + 1);
        }
        ourWin->setFrameGeometry(rect);
        timer = std::chrono::system_clock::now();
      }
    }
  }
exit:

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}