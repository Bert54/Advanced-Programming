#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SDL.h"
#include "libraries/SDL_ttf/SDL_ttf.h"
#include "headers/entryReader.h"
#include "headers/game.h"
#include "headers/gameEvents.h"
#include "headers/scenePlacement.h"
#include "headers/characters.h"
#include "headers/projectiles.h"
#include "headers/menus.h"
#define DEFAULT_SPAWNRATE 100
#define DEFAULT_MAXENEMIES 2000
#define GAMEOVERDELAY 800
#define MENU_ENTER_DELAY 100

int mainMenu() {
  SDL_Surface* menuSplash, *screen, *surfaceLoader;
  SDL_Event eventMenu;
  menuCursor menuCursor;
  int colorKey, mainMenu = 1, startGame = 0, enterDelay = 0;
  char* file = "content/entry/entry.txt";
  srand(time(NULL)); 
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  SDL_WM_SetCaption("Lone Hero","Lone Hero");
  screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0);
  colorKey = SDL_MapRGB(screen->format, 255, 0, 255);
  surfaceLoader = SDL_LoadBMP("content/menu/main.bmp");
  menuSplash = SDL_DisplayFormat(surfaceLoader);
  SDL_FreeSurface(surfaceLoader);
  initMainMenuCursor(&menuCursor, colorKey);
  while (mainMenu) {
    if (enterDelay == 0 && SDL_PollEvent(&eventMenu)) {
      eventManagerMenu(eventMenu, &mainMenu, &menuCursor, &startGame);
    }
    if (enterDelay > 0) {
      enterDelay--;
    }
    if (startGame == 1) {
      gameInit(file, colorKey, screen, &mainMenu);
      startGame = 0;
      enterDelay = MENU_ENTER_DELAY;
    }
    SDL_FillRect(screen,NULL,0x000000);
    SDL_BlitSurface(menuSplash, NULL, screen, NULL);
    SDL_BlitSurface(menuCursor.cursor, NULL, screen, &(menuCursor.posCursor));
    SDL_UpdateRect(screen, 0, 0, 0, 0);
  }
  SDL_FreeSurface(menuCursor.cursor);
  TTF_Quit();
  SDL_Quit();
  return 1;
}

int gameInit(char* fileName, int colorKey, SDL_Surface *screen, int* mainMenu) {
  FILE* file = NULL;
  if (fileOpener(&file, fileName) == -1) {
    return EXIT_FAILURE;
  }
  else {
    int* entry = fileReader(file);
    if (entry != NULL) {
      mainGame(entry, colorKey, screen, mainMenu);
    }
    else {
      return EXIT_FAILURE;
    }
    arrayCleaner(&entry);
  }
  fileCloser(&file);
  return 1;
}

