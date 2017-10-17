#ifndef ENTRY_READER
#define ENTRY_READER

int fileOpener(FILE** file, char* fileName);
int fileCloser(FILE** file);
int* fileReader(FILE* file);
int arrayCleaner(int** arr);

#endif
