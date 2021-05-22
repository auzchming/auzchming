#include <stdio.h>
#include <stdlib.h>
#include <log.h>

/*struct created to store width height and character type*/
typedef struct 
{
	int width;
	int height;
	char* data;
}
LogNode;

/*the bread and butter of logging the data for log.txt*/
void LogFrame( LinkedList* list, char** array, int row, int col )  /*pass link list, array and col&row */
{
	  /*initialize link list node
		locate the memory size for the node
		pass the node to width = col
		pass the node to height = row
		locate the memory size for the dimension of the map which is col*row 
		loop to pass the array data into the node
		use the insertlast function from linklist.c*/
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

void DumpToFile( LinkedList* list, char* filename )
{
	/*open logfile
	for each element in linked list:
	  write array to file
	  if next element is not NULL:
	    write separator
	close logfile*/
	FILE *testLog = NULL;
	int x, y;
	LinkedListNode* curr = NULL;
	LogNode* data = NULL;

	testLog = fopen(filename, "w");
	if (testLog == NULL)
	{
		perror("Could not open log file");
	}
	else
	{
		curr = list->head;
		while ( curr != NULL ) 
		{
			data = curr->data;
			curr = curr->next;

			for ( y = 0; y < data->height; ++y ) {
				fputc('\n', testLog);
  				for ( x = 0; x < data->width; ++x ) {
				
					fputc( data->data[x + y*data->width], testLog);
				}
			}
			
			if ( curr != NULL ) 
			{
			  fputs("\n-------------------------\n", testLog);
		   	}
			
		}
	fclose(testLog);
	}
}

void CleanLogFunc(void* data )
{
	/*basically clear the log file and free the memory of link list*/
	LogNode* node = (LogNode *)data;
	free(node->data);
	free(node);
}


