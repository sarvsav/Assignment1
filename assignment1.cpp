#include <SDL/SDL.h>
#include <stdio.h>

#define SCREENDIVIDER 2
#define RECTANGLE_WIDTH 20
#define INTERVAL_TIME 5000
#define MAX_COLORS 3

const int ScreenWidth = 640;
const int ScreenHeight = 480;


typedef enum _BoxColor { RED = 1,
                         GREEN,
                         BLUE} BoxColor;

int main(int argc, char *argv[])
{
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Surface* screen;
  screen = SDL_SetVideoMode(ScreenWidth, ScreenHeight, 32, SDL_SWSURFACE);
  bool running = true;
  const int FPS = 30;
  BoxColor boxcolor;
  boxcolor = RED;

  Uint32 start;
  SDL_Rect rect;
  rect.w = RECTANGLE_WIDTH;
  rect.h = RECTANGLE_WIDTH;
  rect.x = ScreenWidth/SCREENDIVIDER - rect.w/SCREENDIVIDER;
  rect.y = ScreenHeight/SCREENDIVIDER - rect.h/SCREENDIVIDER;

  Uint32 ScreenColor = SDL_MapRGB(screen->format, 0xcf, 0xcf, 0xcf);

  int time1 = 0;

  while (running) {
    start = SDL_GetTicks();
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT: running = false;
          break;
      }
    }

    boxcolor = boxcolor_function(boxcolor);

    boxcolor_render(boxcolor);

    SDL_Flip(screen);
    if (1000/FPS > SDL_GetTicks()-start)
      SDL_Delay (1000/FPS-(SDL_GetTicks()-start));
  }

  SDL_Quit();
  return 0;
}


int boxcolor_function(start, time1, boxcolor)
{
  if (start > time1 + INTERVAL_TIME) {
    if (boxcolor >= MAX_COLORS) // Resets color counter
      boxcolor = RED;
    else
      boxcolor = (BoxColor)((int)(boxcolor)+1); // Find some alternative

    time1 = start;
  }

  return boxcolor;
}


int boxcolor_render(color)
{
  Uint32 RectColor;

  switch (color) {
    case RED: RectColor = SDL_MapRGB(screen->format, 255, 0, 0);
      break;
    case BLUE: RectColor = SDL_MapRGB(screen->format, 0, 255, 0);
      break;
    case GREEN: RectColor = SDL_MapRGB(screen->format, 0, 0, 255);
      break;
  }

  SDL_FillRect(screen, &screen->clip_rect, ScreenColor);
  SDL_FillRect(screen, &rect, RectColor);

  return 0;
}