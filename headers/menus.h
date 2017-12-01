#ifndef MENUS
#define MENUS

#include "SDL.h"

typedef struct __menuCursor menuCursor;

struct __menuCursor {
  SDL_Surface* cursor;
  SDL_Rect posCursor;
  int cursorWidth;
  int cursorHeight;
  int valueCursor;
};

void initMainMenuCursor(menuCursor* cursor, int colorKey);
void displayPauseMenu(SDL_Surface* screen, menuCursor* pauseCursor);
void initPauseMenuCursor(menuCursor* cursor, int colorKey);
void pauseMenuMovement(menuCursor* cursor, int dir);
void mainMenuMovement(menuCursor* cursor, int dir);

#endif
