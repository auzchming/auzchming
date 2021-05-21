
#include <stdio.h>
#include <stdlib.h>
#include <log.h>

char direction(char direction);
void LogFrame( LinkedList* list, char** array, int row, int col);

/*the main function to graph the map */
void graph(char** array, int row, int col, int px, int py, char direc, int ex, int ey, char edirec, char** mirror, int max_size, Linkedlist* list)
{
	
	LogFrame(list, array, row, col)
	
	int i, k, p;
	char direct = direction(direc);
	char edirect = direction(edirec);

	for (i = 0; i < row ; i++) 
	{
		array[i] = (char *)malloc(col*sizeof(int)); /*loop to locate every column of the array*/
	}


	for (i = 0; i < row ; i++) 
	{
		for (k = 0; k < col ; k++) /*a for loop to go through x and y to print out the array*/
		{
			
			if (i == 0 || k == 0 || i == (row-1) || k == (col-1)) /* a condition to help print the outer box*/
			{
				array[i][k] = '*';
			}
			else if (i == px && k == py) /* a condition to locate the player location*/
			{
				array[i][k] = direct;
			}
			else if (i == ex && k == ey) /* a condition to locate enemy location*/
			{
				array[i][k] = edirect;
			}
			

			else             /*if nothing else then print the empty space within the array*/
			{ 
				array[i][k] = ' ';
			}

			for (p= 0; p< max_size; ++p)
			{

				if (mirror[p][0] == i && mirror[p][1] == k)
				{
					if(mirror[p][2] == 'f')
					{	

						array[i][k] = '/';
					}
					else if (mirror[p][2] == 'b')
					{
						array[i][k] = '\\';
					}
				}
			}
		
		}
	}
	LogFrame( list, array, row, col);

	for (i = 0; i < row ; i++) 
	{
		for (k = 0; k < col ; k++) 
		{
			printf("%c", array[i][k]); /*following the above condition, print the array */
		}
		printf("\n");
		free(array[i]); /*free the array that is allocated above*/
	
	}
}


