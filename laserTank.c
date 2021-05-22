#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linklist.h>
#include <log.h>

/* instruction on how to run the program: 
Basic commands:*/


/* calling functions from other scripts*/
void graph(char** array, int row, int col, int px, int py, char direc, int ex, int ey, char edirec, int** mirror, int max_size, LinkedList* list);
int playershoot(char** array, int row, int col, int px, int py, char direc, int ex, int ey, char edirec, char laserdirec, int** mirror, int max_size, LinkedList* list);
int movementchecker(int playerx, int playery, int enemyx, int enemyy, char direction, int row, int col, int** mirror, int max_size);
int movementy(int playery, int row, char direct);
int movementx(int playerx, int col, char direct);
int check(char direction);
int count(char *input);
int enemyshoot(char** array, int row, int col, int px, int py, char direc, int ex, int ey, char edirec, char elaserdirec, int** mirror, int max_size, LinkedList* list);





int main(int argc, char *argv[]) 
{
	
	/*declaring variables*/

	int col, row, py, px, ex, ey;
	/*variables to store col, row of the map with player and enemy's coordinate*/

	int x, y, p;
	/*variables for mirror*/
	char type;
	char direction, edirection;
	/*variables to store the direction of player and enemy*/

	int max_size;
	/*variable to help check the number of mirrors*/

	char buf[200];
	/*setting the buff to 200 because 200 is enough*/

	FILE *sPtr = NULL;
	char *dPtr;
	/*declaring the files*/

	char hold;
	/*variable that help store the players direction to help change direction without moving*/
	char input[5];
	int exit = 0;
	/*acts as exit*/

	char **array = NULL;
	int** mirror = NULL;
	/*arrays*/
	
	LinkedList* list = NULL;
	/*initialize link list*/

	
	/*Code proccess*/
	/*checks if there is 3 arg 
		if there is 3 arg then the program will continue
		checks if the files was opened successfully
		gets the first three row of the data(map, player position, enemy position
		change the direction input into wasd(my assignment 1 uses wasd input but that's wrong so I need to change the input into udlr)
		loop into mirror array 
		stores the mirror information into the array
		close the file opened
	 checks for condition before the game starts
		checks if player and enemy has the same coordinate and if they do the game will stop and print message
		checks if player spawning directly infront of enemy, where the enemy is looking at the player, if do game will stop and print message
		checks if the input col and row is within the parameter given by the assignment (ie 5 - 25)
		checks if the player and enemy input location is within the map
		checks if the mirror input location is within the map
		checks if player or enemy is spawned in the same spot as mirrors
		checks if mirrors are spawned in front of enemy 
	initialize the enemy shooting
		checks the direction of the enemy
		determine the direction of the laser from the direction of the enemy
	if the program has not exit
		system will clear the screen
		call "hold" variable, allows player to change direction without moving
		calls graph function to print graph
		print the instruction out
		scanf it get input from player for the next move
		checks if input is valid if it is not ask player to try again
		if input is l it will call the dump file function to print the array onto log file
		if input is f checks direction of player and determine laser direction 
		creates the hold variable to allow player to change direction without moving 
			calls the movement function to change player x and y position.
		free memory used by array
		initialize dumpfile to auto save whatever happened into log file without pressing l
		free the linkedlist memory
		free the mirror array memory
	return*/


	if (argc != 3)
	/*checks arg if not equal to three print and end*/
	{
		printf("Not enough arguements!\n");
	}
	else
	{
		
		sPtr = fopen(argv[1], "r");
		/*read the file from argument 1 */

		dPtr = argv[2];
		/* assign argument two to the variable dPtr */


		if(sPtr == NULL) {  /*checks if sPtr can be opened or not*/
			perror("Could not open file");
		}
		else
		{
			list = createLinkedList();
			/*creates link list*/
			fgets(buf, sizeof(buf), sPtr);
			sscanf(buf, "%d %d", &col, &row);
			fgets(buf, sizeof(buf), sPtr);
			sscanf(buf, "%d %d %c", &px, &py, &direction);
			fgets(buf, sizeof(buf), sPtr);
			sscanf(buf, "%d %d %c", &ex, &ey, &edirection);
			/*gets the first three input (player enemy and map coordinate and direction)*/

			max_size = 0;
			/*initialize max_size by setting it to zero*/

			if (direction == 'u')
			{
				direction = 'w';
			}
			else if (direction || edirection == 'r') /*change the direction input into wasd*/
			{
				direction = 'd';
			}
			else if (direction || edirection == 'l')
			{
				direction = 'a';
			}
			else if (direction || edirection == 'd')
			{
				direction = 's';
			}
			if (edirection == 'u')
			{
				edirection = 'w';
			}
			else if (edirection == 'r')
			{
				edirection = 'd';
			}
			else if (edirection == 'l')
			{
				edirection = 'a';
			}
			else if (edirection == 'd')
			{
				edirection = 's';
			}




			while(fgets(buf, sizeof(buf), sPtr)!= NULL)
			{
				/* loop into mirror array 
				stores the mirror information into the array*/
				mirror = (int **)realloc( mirror, (1 + max_size)*sizeof(int *) );
				mirror[max_size] = (int *)malloc(3*sizeof(int) );
				sscanf(buf, "%d %d %c", &x, &y, &type);
				
				
				mirror[max_size][0] = x;
				mirror[max_size][1] = y;
				mirror[max_size][2] = type;

				max_size++;
	
			}
		

		
			fclose(sPtr);/*close the files*/

			if (px == ex && py == ey) /* to prevent player to spawn on to enemy */
			{
				printf("Enemy position cannot be equal to player position. \n");
				exit = 1;
			}
			else if ((edirection == 'a' && py == ex && px < ey ) || (edirection == 'd' && py == ex && px > ey) || (edirection == 'w' && px == ey && py < ex) || (edirection == 's' && px == ey && py > ex)) 
			/* to prevent player to spawn at the same lane with enemy with the enemy looking at them (prevent auto lose when spawn)*/
			{
				printf("Don't spawn here! Enemy is looking at you!\n ");
				exit = 1;
			}
			else if (col-2 < 5 || row-2 < 5 || col-2 > 25 || row-2 > 25) /*limit the player to create the environment within 5-25*/
			{
				printf("collumn and row should be within 5 - 25 \n");
				exit = 1;
			}
			else if ( px >= col-1 || py >= row-1 || ex >= row-1 || ey >= col-1) /* prevent the player from spawning outside of the map */
			{
				printf(" Enter player location within the parameter!\n ");
				exit = 1;
			}
			for (p= 0; p< max_size; ++p)
			{

				if ((px == mirror[p][1] && py == mirror[p][0]) || (ex == mirror[p][0] && ey == mirror[p][1]))
				{
					printf("Do not spawn player or enemy on a mirror!\n"); /*prevents player or enemy spawn at the same place as mirror*/
					exit = 1;
				}
				else if ((edirection == 'a' && mirror[p][0] == ex && mirror[p][1] < ey ) || (edirection == 'd' && mirror[p][0] == ex && mirror[p][1] > ey) || (edirection == 'w' && mirror[p][1] == ey && mirror[p][0] < ex) || (edirection == 's' && mirror[p][1] == ey && mirror[p][0] > ex))
				{
					printf("Mirror is blocking enemy! \nspawn the mirror somewhere else or make the enemy looking at other direction! \n");
					exit = 1;
				} /*prevents mirror to spawn infront of enemy*/
			}

			while (exit == 0)
			{
				
				array = (char **)malloc(row*sizeof(int *)); /* create pointer to pointer (just following the example provided by lecturer*/ 

				/* determine the direction of enemy and the pattern of lazer to shoot the player*/
				if((edirection == 'w' && ey == px && ex > py) || (edirection == 's' && ey == px && ex < py))
				{
				/* if enemy direction is looking upward and player is above the enemy and at the same column then it will shoot
				if enemy direction is looking downward and player is below the enemy and at the same column then it will shoot*/
					char elaserdirec = '|'; 
					exit = enemyshoot(array, row, col, py, px, direction, ex, ey, edirection, elaserdirec, mirror, max_size, list);
					/*takes the return value from enemyshoot function and if enemyshoot equal 1 then end the loop*/

				}
				else if((edirection == 'a' && ex == py && ey > px) || (edirection == 'd' && ex == py && ey < px))
				/* if enemy direction is looking right and player is on the right of the enemy and at the same row then it will shoot
				if enemy direction is looking left and player is on the left of the enemy and at the same row then it will shoot*/
				{
					char elaserdirec = '-';
					exit = enemyshoot(array, row, col, py, px, direction, ex, ey, edirection, elaserdirec, mirror, max_size, list);
					/*takes the return value from enemyshoot function and if enemyshoot equal 1 then end the loop*/

				}
				
				if (exit == 0)
				
				{
					system("clear");
					hold = direction; /*this allow the player to rotate directions without moving*/
					graph(array, row, col, py, px, direction, ex, ey, edirection, mirror, max_size, list); /* printing the graph */

					printf("w to walk up \n");
					printf("s to walk down \n"); /*instruction*/
					printf("a to walk left \n");
					printf("d to walk right \n");
					printf("f to Shoot laser \n");
					printf("l to log file \n");
					printf("Action: ");
					
					scanf("%s", input); /* scan and store in the variable input*/
					
					while (check(input[0]) == 0 || count(input) > 1) /* allowing the player to re-enter if they entered wrong*/
						{
							printf("Try again Action: ");
							scanf("%s", input);
							
						}
						
				
					if (input[0] != 'f'&& input[0] != 'l') /* if the input is not lazer then the direction of the arrow will proceed to input*/
					{
						direction = input[0];
					}
					if (input [0] == 'l') /*if input is l it will store the data recorded in link list to file */
					{
						DumpToFile(list, dPtr);
					}
				
					else if (input[0] == 'f') /*determine the direction of the laser shot by player*/
					{	
						if (direction == 'a' || direction == 'd') /* if the input is left or right then shoot horizontal lazer*/
						{

							char laserdirec = '-';
							
							exit = playershoot(array, row, col, py, px, direction, ex, ey, edirection, laserdirec, mirror, max_size, list);
							/*takes the return value from playershoot and if 1 then the loop ends*/
					
						}
						else if (direction == 'w' || direction == 's') /*if the input is up or down then shoot vertical lazer*/
						{
							char laserdirec = '|';
							exit = playershoot(array, row, col, py, px, direction, ex, ey, edirection, laserdirec, mirror, max_size, list);
							/*takes the return value from playershoot and if 1 then the loop ends*/
						}
					
						
					}
					/* checks the direction of the player and if the direction is the same as the input then it will move at that direction*/
					else if ((direction == 'w' || direction == 's') && direction == hold)
					/* allows the arrow to move up or down, the hold function is to allow the player to rotate direction without moving*/ 
					{
						py = movementchecker(px, py, ex, ey, direction, row, col, mirror, max_size);
						/*takes the return value from movementchecker equal to py*/
					}
					else if ((direction == 'a' || direction == 'd') && direction == hold)
					/*allows the arrow to move left or right, the hold function is to allow the player to rotate direction without moving*/
					{
						px = movementchecker(px, py, ex, ey, direction, row, col, mirror, max_size);
						/*takes the return value from movementchecker equal to px*/
					}
					
				
				}
				
				free(array); /*free array*/
					
			}
			DumpToFile(list, dPtr);
			/*auto save to log file*/
			freeLinkedList( list, &CleanLogFunc );
			
			for ( x = 0; x< max_size; ++x) /*loop into mirror and free the 2darray within*/
			{
				free(mirror[x]);
			}
			free(mirror); /*free the mirror array*/
		}
	}
	return 0;
}
