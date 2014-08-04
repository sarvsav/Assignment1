#include <SDL/SDL.h>
#include <stdio.h>

int main(int argc, char *argv[])
  {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface* screen;
    const int ScreenWidth = 640;
    const int ScreenHeight = 480;
    screen = SDL_SetVideoMode(ScreenWidth, ScreenHeight, 32, SDL_SWSURFACE);
    bool running = true;
    const int FPS = 30;

    Uint32 start;
    SDL_Rect rect;
    rect.w = 20;
    rect.h = 20;
    rect.x = ScreenWidth/2 - rect.w/2;
    rect.y = ScreenHeight/2 - rect.h/2;

    Uint32 ScreenColor = SDL_MapRGB(screen->format, 0xcf, 0xcf, 0xcf);
    Uint32 RectColor;

    int rounds = 1;
    int time1 = 0;

    while (running) {
      start = SDL_GetTicks();
      SDL_Event event;

      while (SDL_PollEvent(&event))
      {
        switch (event.type) {
          case SDL_QUIT: running = false;
            break;
        }
      }

      if (start > time1 + 5000) {
        if (rounds >= 3) // Resets color counter
          rounds = 1;
        else
          rounds++;

        time1 = start;
      }

      switch (rounds) {
        case 1: RectColor = SDL_MapRGB(screen->format, 255, 0, 0);
          break;
        case 2: RectColor = SDL_MapRGB(screen->format, 0, 255, 0);
          break;
        case 3: RectColor = SDL_MapRGB(screen->format, 0, 0, 255);
          break;
      }

      SDL_FillRect(screen, &screen->clip_rect, ScreenColor);
      SDL_FillRect(screen, &rect, RectColor);

      SDL_Flip(screen);
        if (1000/FPS > SDL_GetTicks()-start)
          SDL_Delay (1000/FPS-(SDL_GetTicks()-start));
    }

    SDL_Quit();
    return 0;
}