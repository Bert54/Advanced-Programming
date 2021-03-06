#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SDL.h"
#include "headers/game.h"
#include "headers/characters.h"
#include "headers/projectiles.h"
#define DEFAULT_FIREDELAY 20
#define DEFAULT_HEALTH 20
#define CORPSES_LIMIT 100

void initPlayer (player* player, int* entry, int colorKey) {
  SDL_Surface *surfaceLoader = SDL_LoadBMP("content/character/player.bmp");
  int i = 0, placed = 0;
  player->skin = SDL_DisplayFormat(surfaceLoader);
  SDL_FreeSurface(surfaceLoader);
  SDL_SetColorKey(player->skin, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorKey);
  player->position.x = 0;
  player->position.y = 0;
  player->size.x = 0;
  player->size.y = 0;
  player->size.w = 50;
  player->size.h = 50;
  player->spriteDelay = SPRITEDELAY;
  while (entry[i] != 3 && !placed) {
    if (entry[i] == 4) {
      placed = 1;
    }
    else if (entry[i] == 2) {
      player->position.x = 0;
      player->position.y += 50;
    }
    else {
      player->position.x += 50;
    }
    i++;
  }
  if (!placed) {
    i = 0;
    player->position.x = 0;
    player->position.y = 0;
    while (entry[i] != 3 && !placed) {
      if (entry[i] == 0) {
	placed = 1;
      }
      else if (entry[i] == 2) {
      player->position.x = 0;
      player->position.y += 50;
      }
      else {
	player->position.x += 50;
      }
      i++;
    }
  }
  player->health = DEFAULT_HEALTH;
  player->fireDelay = DEFAULT_FIREDELAY;
  player->curFireDelay = 0;
  player->score = 0;
}

void resetPlayer(player* player, int* entry) {
  int i = 0, placed = 0;
  player->health = DEFAULT_HEALTH;
  player->size.x = 0;
  player->size.y = 0;
  player->position.x = 0;
  player->position.y = 0;
  player->fireDelay = DEFAULT_FIREDELAY;
  player->curFireDelay = 0;
  player->score = 0;
  while (entry[i] != 3 && !placed) {
    if (entry[i] == 4) {
      placed = 1;
    }
    else if (entry[i] == 2) {
      player->position.x = 0;
      player->position.y += 50;
    }
    else {
      player->position.x += 50;
    }
    i++;
  }
  if (!placed) {
    i = 0;
    player->position.x = 0;
    player->position.y = 0;
    while (entry[i] != 3 && !placed) {
      if (entry[i] == 0) {
	placed = 1;
      }
      else if (entry[i] == 2) {
      player->position.x = 0;
      player->position.y += 50;
      }
      else {
	player->position.x += 50;
      }
      i++;
    }
  }
}

void freePlayer(player* player) {
  SDL_FreeSurface(player->skin);
}

int playerCollision (player* player, caseg grid[20][20], int dir) {
  int i, j;
  switch (dir) {
  case 0:
    for (i=0;i<20;i++) {
      for (j=0;j<20;j++) {
	if (grid[j][i].inaccesibble == 1 && player->position.y-1 == grid[j][i].yvalue+49 && player->position.x-10 >= grid[j][i].xvalue && player->position.x+10 <= grid[j][i].xvalue + 49) {
	    return 1;
	}
	if (grid[j+1][i].inaccesibble == 1 && player->position.y-1 == grid[j+1][i].yvalue+49 && player->position.x+40 >= grid[j+1][i].xvalue && player->position.x+40 <= grid[j+1][i].xvalue + 49) {
	  return 1;
	}
      }
    }
    break;
  case 1:
    for (i=0;i<20;i++) {
      for (j=0;j<20;j++) {
	if (grid[j][i].inaccesibble == 1 && player->position.x+41 == grid[j][i].xvalue && player->position.y >= grid[j][i].yvalue && player->position.y <= grid[j][i].yvalue + 49) {
	  return 1;
	}
	if (grid[j][i+1].inaccesibble == 1 && player->position.x+41 == grid[j][i+1].xvalue && player->position.y+48 >= grid[j][i+1].yvalue && player->position.y <= grid[j][i+1].yvalue + 1) {
	  return 1;
	}
      }
    }
    break;
  case 2:
    for (i=0;i<20;i++) {
      for (j=0;j<20;j++) {
	if (grid[j][i].inaccesibble == 1 && player->position.y+49 == grid[j][i].yvalue && player->position.x-10 >= grid[j][i].xvalue && player->position.x+10 <= grid[j][i].xvalue + 49) {
	  return 1;
	}
	if (grid[j+1][i].inaccesibble == 1 && player->position.y+49 == grid[j+1][i].yvalue && player->position.x+40  >= grid[j+1][i].xvalue && player->position.x+40 <= grid[j+1][i].xvalue + 49) {
	  return 1;
	}
      }
    }
    break;
  case 3:
    for (i=0;i<20;i++) {
      for (j=0;j<20;j++) {
	if (grid[j][i].inaccesibble == 1 && player->position.x+9 == grid[j][i].xvalue+49 && player->position.y >= grid[j][i].yvalue && player->position.y <= grid[j][i].yvalue + 49) {
	  return 1;
	}
	if (grid[j][i+1].inaccesibble == 1 && player->position.x+9 == grid[j][i+1].xvalue+49 && player->position.y+48 >= grid[j][i+1].yvalue && player->position.y + 50 <= grid[j][i+1].yvalue + 49) {
	  return 1;
	}
      }
    }
    break;
  }
  return 0;
}

