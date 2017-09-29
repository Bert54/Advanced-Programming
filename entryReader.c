#include <stdio.h>
#include <stdlib.h>
#define ENTRY_SIZE 100

int fileOpener(FILE** file, char* fileName) {
  *file = fopen(fileName,"r");
  if (*file == NULL) {
    printf("Error: cannot open file.\n");
    return -1;
  }
  return 1;
}

int fileCloser(FILE** file) {
  if (*file == NULL) {
    printf("Error: entry isn't a file or the file hasn't been opened yet.\n") ;
    return -1;
  }
  if (fclose(*file) == EOF) {
    printf("Error: cannot close file.\n");
    return -2;
  }
  return 1;
}

int* fileReader(FILE* file) {
  if (file == NULL) {
    printf("Error: file not recognized. Cannot create entry.\n");
    return NULL;
  }
  int* content = NULL;
  content = malloc((int)ENTRY_SIZE * sizeof(int));
  char curChar;
  int i = 0;
  curChar = fgetc(file);
  while (curChar != EOF && i < ENTRY_SIZE - 1) {
    switch (curChar) {
      case '#':
	content[i] = 1;
	break;
      case '\n':
	content[i] = 2;
	break;
      default:
	content[i] = 0;
    }
    i++;
    curChar = fgetc(file);
  }
  content[i] = 3;
  return content;
}

int arrayCleaner(int** arr) {
  if (*arr == NULL) {
    printf("Error: cannot free memory allocated for array entry. Array is either null or in incorrect format.\n");
    return EXIT_FAILURE;
  }
  free(*arr);
  return 1;
}