void mainGame(int* entry, int colorKey, SDL_Surface *screen, int* mainMenu) {
  int mainScreen = 1, nbSpawners = 0, nbEnemies, maxEnemies, spawnRate, goCounter = 0, gameOverDelay = GAMEOVERDELAY, pause = 0, pauseDelay = 0;
  int gameOver = 0, lowHealthCurColor = 0, lowHealthAnim = 0, enemySpawnAnimDelay;
  caseg gameGrid[20][20];
  SDL_Event eventGame;
  SDL_Surface *surfaceLoader, *ground, *wall, *enemySpawn = NULL;
  SDL_Rect posWall, posEnSpawn, enemySpawnAnim;
  player player;
  Projectiles *projectiles = malloc(sizeof(Projectiles));
  Enemies *enemies = malloc(sizeof(Enemies));
  DeadEnemies dEnemies = initDeadQueue(dEnemies);
  menuCursor pauseCursor, gameOverCursor;
  TTF_Font *statFont = NULL;
  Stats stats;
  SDL_Color whiteText = {255, 255, 255}, redText = {255, 0, 0};
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
  initPauseMenuCursor(&pauseCursor, colorKey);
  initGameOverCursor(&gameOverCursor, colorKey);
  nbEnemies = 0;
  maxEnemies = DEFAULT_MAXENEMIES;
  spawnRate = DEFAULT_SPAWNRATE;
  statFont = TTF_OpenFont ("content/font/Final-Fantasy.ttf", 20);
  surfaceLoader = SDL_LoadBMP("content/scene/enemy_spawn.bmp");
  enemySpawn = SDL_DisplayFormat(surfaceLoader);
  SDL_FreeSurface(surfaceLoader);
  SDL_SetColorKey(enemySpawn, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorKey);
  initEnemySpawnSprite(&enemySpawnAnimDelay, &posEnSpawn, &enemySpawnAnim);
  while (mainScreen) {
    if (SDL_PollEvent(&eventGame)) {
      eventManager(eventGame, &mainScreen, &player, gameGrid, projectiles, colorKey, &gameOverDelay, enemies, entry, &pause, &pauseDelay, &pauseCursor, &gameOver, mainMenu, &gameOverCursor);
    }
    if (pauseDelay > 0) {
	pauseDelay--;
    }
    if (gameOver) {
      displayGameOverMenu(screen, &gameOverCursor, player);
    }
    else if (pause) {
      displayPauseMenu(screen, &pauseCursor);
    }
    else {
      projectileHit(enemies, &player, projectiles, &dEnemies, colorKey);
      if (player.health <= 0)  {
	if (goCounter == 0) {
	  playerGameOverAnim(&player);
	  goCounter = 200;
	}
	else {
	  goCounter--;
	}
	if (gameOverDelay > 0) {
	  gameOverDelay--;
	}
	else {
	  nbEnemies = 0;
	}
	if (gameOverDelay <= 0) {
	  gameOver = 1;
	}
      }
      if (player.curFireDelay > 0) {
	player.curFireDelay--;
      }
      if (nbEnemies < maxEnemies) {
	generateEnemy(enemies, gameGrid, spawnRate, &nbEnemies, colorKey);
      }
      SDL_FillRect(screen,NULL,0x000000);
      SDL_BlitSurface(ground, NULL, screen, NULL);
      wallPlacement(entry, *screen, *wall, &posWall);
      enemySpawnPlacement(entry, &enemySpawnAnimDelay, *screen, *enemySpawn, posEnSpawn, &enemySpawnAnim);
      if (!dEnemies.empty) {
	updateDeadQueue(screen, &dEnemies);
      }
      if (player.health <= 0) {
	SDL_BlitSurface(player.skin, &(player.size), screen, &(player.position));
      }
      displayEnemies(screen, enemies, gameGrid, &player, projectiles, colorKey);
      displayProjectiles(screen, projectiles, gameGrid);
      updateStats(&stats, whiteText, redText, statFont, player, &lowHealthAnim, &lowHealthCurColor);
      displayStats(stats, screen);
      if (player.health > 0) {
	SDL_BlitSurface(player.skin, &(player.size), screen, &(player.position));
      }
    }
    SDL_UpdateRect(screen, 0, 0, 0, 0);
  }
  freePlayer(&player);
  destroyProjectilesList(projectiles);
  destroyDeadQueue(&dEnemies);
  free(projectiles);
  destroyEnemyList(enemies);
  free(enemies);
  SDL_FreeSurface(pauseCursor.cursor);
  SDL_FreeSurface(gameOverCursor.cursor);
  SDL_FreeSurface(ground);
  SDL_FreeSurface(wall);
  TTF_CloseFont(statFont);
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

void resetGame(Projectiles* projectiles, Enemies* enemies, player* player, int* gameOverDelay, int* entry) {
  destroyProjectilesList(projectiles);
  destroyEnemyList(enemies);
  consEmptyProjectilesList(projectiles);
  consEmptyEnemyList(enemies);
  resetPlayer(player, entry);
  *gameOverDelay = GAMEOVERDELAY;
}

void updateStats(Stats* stats, SDL_Color statColor, SDL_Color lowHealthColor, TTF_Font *statFont, player player, int* lowHealthAnim, int* lowHealthCurColor) {
  char statCopy[500];
  sprintf(statCopy, "Score - %d", player.score);
  stats->score = TTF_RenderText_Solid(statFont, statCopy, statColor); 
  stats->posScore.x = 50;
  stats->posScore.y = 10;
  if (player.health > 0) { 
    if (player.health > 3 || *lowHealthCurColor == 0) {
      sprintf(statCopy, "Health - %d", player.health);
      stats->health = TTF_RenderText_Solid(statFont, statCopy, statColor);
    }
    else {
      sprintf(statCopy, "Health - %d", player.health);
      stats->health = TTF_RenderText_Solid(statFont, statCopy, lowHealthColor);
    }
    if (*lowHealthAnim == 100) {
      if (*lowHealthCurColor == 0) {
	*lowHealthCurColor = 1;
      }
      else {
	*lowHealthCurColor = 0;
      }
      *lowHealthAnim = 0;
    }
    else {
      *lowHealthAnim = *lowHealthAnim + 1;
    }
  }
  if (player.health == 0) {
    sprintf(statCopy, "Health - %d", player.health);
    stats->health = TTF_RenderText_Solid(statFont, statCopy, lowHealthColor);
  }
  stats->posHealth.x = 350;
  stats->posHealth.y = 10;
}

void displayStats(Stats stats, SDL_Surface* screen) {
  SDL_BlitSurface(stats.score, NULL, screen, &(stats.posScore));
  SDL_BlitSurface(stats.health, NULL, screen, &(stats.posHealth));
}