void consEmptyEnemyList(Enemies* enemies) {
  enemies->first = NULL;
}

void destroyEnemyList(Enemies* enemies) {
  Enemy *temp;
  if (enemies->first != NULL) {
    while (enemies->first->next != NULL) {
      temp = enemies->first->next;
      SDL_FreeSurface(enemies->first->sprite);
      free(enemies->first);
      enemies->first = temp;
    }
    SDL_FreeSurface(enemies->first->sprite);
    free(enemies->first);
  }
}

void generateEnemy(Enemies* enemies, caseg grid[20][20], int spawnRate, int* nbEnemies, int colorKey) {
  int result, i, j;
  for (i=0;i<20;i++) {
    for (j=0;j<20;j++) {
      if (grid[i][j].inaccesibble == 2) {
	result = rand() % (12000 - spawnRate);
	if (result == 1) {
	  int position = rand() % 4;
	  Enemy *temp = malloc(sizeof(Enemy));
	  SDL_Surface *surfaceLoader = SDL_LoadBMP("content/character/enemy1.bmp");
	  temp->sprite = SDL_DisplayFormat(surfaceLoader);
	  SDL_SetColorKey(temp->sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorKey);
	  temp->position.x = grid[i][j].xvalue;
	  temp->position.y = grid[i][j].yvalue;
	  temp->animation.x = 0;
	  temp->animation.y = 50 * position;
	  temp->animation.w = 50;
	  temp->animation.h = 50;
	  temp->spriteRate = 0;
	  temp->speed = 0;
	  temp->speedController = 2;
	  temp->direction = position;
	  temp->health = 3;
	  temp->fireDelay = 250;
	  temp->curFireDelay = 0;
	  temp->next = enemies->first;
	  temp->scoreValue = 100;
	  enemies->first = temp;
	  *nbEnemies = *nbEnemies + 1;
	}
      }
    }	
  }
}

void displayEnemies(SDL_Surface* screen, Enemies* enemies, caseg grid[20][20], player* player, Projectiles* projectiles, int colorKey) {
  Enemy* temp = enemies->first;
  int changeDirection, sightDir = 0;
  while (temp != NULL) {
    sightDir = playerInSight(temp, player);
    if (player->health > 0 && sightDir != 0) {
      temp->direction = sightDir - 1;
      temp->animation.y = 50 * temp->direction;
      if (temp->curFireDelay == 0) {
	consProjectilePlayer(projectiles, colorKey, player, temp->direction, 1, temp);
	temp->curFireDelay = temp->fireDelay;
      }
    }
    else {
      if (temp->spriteRate >= SPRITEDELAY+30) {
	if (temp->animation.x >= 150) {
	  temp->animation.x = 0;
	}
	else {
	  temp->animation.x += 50;
	}
	temp->spriteRate = 0;
      }
      else {
	temp->spriteRate++;
      }
      changeDirection = rand() % 500;
      if (changeDirection == 0) {
	temp->direction = rand() % 4;
	temp->animation.y = 50 * temp->direction;
      }
      if (temp->speed >= temp->speedController) {
	enemyCollision(temp, grid);
	temp->speed = 0;
      }
      else {
	temp->speed++;
      }
    }
    SDL_BlitSurface(temp->sprite, &(temp->animation), screen, &(temp->position));
    if (temp->curFireDelay > 0) {
      temp->curFireDelay--;
    }
    temp = temp->next;
  }
}

