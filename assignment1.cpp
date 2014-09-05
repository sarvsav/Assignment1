
#include <SDL/SDL.h>
#include <stdio.h>

#define SCREENDIVIDER 2
#define RECTANGLE_WIDTH 20
#define INTERVAL_TIME 5000
#define MAX_COLORS 3

typedef enum _BoxColor { RED = 1,
                         GREEN,
                         BLUE} BoxColor;

BoxColor color_timer(Uint32 & start, int & time2, BoxColor color);
int render_screen(SDL_Surface screen, SDL_Rect rect, Uint32 ScreenColor, Uint32 RectColor);


// ------------------------------------
// Main function
// ------------------------------------
int main(int argc, char *argv[])
{
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Surface* screen;
  const int ScreenWidth = 640;
  const int ScreenHeight = 480;
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
  Uint32 RectColor;

  int time1 = 0;

  Uint32 * pstart = &start;
  int * ptime1 = &time1;
  
  while (running)
  {
    start = SDL_GetTicks();
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
      switch (event.type) {
        case SDL_QUIT: running = false;
          break;
      }
    }

    boxcolor = color_timer(start, time1, boxcolor);

    switch (boxcolor) {
      case RED: RectColor = SDL_MapRGB(screen->format, 255, 0, 0);
        break;
      case BLUE: RectColor = SDL_MapRGB(screen->format, 0, 255, 0);
        break;
      case GREEN: RectColor = SDL_MapRGB(screen->format, 0, 0, 255);
        break;
    }

    render_screen(SDL_Surface screen);

    if (1000/FPS > SDL_GetTicks()-start)
      SDL_Delay (1000/FPS-(SDL_GetTicks()-start));
  }
  
  SDL_Quit();
  return 0;
}

// ------------------------------------
// Screen rendering
// ------------------------------------
int render_screen(SDL_Surface screen, SDL_Rect rect, Uint32 ScreenColor, Uint32 RectColor)
{
  SDL_FillRect(screen, &screen->clip_rect, ScreenColor);
  SDL_FillRect(screen, &rect, RectColor);
  SDL_Flip(screen);

  return 0;
}

// ------------------------------------
// Color logic
// ------------------------------------
BoxColor color_timer(Uint32 & start, int & time1, BoxColor color)
{
  if (start > time1 + INTERVAL_TIME) {
      if (color >= MAX_COLORS) // Resets color counter
        color = RED;
      else
        color = (BoxColor)((int)(color)+1); // Find some alternative
      time1 = start;
    }
    return color;
}