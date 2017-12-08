#ifndef PLACEMENT
#define PLACEMENT

void wallPlacement(int* entry, struct SDL_Surface screen, struct SDL_Surface wall, SDL_Rect* posWall);
void initEnemySpawnSprite(int* delay, SDL_Rect* posEnSpawn, SDL_Rect* enemySpawnAnim);
void enemySpawnPlacement(int* entry, int* delay, SDL_Surface screen, SDL_Surface enemySpawn, SDL_Rect posEnSpawn, SDL_Rect* enemySpawnAnim);

#endif
