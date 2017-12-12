#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "headers/gameEvents.h"
#include "headers/game.h"
#include "headers/characters.h"
#include "headers/projectiles.h"
#include "headers/menus.h"
#define PAUSE_DELAY_EN 10
#define PAUSE_DELAY_DI 90

void eventManager(SDL_Event event, int *mainScreen, player* player, caseg grid[20][20], Projectiles* projectiles, int colorKey, int* gameOverDelay, Enemies* enemies, int* entry, int* pause, int* pauseDelay, menuCursor* pauseCursor, int* gameOver, int* mainMenu, menuCursor* gameOverCursor){
  Uint8 *keystates = SDL_GetKeyState(NULL);
  if (event.type == SDL_QUIT) {
    eventQuit(mainScreen);
    eventQuit(mainMenu);
  }
  if (*gameOver) {
    if (keystates[SDLK_UP]) {
      gameOverMenuMovement(gameOverCursor, 2);
    }
    else if (keystates[SDLK_DOWN]) {
      gameOverMenuMovement(gameOverCursor, 1);
    }
    if (keystates[SDLK_RETURN]) {
      if (gameOverCursor->valueCursor == 1) {
	resetGame(projectiles, enemies, player, gameOverDelay, entry);
      }
      else {
	eventQuit(mainScreen);
      }
      *gameOver = 0;
    }
  }
  else {
    if (*pauseDelay == 0 && keystates[SDLK_ESCAPE]) {
      if (*pause == 0) {
	*pause = 1;
	*pauseDelay = PAUSE_DELAY_EN;
      }
      else {
	*pause = 0;
	*pauseDelay = PAUSE_DELAY_DI;
      }
    }
    if (!*pause) {
      if (player->health > 0 && keystates[SDLK_UP]) {
	eventPlayerMovement(player, 0, grid);
      }
      else if (player->health > 0 && keystates[SDLK_RIGHT]) {
	eventPlayerMovement(player, 1, grid);
      }
      else if (player->health > 0 && keystates[SDLK_DOWN]) {
	eventPlayerMovement(player, 2, grid);
      }
      else if (player->health > 0 && keystates[SDLK_LEFT]) {
	eventPlayerMovement(player, 3, grid);
      }
      if (player->health > 0 && keystates[SDLK_SPACE] && player->curFireDelay == 0) {
	consProjectilePlayer(projectiles, colorKey, player, player->size.y / 50, 0, NULL);
	player->curFireDelay = player->fireDelay;
      }
      if (player->health > 0 && event.type == SDL_KEYUP) {
	switch (event.key.keysym.sym) {
	case SDLK_UP:
	case SDLK_RIGHT:
	case SDLK_DOWN:
	case SDLK_LEFT:
	  resetPlayerSprite(player);
	  break;
	default: //deletes the warnings for the unused keys in gcc
	  break;
	}
      }
    }
    else {
      if (keystates[SDLK_UP]) {
	pauseMenuMovement(pauseCursor, 2);
      }
      else if (keystates[SDLK_DOWN]) {
	pauseMenuMovement(pauseCursor, 1);
      }
      if (keystates[SDLK_RETURN]) {
	if (pauseCursor->valueCursor == 1) {
	}
	else if (pauseCursor->valueCursor == 2) {
	  resetGame(projectiles, enemies, player, gameOverDelay, entry);
	}
	else {
	  eventQuit(mainScreen);
	}
	*pause = 0;
      }
    }
  }
}

void eventManagerMenu(SDL_Event event, int* mainMenu, menuCursor* mainCursor, int* startGame, int* scoreMenu) {
  Uint8 *keystates = SDL_GetKeyState(NULL);
  if (event.type == SDL_QUIT) {
    eventQuit(mainMenu);
  }
  if (*scoreMenu == 0) {
    if (keystates[SDLK_UP]) {
      mainMenuMovement(mainCursor, 2);
    }
    else if (keystates[SDLK_DOWN]) {
      mainMenuMovement(mainCursor, 1);
    }
    if (keystates[SDLK_RETURN]) {
      if (mainCursor->valueCursor == 1) {
	*startGame = 1;
      }
      else if (mainCursor->valueCursor == 2) {
	*scoreMenu = 1;
      }
      else {
	eventQuit(mainMenu);
      }
    }
  }
  else {
    if (keystates[SDLK_RETURN]) {
      *scoreMenu = 0;
    }
  }
}

void eventPlayerMovement(player* player, int dir, caseg grid[20][20]) {
  switch (dir) {
  case 0:
    player->size.y = 0;
    if (player->position.y > 0 && !playerCollision(player, grid, dir)) {
      player->position.y--;
    }
    break;
  case 1:
    player->size.y = 50;
    if (player->position.x < 1000 && !playerCollision(player, grid, dir)) {
      player->position.x++;
    }
    break;
 case 2:
   player->size.y = 100;
    if (player->position.y < 1000 && !playerCollision(player, grid, dir)) {
      player->position.y++;
    }
    break;
 case 3:
   player->size.y = 150;
    if (player->position.x > 0 && !playerCollision(player, grid, dir)) {
      player->position.x--;
    }
    break;
  }
  if (player->spriteDelay >= SPRITEDELAY) {
    if (player->size.x >= 150) {
      player->size.x = 0;
    }
    else {
      player->size.x += 50;
    }
    player->spriteDelay = 0;
  }
  else {
    player->spriteDelay++;
  }
}

void eventQuit(int *mainScreen) {
  *mainScreen = 0;
}

void resetPlayerSprite(player* player) {
  player->spriteDelay = SPRITEDELAY;
}
