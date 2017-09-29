#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "gameEvents.h"

void eventManager(SDL_Event event, int *mainScreen){
  switch (event.type) {
  case SDL_QUIT:
    eventQuit(mainScreen);
    break;
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_ESCAPE:
      eventQuit(mainScreen);
      break;
    }
  }
}

void eventQuit(int *mainScreen) {
  *mainScreen = 0;
}
