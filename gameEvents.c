#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "headers/gameEvents.h"
#include "headers/game.h"
#include "headers/characters.h"
#include "headers/projectiles.h"

void eventManager(SDL_Event event, int *mainScreen, player* player, caseg grid[20][20], Projectiles* projectiles, int colorKey){
  Uint8 *keystates = SDL_GetKeyState(NULL);
  if (event.type == SDL_QUIT) {
    eventQuit(mainScreen);
  }
  if (keystates[SDLK_ESCAPE]) {
      eventQuit(mainScreen);
  }
  if (keystates[SDLK_UP]) {
      eventPlayerMovement(player, 0, grid);
  }
  else if (keystates[SDLK_RIGHT]) {
      eventPlayerMovement(player, 1, grid);
  }
  else if (keystates[SDLK_DOWN]) {
      eventPlayerMovement(player, 2, grid);
  }
  else if (keystates[SDLK_LEFT]) {
      eventPlayerMovement(player, 3, grid);
  }
  if (keystates[SDLK_SPACE] && player->curFireDelay == 0) {
      consProjectilePlayer(projectiles, colorKey, player, player->size.y / 50);
      player->curFireDelay = player->fireDelay;
  }
  if (event.type == SDL_KEYUP) {
    switch (event.key.keysym.sym) {
    case SDLK_UP:
    case SDLK_RIGHT:
    case SDLK_DOWN:
    case SDLK_LEFT:
      resetPlayerSprite(player);
      break;
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
