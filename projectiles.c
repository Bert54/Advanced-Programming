#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "headers/projectiles.h"
#include "headers/characters.h"
#include "headers/game.h"

void consProjectilePlayer(Projectiles* projectile, int colorKey, player* player, int direction) {
  Projectile *temp = malloc(sizeof(Projectile));
  SDL_Surface *surfaceLoader = SDL_LoadBMP("content/projectiles/alliedProjectile.bmp");
  temp->sprite = SDL_DisplayFormat(surfaceLoader);
  SDL_FreeSurface(surfaceLoader);
  SDL_SetColorKey(temp->sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorKey);
  switch (direction) {
  case 0:
    temp->position.x = player->position.x + 50 - PROJECTILE_WIDTH - 5;
    temp->position.y = player->position.y - PROJECTILE_HEIGHT;
    break;
  case 1:
    temp->position.x = player->position.x + 40;
    temp->position.y = player->position.y + 50 - PROJECTILE_HEIGHT - 15;
    break;
  case 2:
    temp->position.x = player->position.x + 50 - PROJECTILE_WIDTH - 5;
    temp->position.y = player->position.y + 50;
    break;
  case 3:
    temp->position.x = player->position.x - PROJECTILE_WIDTH + 10;
    temp->position.y = player->position.y + 50 - PROJECTILE_HEIGHT - 15;
  }
  temp->animation.x = 0;
  temp->animation.y = PROJECTILE_HEIGHT * direction;
  temp->animation.w = PROJECTILE_WIDTH;
  temp->animation.h = PROJECTILE_HEIGHT;
  temp ->spriteRate = 0;
  temp->velocity = 10;
  temp->alliedTeam = 0;
  temp->direction = direction;
  temp->next = projectile->first;
  projectile->first = temp;
}

void consEmptyProjectilesList(Projectiles* proj) {
  proj->first = NULL;
}

void destroyProjectilesList(Projectiles* proj) {
  Projectile* temp;
  if (proj->first != NULL) {
    while (proj->first->next != NULL) {
      temp = proj->first->next;
      free(proj->first);
      proj->first = temp;
    }
    free(proj->first);
  }
  free(proj);
}

void destroyProjectile(Projectiles* projectiles, int position) {
  Projectile* temp = projectiles->first, *temp2;
  if (projectiles != NULL) {
    if (position == 1) {
      if (projectiles->first->next != NULL) {
	projectiles->first = projectiles->first->next;
	free(temp);
      }
      else {
	free(temp);
	projectiles->first = NULL;
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
	free(temp2);
      }
      else {
	free(temp->next);
	temp->next = NULL;
      }
    }
  }
}

void displayProjectiles(SDL_Surface *screen, Projectiles* projectiles, caseg grid[20][20]) {
  Projectile* temp = projectiles->first;
  int collide, i, j, nbProj = 1;
  while (temp != NULL) {
    collide = 0;
    if (temp->spriteRate >= PROJNANIMRATE) {
      if (temp->animation.x >= PROJECTILE_WIDTH * 3) {
	temp->animation.x = 0;
      }
      else {
	temp->animation.x += PROJECTILE_WIDTH;
      }
      temp->spriteRate = 0;
    }
    else {
      temp->spriteRate++;
    }
    switch (temp->direction) {
    case 0:
      temp->position.y -= temp->velocity / 10;
      for (i=0;i<20;i++) {
	for (j=0;j<20;j++) {
	  if (grid[j][i].inaccesibble == 1 && temp->position.y >= grid[j][i].yvalue && temp->position.y <= grid[j][i].yvalue+50 && temp->position.x >= grid[j][i].xvalue && temp->position.x <= grid[j][i].xvalue + 49) {
	    collide = 1;
	  }
	  if (!collide && grid[j+1][i].inaccesibble == 1 && temp->position.y >= grid[j+1][i].yvalue && temp->position.y <= grid[j+1][i].yvalue+50 && temp->position.x+PROJECTILE_WIDTH >= grid[j+1][i].xvalue && temp->position.x+PROJECTILE_WIDTH <= grid[j+1][i].xvalue + 49) {
	    collide = 1;
	  }
	}
      }
      break;
    case 1:
      temp->position.x += temp->velocity / 10;
       for (i=0;i<20;i++) {
	 for (j=0;j<20;j++) {
	   if (grid[j][i].inaccesibble == 1 && temp->position.x+PROJECTILE_WIDTH >= grid[j][i].xvalue && temp->position.x+PROJECTILE_WIDTH <= grid[j][i].xvalue+50 && temp->position.y >= grid[j][i].yvalue && temp->position.y <= grid[j][i].yvalue + 49) {
	     collide = 1;
	   }
	   if (!collide && grid[j][i+1].inaccesibble == 1 && temp->position.x+PROJECTILE_WIDTH >= grid[j][i+1].xvalue && temp->position.x+PROJECTILE_WIDTH <= grid[j][i+1].xvalue+50 && temp->position.y+PROJECTILE_HEIGHT >= grid[j][i+1].yvalue && temp->position.y <= grid[j][i+1].yvalue + 1) {
	     collide = 1;
	       }
	 }
       }
       break;
    case 2:
      temp->position.y += temp->velocity / 10;
      for (i=0;i<20;i++) {
	for (j=0;j<20;j++) {
	  if (grid[j][i].inaccesibble == 1 && temp->position.y+PROJECTILE_HEIGHT >= grid[j][i].yvalue && temp->position.y+PROJECTILE_HEIGHT <= grid[j][i].yvalue+50  && temp->position.x >= grid[j][i].xvalue && temp->position.x <= grid[j][i].xvalue + 49) {
	     collide = 1;
	  }
	  if (!collide && grid[j+1][i].inaccesibble == 1 && temp->position.y+PROJECTILE_HEIGHT >= grid[j+1][i].yvalue && temp->position.y+PROJECTILE_HEIGHT <= grid[j+1][i].yvalue+50 && temp->position.x+PROJECTILE_WIDTH  >= grid[j+1][i].xvalue && temp->position.x+PROJECTILE_WIDTH <= grid[j+1][i].xvalue + 49) {
	     collide = 1;
	  }
	}
      }
      break;
    case 3:
      temp->position.x -= temp->velocity / 10;
      for (i=0;i<20;i++) {
	for (j=0;j<20;j++) {
	  if (grid[j][i].inaccesibble == 1 && temp->position.x >= grid[j][i].xvalue && temp->position.x <= grid[j][i].xvalue+50 && temp->position.y >= grid[j][i].yvalue && temp->position.y <= grid[j][i].yvalue + 49) {
	    collide = 1;
	  }
	  if (!collide && grid[j][i+1].inaccesibble == 1 && temp->position.x >= grid[j][i+1].xvalue &&temp->position.x <= grid[j][i+1].xvalue+50 && temp->position.y+PROJECTILE_WIDTH >= grid[j][i+1].yvalue && temp->position.y + PROJECTILE_WIDTH <= grid[j][i+1].yvalue + 49) {
	    collide = 1;
	  }
	}
      }
    }
    if (!collide) {
      SDL_BlitSurface(temp->sprite, &(temp->animation), screen, &(temp->position));
      nbProj++;
    }
    else {
      destroyProjectile(projectiles, nbProj);
      // nbProj--;
    }
    temp = temp->next;
  }
}
