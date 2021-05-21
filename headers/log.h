#ifndef LOG_H
#define LOG_H

#include "linklist.h"


void LogFrame( LinkedList* list, char** array, int row, int col);
void DumpToFile( LinkedList* list, char* filename);
void CleanLogFunc(void* data);

#endif
