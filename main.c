#include <stdio.h>
#include <stdlib.h>
#include "headers/game.h"

int main (int argc, char* argv[]) {
  char* file = "content/entry/entry.txt";
  gameInit(file);
  return EXIT_SUCCESS;
}
