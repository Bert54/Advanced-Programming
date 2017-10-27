#ifndef CHARACT
#define CHARACT

typedef struct __linkedListEnemy Enemy;

struct __linkedListEnemy {
  SDL_Surface *sprite;
  SDL_Rect position;
  SDL_Rect animation;
  int spriteRate;
  int speed;
  int speedController;
  int direction;
  int health;
  int fireDelay;
  int curFireDelay;
  Enemy *next;
};

typedef struct __linkedListFirstE Enemies;

struct __linkedListFirstE {
  Enemy *first;
};

typedef struct __enemyCorpse DeadEnemy;

struct __enemyCorpse {
  SDL_Surface *sprite;
  SDL_Rect position;
  SDL_Rect animation;
  int animDelay;
  int curAnimDelay;
};

typedef struct __enemyCorpsesQueue DeadEnemies;

struct __enemyCorpsesQueue {
  DeadEnemy* number;
  int start;
  int end;
  int empty;
};

#include "SDL.h"
#include "game.h"
#include "projectiles.h"
#define SPRITEDELAY 16

void initPlayer (player* player, int* entry, int colorKey);
int playerCollision (player* player, caseg grid[20][20], int dir);
void freePlayer(player* player);
void consEmptyEnemyList(Enemies* enemies);
void destroyEnemyList(Enemies* enemies);
void generateEnemy(Enemies* enemies, caseg grid[20][20], int spawnRate, int* nbEnemies, int colorKey);
void displayEnemies(SDL_Surface* screen, Enemies* enemies, caseg grid[20][20], player* player, Projectiles* projectiles, int colorKey);
void enemyCollision(Enemy* enemy, caseg grid[20][20]);
int playerInSight(Enemy* enemy, player* player);
void projectileHit(Enemies* enemies, player* player, Projectiles* projectiles, DeadEnemies* dEnemies, int colorKey);
void playerGameOverAnim(player* player);
void destroyEnemy(Enemies* enemies, int position);
void checkDeadEnemies(Enemies* enemies, DeadEnemies* dEnemies, int colorKey);
DeadEnemies initDeadQueue();
void alterDeadQueue(DeadEnemies* dEnemies, Enemy* enemy, int colorKey);
void updateDeadQueue(SDL_Surface* screen, DeadEnemies* dEnemies);

#endif
