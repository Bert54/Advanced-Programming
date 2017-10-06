#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "game.h"
#include "characters.h"

void initPlayer (player* player, int* entry, int colorKey) {
  SDL_Surface *surfaceLoader = SDL_LoadBMP("content/character/player.bmp");
  int i = 0, placed = 0;
  player->skin = SDL_DisplayFormat(surfaceLoader);
  SDL_FreeSurface(surfaceLoader);
  SDL_SetColorKey(player->skin, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorKey);
  player->position.x = 0;
  player->position.y = 0;
  player->size.x = 0;
  player->size.y = 0;
  player->size.w = 50;
  player->size.h = 50;
  player->spriteDelay = SPRITEDELAY;
  while (entry[i] != 3 && !placed) {
    if (entry[i] == 4) {
      placed = 1;
    }
    else if (entry[i] == 2) {
      player->position.x = 0;
      player->position.y += 50;
    }
    else {
      player->position.x += 50;
    }
    i++;
  }
  if (!placed) {
    i = 0;
    player->position.x = 0;
    player->position.y = 0;
    while (entry[i] != 3 && !placed) {
      if (entry[i] == 0) {
	placed = 1;
      }
      else if (entry[i] == 2) {
      player->position.x = 0;
      player->position.y += 50;
      }
      else {
	player->position.x += 50;
      }
      i++;
    }
  }
  player->health = 100;
}

void freePlayer(player* player) {
  SDL_FreeSurface(player->skin);
}

int playerCollision (player* player, caseg grid[20][20], int dir) {
  int i, j;
  switch (dir) {
  case 0:
    for (i=0;i<20;i++) {
      for (j=0;j<20;j++) {
	if (grid[j][i].inaccesibble == 1 && player->position.y-1 == grid[j][i].yvalue+49 && player->position.x-10 >= grid[j][i].xvalue && player->position.x+10 <= grid[j][i].xvalue + 49) {
	    return 1;
	}
	if (grid[j+1][i].inaccesibble == 1 && player->position.y-1 == grid[j+1][i].yvalue+49 && player->position.x+40 >= grid[j+1][i].xvalue && player->position.x+40 <= grid[j+1][i].xvalue + 49) {
	  return 1;
	}
      }
    }
    break;
  case 1:
    for (i=0;i<20;i++) {
      for (j=0;j<20;j++) {
	if (grid[j][i].inaccesibble == 1 && player->position.x+41 == grid[j][i].xvalue && player->position.y >= grid[j][i].yvalue && player->position.y <= grid[j][i].yvalue + 49) {
	  return 1;
	}
	if (grid[j][i+1].inaccesibble == 1 && player->position.x+41 == grid[j][i+1].xvalue && player->position.y+48 >= grid[j][i+1].yvalue && player->position.y <= grid[j][i+1].yvalue + 1) {
	  return 1;
	}
      }
    }
    break;
  case 2:
    for (i=0;i<20;i++) {
      for (j=0;j<20;j++) {
	if (grid[j][i].inaccesibble == 1 && player->position.y+49 == grid[j][i].yvalue && player->position.x-10 >= grid[j][i].xvalue && player->position.x+10 <= grid[j][i].xvalue + 49) {
	  return 1;
	}
	if (grid[j+1][i].inaccesibble == 1 && player->position.y+49 == grid[j+1][i].yvalue && player->position.x+38  >= grid[j+1][i].xvalue && player->position.x+38 <= grid[j+1][i].xvalue + 49) {
	  return 1;
	}
      }
    }
    break;
  case 3:
    for (i=0;i<20;i++) {
      for (j=0;j<20;j++) {
	if (grid[j][i].inaccesibble == 1 && player->position.x+9 == grid[j][i].xvalue+49 && player->position.y >= grid[j][i].yvalue && player->position.y <= grid[j][i].yvalue + 49) {
	  return 1;
	}
	if (grid[j][i+1].inaccesibble == 1 && player->position.x+9 == grid[j][i+1].xvalue+49 && player->position.y+48 >= grid[j][i+1].yvalue && player->position.y + 50 <= grid[j][i+1].yvalue + 49) {
	  return 1;
	}
      }
    }
    break;
  }
  return 0;
}
