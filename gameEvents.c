#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "gameEvents.h"
#include "game.h"
#include "characters.h"

void eventManager(SDL_Event event, int *mainScreen, player* player, caseg grid[20][20]){
  switch (event.type) {
  case SDL_QUIT:
    eventQuit(mainScreen);
    break;
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_ESCAPE:
      eventQuit(mainScreen);
      break;
    case SDLK_UP:
      eventPlayerMovement(player, 0, grid);
      break;
    case SDLK_RIGHT:
      eventPlayerMovement(player, 1, grid);
      break;
    case SDLK_DOWN:
      eventPlayerMovement(player, 2, grid);
      break;
    case SDLK_LEFT:
      eventPlayerMovement(player, 3, grid);
      break;
    }
    break;
  case SDL_KEYUP:
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
    //player->size.y = 0;
    if (player->position.y > 0 && !playerCollision(player, grid, dir)) {
      player->position.y--;
    }
    break;
  case 1:
    //player->size.y = 50;
    if (player->position.x < 1000 && !playerCollision(player, grid, dir)) {
      player->position.x++;
    }
    break;
 case 2:
   //player->size.y = 100;
    if (player->position.y < 1000 && !playerCollision(player, grid, dir)) {
      player->position.y++;
    }
    break;
 case 3:
   //player->size.y = 150;
    if (player->position.x > 0 && !playerCollision(player, grid, dir)) {
      player->position.x--;
    }
    break;
  }
  if (player->spriteDelay >= SPRITEDELAY) {
    if (player->size.x == 100) {
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
