#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "headers/game.h"
#include "headers/menus.h"
#define PAUSE_SPLASH_SIZE_W 800
#define PAUSE_SPLASH_SIZE_H 500
#define PAUSE_CURSOR_W 500
#define PAUSE_CURSOR_H 160
#define MAIN_CURSOR_W 450
#define MAIN_CURSOR_H 150

void initMainMenuCursor(menuCursor* cursor, int colorKey) {
  SDL_Surface *surfaceLoader = SDL_LoadBMP("content/menu/mainMenuCursor.bmp");
  cursor->cursor = surfaceLoader;
  SDL_SetColorKey(cursor->cursor, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorKey);
  cursor->cursorWidth = MAIN_CURSOR_W;
  cursor->cursorHeight = MAIN_CURSOR_H;
  cursor->valueCursor = 1;
  cursor->posCursor.x = 310;
  cursor->posCursor.y = 615;
}

void displayPauseMenu(SDL_Surface* screen, menuCursor* pauseCursor) {
  SDL_Surface *menuSplash, *surfaceLoader;
  SDL_Rect posMenuSplash;
  surfaceLoader = SDL_LoadBMP("content/menu/pause.bmp");
  menuSplash = SDL_DisplayFormat(surfaceLoader);
  SDL_FreeSurface(surfaceLoader);
  posMenuSplash.x = (int)(WINDOW_WIDTH - PAUSE_SPLASH_SIZE_W) / 2;
  posMenuSplash.y = (int)(WINDOW_HEIGHT - PAUSE_SPLASH_SIZE_H) / 2;
  SDL_BlitSurface(menuSplash, NULL, screen, &posMenuSplash);
  SDL_BlitSurface(pauseCursor->cursor, NULL, screen, &(pauseCursor->posCursor));
  SDL_FreeSurface(menuSplash);
}

void initPauseMenuCursor(menuCursor* cursor, int colorKey) {
  SDL_Surface *surfaceLoader = SDL_LoadBMP("content/menu/pauseMenuCursor.bmp");
  cursor->cursor = surfaceLoader;
  SDL_SetColorKey(cursor->cursor, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorKey);
  cursor->cursorWidth = PAUSE_CURSOR_W;
  cursor->cursorHeight = PAUSE_CURSOR_H;
  cursor->valueCursor = 1;
  cursor->posCursor.x = 240;
  cursor->posCursor.y = 270;
}


void pauseMenuMovement(menuCursor* cursor, int dir) {
  if (dir == 1) {
    if (cursor->valueCursor == 1) {
      cursor->posCursor.y = 415;
      cursor->valueCursor = 2;
    }
    else if (cursor->valueCursor == 2) {
      cursor->posCursor.y = 565;
      cursor->valueCursor = 3;
    }
  }
  else {
    if (cursor->valueCursor == 2) {
      cursor->posCursor.y = 270;
      cursor->valueCursor = 1;
    }
    else if (cursor->valueCursor == 3) {
      cursor->posCursor.y = 415;
      cursor->valueCursor = 2;
    }
  }
}

void mainMenuMovement(menuCursor* cursor, int dir) {
  if (dir == 1) {
    if (cursor->valueCursor == 1) {
      cursor->posCursor.y = 775;
      cursor->valueCursor = 2;
    }
  }
  else {
    if (cursor->valueCursor == 2) {
      cursor->posCursor.y = 615;
      cursor->valueCursor = 1;
    }
  }
}

