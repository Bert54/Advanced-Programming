#ifndef GAME
#define GAME

#include "SDL.h"
#include "../libraries/SDL_ttf/SDL_ttf.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

typedef struct __player player;
struct __player {
  SDL_Surface *skin;
  SDL_Rect position;
  SDL_Rect size;
  int spriteDelay;
  int health;
  int fireDelay;
  int curFireDelay;
  int score;
};

typedef struct __case caseg;
struct __case {
  int inaccesibble;
  int xvalue;
  int yvalue;
};

typedef struct __stats Stats;
struct __stats {
  SDL_Surface *score;
  SDL_Rect posScore;
  SDL_Surface *health;
  SDL_Rect posHealth;
  SDL_Surface *bestScore;
  SDL_Rect posBestScore;
};

#include "characters.h"
#include "projectiles.h"
#include "scoresManager.h"

int mainMenu();
int gameInit(char* fileName, int colorKey, SDL_Surface *screen, int* mainMenu);
void mainGame(int* entry, int colorKey, SDL_Surface* screen, int* mainMenu);
void gameGridFiller(int* entry, caseg gameGrid[20][20], int* nbSpawners);
void resetGame(Projectiles* projectiles, Enemies* enemies, player* player, int* gameOverDelay, int* entry);
void updateStats(Stats* stats, SDL_Color statColor, SDL_Color lowHealthColor, TTF_Font *statFont, player player, int* lowHealthAnim, int* lowHealthCurColor, int bestScore);
void displayStats(Stats stats, SDL_Surface* screen);
void displayScoresMenu(SDL_Surface* screen, ScoreList scores);

#endif