void enemyCollision(Enemy* enemy, caseg grid[20][20]) {
  int i, j, memorizer, changeDir = 0;
  for (i=0;i<20;i++) {
    for (j=0;j<20;j++) {
      switch (enemy->direction) {
      case 0:
	if (grid[j][i].inaccesibble == 1 && enemy->position.y-1 == grid[j][i].yvalue+49 && enemy->position.x-10 >= grid[j][i].xvalue && enemy->position.x+10 <= grid[j][i].xvalue + 49) {
	  changeDir = 1;
	}
	if (!changeDir && grid[j+1][i].inaccesibble == 1 && enemy->position.y-1 == grid[j+1][i].yvalue+49 && enemy->position.x+40 >= grid[j+1][i].xvalue && enemy->position.x+40 <= grid[j+1][i].xvalue + 49) {
	  changeDir = 1;
	}
	break;
      case 1:
	if (grid[j][i].inaccesibble == 1 && enemy->position.x+41 == grid[j][i].xvalue && enemy->position.y >= grid[j][i].yvalue && enemy->position.y <= grid[j][i].yvalue + 49) {
	 changeDir = 1;
	}
	if (!changeDir && grid[j][i+1].inaccesibble == 1 && enemy->position.x+41 == grid[j][i+1].xvalue && enemy->position.y+48 >= grid[j][i+1].yvalue && enemy->position.y <= grid[j][i+1].yvalue + 1) {
	  changeDir = 1;
	}
	break;
      case 2:
	if (grid[j][i].inaccesibble == 1 && enemy->position.y+49 == grid[j][i].yvalue && enemy->position.x-10 >= grid[j][i].xvalue && enemy->position.x+10 <= grid[j][i].xvalue + 49) {
	  changeDir = 1;
	}
	if (!changeDir && grid[j+1][i].inaccesibble == 1 && enemy->position.y+49 == grid[j+1][i].yvalue && enemy->position.x+40  >= grid[j+1][i].xvalue && enemy->position.x+40 <= grid[j+1][i].xvalue + 49) {
	  changeDir = 1;
	}
	break;
      case 3:
	if (grid[j][i].inaccesibble == 1 && enemy->position.x+9 == grid[j][i].xvalue+49 && enemy->position.y >= grid[j][i].yvalue && enemy->position.y <= grid[j][i].yvalue + 49) {
	  changeDir = 1;
	}
	if (!changeDir && grid[j][i+1].inaccesibble == 1 && enemy->position.x+9 == grid[j][i+1].xvalue+49 && enemy->position.y+48 >= grid[j][i+1].yvalue && enemy->position.y + 50 <= grid[j][i+1].yvalue + 49) {
	  changeDir = 1;
	}
	break;
      }
    }
  }
  if (changeDir == 1) {
    memorizer = enemy->direction;
    do {
      enemy->direction = rand() % 4;
    } while (enemy->direction == memorizer);
    enemy->animation.y = 50 * enemy->direction;
  }
  else {
    switch (enemy->direction) {
    case 0:
      enemy->position.y--;
      break;
    case 1:
      enemy->position.x++;
      break;
    case 2:
      enemy->position.y++;
      break;
     case 3:
      enemy->position.x--;
      break;
    }
  }
}

int playerInSight(Enemy* enemy, player* player) {
  if (enemy->position.x + 5 > player->position.x && enemy->position.x < player->position.x + 5) {
    if (enemy->position.y > player->position.y) {
      return 1;
    }
    else {
      return 3;
    }
  }
  if (enemy->position.y + 5 > player->position.y && enemy->position.y < player->position.y + 5) {
    if (enemy->position.x > player->position.x) {
      return 4;
    }
    else {
      return 2;
    }
  }
  return 0;
}


