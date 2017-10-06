#ifndef GAME
#define GAME

#include "SDL.h"

typedef struct __player player;
struct __player {
  SDL_Surface *skin;
  SDL_Rect position;
  SDL_Rect size;
  int spriteDelay;
  int health;
};

typedef struct __case caseg;
struct __case {
  int inaccesibble;
  int xvalue;
  int yvalue;
};

int gameInit(char* fileName);
void mainGame(int* entry);
void gameGridFiller(int* entry, caseg gameGrid[20][20]);

#endif
