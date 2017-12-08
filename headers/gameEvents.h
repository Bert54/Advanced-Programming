#ifndef EVENT
#define EVENT

#include "game.h"
#include "projectiles.h"
#include "characters.h"
#include "menus.h"

void eventManager(SDL_Event event, int* mainScreen, player* player, caseg grid[20][20], Projectiles* projectiles, int colorKey, int* gameOverDelay, Enemies* enemies, int* entry, int* pause, int* pauseDelay, menuCursor* pauseCursor, int* gameOver, int* mainMenu, menuCursor* gameOverCursor);
void eventManagerMenu(SDL_Event event, int* mainMenu, menuCursor* mainCursor, int* startGame);
void eventPlayerMovement(player* player, int dir, caseg grid[20][20]);
void eventQuit(int* mainScreen);
void resetPlayerSprite(player* player);

#endif
