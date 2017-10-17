#define PROJNANIMRATE 10
#define PROJECTILE_WIDTH 32
#define PROJECTILE_HEIGHT 32

#ifndef PROJ
#define PROJ

#include "SDL.h"
#include "characters.h"
#include "game.h"

typedef struct __linkedListProjectile Projectile;

struct __linkedListProjectile {
  SDL_Surface *sprite;
  SDL_Rect position;
  SDL_Rect animation;
  int spriteRate;
  int velocity;
  int alliedTeam;
  int direction;
  Projectile *next;
};

typedef struct __linkedListFirstP Projectiles;

struct __linkedListFirstP {
  Projectile *first;
};

void consProjectile(Projectiles* projectile, int colorKey, player* player, int direction);
void consEmptyProjectilesList(Projectiles* proj);
void destroyProjectilesList(Projectiles* proj);
void destroyProjectile(Projectiles* projectiles, int position);
void displayProjectiles(SDL_Surface *screen, Projectiles* projectiles, caseg grid[20][20]);

#endif
