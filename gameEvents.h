#ifndef EVENT
#define EVENT

#include "game.h"

void eventManager(SDL_Event event, int* mainScreen, player* player, caseg grid[20][20]);
void eventPlayerMovement(player* player, int dir, caseg grid[20][20]);
void eventQuit(int* mainScreen);
void resetPlayerSprite(player* player);

#endif
