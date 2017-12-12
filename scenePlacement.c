#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#define ENEMY_SPAWN_SIZE_WIDTH 50
#define ENEMY_SPAWN_SIZE_HEIGHT 50
#define ENEMY_SPAWN_ANIM_DELAY 10
#define ENEMY_SPAWN_NB_FRAMES 10

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

void initEnemySpawnSprite(int* delay, SDL_Rect* posEnSpawn, SDL_Rect* enemySpawnAnim) {
  posEnSpawn->x = 0;
  posEnSpawn->y = 0;
  enemySpawnAnim->x = 0;
  enemySpawnAnim->y = 0;
  enemySpawnAnim->w = ENEMY_SPAWN_SIZE_WIDTH;
  enemySpawnAnim->h = ENEMY_SPAWN_SIZE_HEIGHT;
  *delay = ENEMY_SPAWN_ANIM_DELAY;
}

void enemySpawnPlacement(int* entry, int* delay, SDL_Surface screen, SDL_Surface enemySpawn, SDL_Rect posEnSpawn, SDL_Rect* enemySpawnAnim) {
  int i = 0;
  if (*delay == 0) {
    if (enemySpawnAnim->x / ENEMY_SPAWN_SIZE_WIDTH >= ENEMY_SPAWN_NB_FRAMES - 1) {
      enemySpawnAnim->x = 0;
    }
    else {
      enemySpawnAnim->x = enemySpawnAnim->x + ENEMY_SPAWN_SIZE_WIDTH;
    }
    *delay = ENEMY_SPAWN_SIZE_WIDTH;
  }
  else {
    *delay = *delay - 1;
  }
  while (entry[i] != 3) {
    switch (entry[i]) {
    case 5:
      SDL_BlitSurface(&enemySpawn, enemySpawnAnim, &screen, &posEnSpawn);
      SDL_UpdateRect(&screen, 0, 0, 0, 0);
      posEnSpawn.x += 50;
      break;
    case 2:
      posEnSpawn.x = 0;
      posEnSpawn.y += 50;
      break;
    default:
      posEnSpawn.x += 50;
    }
    i++;
  }
}