void projectileHit(Enemies* enemies, player* player, Projectiles* projectiles, DeadEnemies* dEnemies, int colorKey) {
  Projectile* tempP = projectiles->first;
  int counterE, counterP = 1, hit;
  Enemy* tempE;
  while (tempP != NULL) {
    if (tempP->alliedTeam == 0) {
      tempE = enemies->first;
      counterE = 0;
      hit = 0;
      while (!hit && tempE != NULL) {
	if ((tempE->position.x+10 >= tempP->position.x+10 && tempE->position.x+10 <= tempP->position.x+40 && tempE->position.y+10 >= tempP->position.y+10 && tempE->position.y+10 <= tempP->position.y+40) || (tempE->position.x+40 >= tempP->position.x+10 && tempE->position.x+40 <= tempP->position.x+40 && tempE->position.y+40 >= tempP->position.y+10 && tempE->position.y+40 <= tempP->position.y+40) || (tempE->position.x+40 >= tempP->position.x+10 && tempE->position.x+40 <= tempP->position.x+40 && tempE->position.y+10 >= tempP->position.y+10 && tempE->position.y+10 <= tempP->position.y+40) || (tempE->position.x+10 >= tempP->position.x+10 && tempE->position.x+40 <= tempP->position.x+40 && tempE->position.y+40 >= tempP->position.y+10 && tempE->position.y+40 <= tempP->position.y+40)) {
	  tempE->health--;
	  destroyProjectile(projectiles, counterP);
	  if (tempE->health <= 0) {
	    counterE--;
	    player->score += 100;
	  }
	  counterP--;
	  hit = 1;
	}
	tempE = tempE->next;
	counterE++;
      }
    }
    else if (tempP->alliedTeam == 1) {
      if ((player->position.x >= tempP->position.x && player->position.x <= tempP->position.x+15 && player->position.y >= tempP->position.y && player->position.y <= tempP->position.y+20) || (player->position.x+35 >= tempP->position.x && player->position.x <= tempP->position.x && player->position.y+45 >= tempP->position.y && player->position.y <= tempP->position.y) || (player->position.x+40 >= tempP->position.x+10 && player->position.x+40 <= tempP->position.x+40 && player->position.y+10 >= tempP->position.y+10 && player->position.y+10 <= tempP->position.y+40) || (player->position.x >= tempP->position.x && player->position.x <= tempP->position.x+15 && player->position.y+45 >= tempP->position.y+5 && player->position.y <= tempP->position.y)) {
	player->health--;
	destroyProjectile(projectiles, counterP);
	counterP--;
      }
    }
    tempP = tempP->next;
    counterP++;
  }
  checkDeadEnemies(enemies, dEnemies, colorKey);
}

void playerGameOverAnim(player* player) {
  if (player->size.y < 200) {
    player->size.y = 200;
    player->size.x = 0;
  }
  else if (player->size.x < 150) {
    player->size.x += 50;
  }
}

void destroyEnemy(Enemies* enemies, int position) {
  Enemy* temp = enemies->first, *temp2;
  if (enemies != NULL) {
    if (position == 1) {
      if (enemies->first->next != NULL) {
	enemies->first = enemies->first->next;
	SDL_FreeSurface(temp->sprite);
	free(temp);
      }
      else {
	free(temp);
        enemies->first = NULL;
      }
    }
    else {
      while (position > 2) {
	temp = temp->next;
	position--;
      }
      if (temp->next->next != NULL) {
	temp2 = temp->next;
	temp->next = temp->next->next;
	SDL_FreeSurface(temp2->sprite);
	free(temp2);
      }
      else {
	SDL_FreeSurface(temp->next->sprite);
	free(temp->next);
	temp->next = NULL;
      }
    }
  }
}

void checkDeadEnemies(Enemies* enemies, DeadEnemies* dEnemies, int colorKey) {
  Enemy* temp = enemies->first;
  int counter = 1;
  while (temp != NULL) {
    if (temp->health <= 0) {
      alterDeadQueue(dEnemies, temp, colorKey);
      destroyEnemy(enemies, counter);
      counter--;
    }
    counter++;
    temp = temp->next;
  }
}

