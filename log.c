#include <stdio.h>
#include <stdlib.h>
#include <log.h>

typedef struct {
		int width;
		int height;
		char* data;
		LogNode;
		}

void LogFrame( LinkedList* list, char** array, int row, int col ) 
{
	LogNode* node = NULL;
	int x, y;

	node = (LogNode *)malloc(sizeof(LogNode));
	node->width = col;
	node->height = row;
	node->data = (char *)malloc(col*row*sizeof(char));
	for ( y = 0; y < node->height; ++y ) 
	{
		for ( x = 0; x < node->width; ++x ) 
		{
		node->data[x + y*node->width] = array[y][x];
		}
	}

	insertLast( list, node );
}

void DumpToFile( LinkedList* list, char* filename);
{
	
}

void CleanLogFunc( void* data );
{
	free(data->data);
	free(data);
}


