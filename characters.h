#ifndef CHARACT
#define CHARACT

#include "game.h"
#define SPRITEDELAY 30

void initPlayer (player* player, int* entry, int colorKey);
int playerCollision (player* player, caseg grid[20][20], int dir);
void freePlayer(player* player);

#endif
