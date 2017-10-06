#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"

void wallPlacement(int* entry, SDL_Surface screen, SDL_Surface wall, SDL_Rect posWall){
  int i = 0;
  posWall.x = 0;
  posWall.y = 0;
  while (entry[i] != 3) {
    switch (entry[i]) {
    case 1:
      SDL_BlitSurface(&wall, NULL, &screen, &posWall);
      SDL_UpdateRect(&screen, 0, 0, 0, 0);
      posWall.x += 50;
      break;
    case 2:
      posWall.x = 0;
      posWall.y += 50;
      break;
    default:
      posWall.x += 50;
    }
    i++;
  }
}