DeadEnemies initDeadQueue() {
  DeadEnemies dEnemies;
  dEnemies.number = malloc(CORPSES_LIMIT * sizeof(DeadEnemy));
  dEnemies.start = 0;
  dEnemies.end = 0;
  dEnemies.empty = 1;
  dEnemies.full = 0;
  return dEnemies;
}

void alterDeadQueue(DeadEnemies* dEnemies, Enemy* enemy, int colorKey) {
  int noFree = 0;
  dEnemies->end = dEnemies->end + 1;
  if (dEnemies->end == CORPSES_LIMIT) {
    dEnemies->end = 0;
  }
  if (dEnemies->start != dEnemies->end || (dEnemies->start == dEnemies->end && dEnemies->full == 0)) {
    SDL_Surface* surfaceLoader = SDL_LoadBMP("content/character/enemy1.bmp");
    dEnemies->number[dEnemies->end].sprite = SDL_DisplayFormat(surfaceLoader);
    SDL_FreeSurface(surfaceLoader);
    SDL_SetColorKey(dEnemies->number[dEnemies->end].sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorKey);
    if (dEnemies->start == dEnemies->end && dEnemies->full == 0) {
      dEnemies->full = 1;
      noFree = 1;
    }
  }
  if (dEnemies->full == 1 && noFree == 0) {
    dEnemies->start++;
  }
  if (dEnemies->start == CORPSES_LIMIT) {
    dEnemies->start = 0;
  }
  dEnemies->number[dEnemies->end].position.x = enemy->position.x;
  dEnemies->number[dEnemies->end].position.y = enemy->position.y;
  dEnemies->number[dEnemies->end].animation.x = 0;
  dEnemies->number[dEnemies->end].animation.y = 200;
  dEnemies->number[dEnemies->end].animation.w = enemy->animation.w;
  dEnemies->number[dEnemies->end].animation.h = enemy->animation.h;
  dEnemies->number[dEnemies->end].animDelay = 20;
  dEnemies->number[dEnemies->end].curAnimDelay = dEnemies->number[dEnemies->end].animDelay;
  if (dEnemies->empty == 1) {
    dEnemies->empty = 0;
  }
}

void updateDeadQueue(SDL_Surface* screen, DeadEnemies* dEnemies) {
  int start, end, counter  = 0;
  if (dEnemies->start == dEnemies->end) {
    while (counter < CORPSES_LIMIT) {
      if (dEnemies->number[counter].animation.x < 150) {
	if (dEnemies->number[counter].curAnimDelay == 0) {
	  dEnemies->number[counter].animation.x += 50;
	  dEnemies->number[counter].curAnimDelay = dEnemies->number[counter].animDelay;
	}
	else {
	  dEnemies->number[counter].curAnimDelay--;
	}
      }
      SDL_BlitSurface(dEnemies->number[counter].sprite, &(dEnemies->number[counter].animation), screen, &(dEnemies->number[counter].position));
      counter++;
    }
  }
  else {
    start = dEnemies->start+1;
    end = dEnemies->end+1;
    while (start != end) {
      if (start >= CORPSES_LIMIT) {
	start = 0;
      }
      if (dEnemies->number[start].animation.x < 150) {
	 if (dEnemies->number[start].curAnimDelay == 0) {
	   dEnemies->number[start].animation.x += 50;
	   dEnemies->number[start].curAnimDelay = dEnemies->number[start].animDelay;
	 }
	 else {
	   dEnemies->number[start].curAnimDelay--;
	 }
      }
      SDL_BlitSurface(dEnemies->number[start].sprite, &(dEnemies->number[start].animation), screen, &(dEnemies->number[start].position));
      start++;
    }
  }
}

void destroyDeadQueue(DeadEnemies* dEnemies) {
  int counter = 0;
  if (!dEnemies->empty) {
    if (dEnemies->start == dEnemies->end) {
      while (counter < CORPSES_LIMIT-1) {
	SDL_FreeSurface(dEnemies->number[counter].sprite);
	counter++;
      }
    }
    else {
      while (dEnemies->start != dEnemies->end) {
	if (dEnemies->start >= CORPSES_LIMIT) {
	  dEnemies->start = 0;
	}
	SDL_FreeSurface(dEnemies->number[counter].sprite);
	dEnemies->start++;
      }
    }
  }
  free(dEnemies->number);
}
