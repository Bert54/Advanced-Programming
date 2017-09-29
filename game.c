#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "entryReader.h"
#include "game.h"
#include "gameEvents.h"
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

int gameInit(char* fileName) {
  FILE* file = NULL;
  if (fileOpener(&file, fileName) == -1) {
    return EXIT_FAILURE;
  }
  else {
    int* entry = fileReader(file);
    if (entry != NULL) {
      mainGame(entry);
    }
    else {
      return EXIT_FAILURE;
    }
    arrayCleaner(&entry);
  }
  fileCloser(&file);
  return 1;
}

void mainGame(int* entree) {
  int mainScreen = 1;
  SDL_Event eventGame;
  SDL_Surface *screen;
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption("A temporary name","A temporary name");
  screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0);
  while (mainScreen) {
    if (SDL_PollEvent(&eventGame)) {
      eventManager(eventGame, &mainScreen);
    }
    SDL_UpdateRect(screen, 0, 0, 0, 0);
  }
  SDL_Quit();
}
