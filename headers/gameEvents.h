#ifndef EVENT
#define EVENT

#include "game.h"
#include "projectiles.h"

void eventManager(SDL_Event event, int* mainScreen, player* player, caseg grid[20][20], Projectiles* projectiles, int colorKey);
void eventPlayerMovement(player* player, int dir, caseg grid[20][20]);
void eventQuit(int* mainScreen);
void resetPlayerSprite(player* player);

#endif
