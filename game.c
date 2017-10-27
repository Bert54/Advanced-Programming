#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SDL.h"
#include "headers/entryReader.h"
#include "headers/game.h"
#include "headers/gameEvents.h"
#include "headers/scenePlacement.h"
#include "headers/characters.h"
#include "headers/projectiles.h"
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
#define DEFAULT_SPAWNRATE 500
#define DEFAULT_MAXENEMIES 2000

int gameInit(char* fileName) {
  FILE* file = NULL;
  if (fileOpener(&file, fileName) == -1) {
    return EXIT_FAILURE;
  }
  else {
    int* entry = fileReader(file);
    if (entry != NULL) {
      mainGame(entry);
    }
    else {
      return EXIT_FAILURE;
    }
    arrayCleaner(&entry);
  }
  fileCloser(&file);
  return 1;
}

void mainGame(int* entry) {
  int mainScreen = 1, colorKey, nbSpawners = 0, nbEnemies, maxEnemies, spawnRate, goCounter = 0;
  caseg gameGrid[20][20];
  SDL_Event eventGame;
  SDL_Surface *screen, *surfaceLoader, *ground, *wall;
  SDL_Rect posWall;
  player player;
  Projectiles *projectiles = malloc(sizeof(Projectiles));
  Enemies *enemies = malloc(sizeof(Enemies));
  srand(time(NULL)); 
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption("Survival Shooter","Survival Shooter");
  screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0);
  colorKey = SDL_MapRGB(screen->format, 255, 0, 255);
  gameGridFiller(entry, gameGrid, &nbSpawners);
  surfaceLoader = SDL_LoadBMP("content/scene/grass.bmp");
  ground = SDL_DisplayFormat(surfaceLoader);
  SDL_FreeSurface(surfaceLoader);
  surfaceLoader = SDL_LoadBMP("content/scene/wall.bmp");
  wall = SDL_DisplayFormat(surfaceLoader);
  SDL_FreeSurface(surfaceLoader);
  initPlayer(&player, entry, colorKey);
  SDL_EnableKeyRepeat(1, 6);
  consEmptyProjectilesList(projectiles);
  consEmptyEnemyList(enemies);
  nbEnemies = 0;
  maxEnemies = DEFAULT_MAXENEMIES;
  spawnRate = DEFAULT_SPAWNRATE;
  while (mainScreen) {
    projectileHit(enemies, &player, projectiles);
    if (player.health <= 0)  {
      if (goCounter == 0) {
	playerGameOverAnim(&player);
	goCounter = 200;
      }
      else {
	goCounter--;
      }
    }
    if (player.curFireDelay > 0) {
      player.curFireDelay--;
    }
    if (SDL_PollEvent(&eventGame)) {
      eventManager(eventGame, &mainScreen, &player, gameGrid, projectiles, colorKey);
    }
    if (nbEnemies < maxEnemies) {
      generateEnemy(enemies, gameGrid, spawnRate, &nbEnemies, colorKey);
    }
    SDL_FillRect(screen,NULL,0x000000);
    SDL_BlitSurface(ground, NULL, screen, NULL);
    wallPlacement(entry, *screen, *wall, &posWall);
    if (player.health <= 0) {
      SDL_BlitSurface(player.skin, &(player.size), screen, &(player.position));
    }
    displayEnemies(screen, enemies, gameGrid, &player, projectiles, colorKey);
    displayProjectiles(screen, projectiles, gameGrid);
    if (player.health > 0) {
      SDL_BlitSurface(player.skin, &(player.size), screen, &(player.position));
    }
    SDL_UpdateRect(screen, 0, 0, 0, 0);
  }
  freePlayer(&player);
  destroyProjectilesList(projectiles);
  destroyEnemyList(enemies);
  SDL_FreeSurface(ground);
  SDL_FreeSurface(wall);
  SDL_Quit();
}

void gameGridFiller(int* entry, caseg gameGrid[20][20], int* nbSpawners) {
  int i = 0;
  int j = 0;
  int k = 0;
  while(entry[i] != 3) {
    switch (entry[i]) {
    case 1:
      gameGrid[j][k].inaccesibble = 1;
      gameGrid[j][k].xvalue = j * 50;
      gameGrid[j][k].yvalue = k * 50;
      j++;
      break;
    case 2:
      j = 0;
      k++;
      break;
    case 5:
      nbSpawners++;
      gameGrid[j][k].inaccesibble = 2;
      gameGrid[j][k].xvalue = j * 50;
      gameGrid[j][k].yvalue = k * 50;
      j++;
      break;
    default:
      gameGrid[j][k].inaccesibble = 0;
      gameGrid[j][k].xvalue = j * 50;
      gameGrid[j][k].yvalue = k * 50;
      j++;
    }
    i++;
  }
}
