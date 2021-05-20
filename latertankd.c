#include <stdio.h>
#include <stdlib.h>
/* instruction on how to run the program: 
Basic commands:
input < 1.collumn of the map>  < 2.row of the map>  <3.x-coordinate of player>  <4.y-coordinate of player> <5. player's direction> <6.x-coordinate of enemy>  <7.y-coordinate of enemy>   < 8. enemy's direction>

Direction input:
w if you want to look up
d if you want to look right
s if you want to look down
a if you want to look left

example: ./laserTank 20 10 1 1 s 5 4 w
 
*/

/* calling functions from other script*/
void graph(char** array, int row, int col, int px, int py, char direc, int ex, int ey, char edirec);
int playershoot(char** array, int row, int col, int px, int py, char direc, int ex, int ey, char edirec, char laserdirec);
int movementchecker(int playerx, int playery, int enemyx, int enemyy, char direction, int row, int col);
int movementy(int playery, int row, char direct);
int movementx(int playerx, int col, char direct);
int check(char direction);
int count(char *input);
int enemyshoot(char** array, int row, int col, int px, int py, char direc, int ex, int ey, char edirec, char elaserdirec);


int main(int argc, char *argv[]) 
{
	char *p;
	char hold;
	char input[5];
	
	int exit = 0;
	
	/* arguement input */
	int col = strtol(argv[1], &p, 10) + 2; /* the p and 10 is to help the char to turn into an integer */
	int row = strtol(argv[2], &p, 10) + 2;
	
	int py = strtol(argv[3], &p, 10);
	int px = strtol(argv[4], &p, 10);
	
	char direction = *(argv[5]); /* since the input is already an char there is no need to convert */
	
	int ex = strtol(argv[6], &p, 10);
	int ey = strtol(argv[7], &p, 10);
	
	char edirection = *(argv[8]);

	if (px == ex && py == ey) /* to prevent player to spawn on to enemy */
	{
		printf("Enemy position cannot be equal to player position. \n");
		exit = 1;
	}
	else if ((edirection == 'a' && py < ey && px == ex ) || (edirection == 'd' && py > ey && px == ex) || (edirection == 'w' && px < ex && py == ey) || (edirection == 's' && px > ex && py == ey)) 
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
	else if ( px >= col -2 || py >= row-2 || ex >= row-2 || ey >= col-2) /* prevent the player from spawning outside of the map */
	{
		printf(" Enter player location within the parameter!\n ");
		exit = 1;
	}


	while (exit == 0)
	{
		
		char **array = NULL; /*create 2 pointer array */
		array = (char **)malloc(row*sizeof(int *)); /* create pointer to pointer (just following the example provided by lecturer*/ 


		/* determine the direction of enemy and the pattern of lazer to shoot the player*/
		if((edirection == 'w' && ey == px && ex > py) || (edirection == 's' && ey == px && ex < py))
		{
		/* if enemy direction is looking upward and player is above the enemy and at the same column then it will shoot
		if enemy direction is looking downward and player is below the enemy and at the same column then it will shoot*/
			char elaserdirec = '|'; 
			exit = enemyshoot(array, row, col, py, px, direction, ex, ey, edirection, elaserdirec);
			/*takes the return value from enemyshoot function and if enemyshoot equal 1 then end the loop*/

		}
		else if((edirection == 'a' && ex == py && ey > px) || (edirection == 'd' && ex == py && ey < px))
		/* if enemy direction is looking right and player is on the right of the enemy and at the same row then it will shoot
		if enemy direction is looking left and player is on the left of the enemy and at the same row then it will shoot*/
		{
			char elaserdirec = '-';
			exit = enemyshoot(array, row, col, py, px, direction, ex, ey, edirection, elaserdirec);
			/*takes the return value from enemyshoot function and if enemyshoot equal 1 then end the loop*/

		}
		
		if (exit == 0)
		
		{
			system("clear");
			hold = direction; /*this allow the player to rotate directions without moving*/
			graph(array, row, col, py, px, direction, ex, ey, edirection); /* printing the graph */
			
			printf("w to walk up \n");
			printf("s to walk down \n"); /*instruction*/
			printf("a to walk left \n");
			printf("d to walk right \n");
			printf("f to Shoot laser \n");
			printf("Action: ");
			
			scanf("%s", input); /* scan and store in the variable input*/
			
			while (check(input[0]) == 0 || count(input) > 1) /* allowing the player to re-enter if they entered wrong*/
				{
					printf("Try again Action: ");
					scanf("%s", input);
					if (input[0] != 'f')
					{
						direction = input[0];
					}
				}
				
			if (input[0] != 'f') /* if the input is not lazer then the direction of the arrow will proceed to input*/
			{
				direction = input[0];
			}
			
			
			if (input[0] == 'f') /*determine the direction of the laser shot by player*/
			{	
				if (direction == 'a' || direction == 'd') /* if the input is left or right then shoot horizontal lazer*/
				{

					char laserdirec = '-';
					
					exit = playershoot(array, row, col, py, px, direction, ex, ey, edirection, laserdirec);
					/*takes the return value from playershoot and if 1 then the loop ends*/
			
				}
				else if (direction == 'w' || direction == 's') /*if the input is up or down then shoot vertical lazer*/
				{
					char laserdirec = '|';
					exit = playershoot(array, row, col, py, px, direction, ex, ey, edirection, laserdirec);
					/*takes the return value from playershoot and if 1 then the loop ends*/
				}
			
				
			}
/* checks the direction of the player and if the direction is the same as the input then it will move at that direction*/
			else if ((direction == 'w' || direction == 's') && direction == hold)
	/* allows the arrow to move up or down, the hold function is to allow the player to rotate direction without moving*/ 
			{
				py = movementchecker(px, py, ex, ey, direction, row, col);
				/*takes the return value from movementchecker equal to py*/
			}
			else if ((direction == 'a' || direction == 'd') && direction == hold)
	/*allows the arrow to move left or right, the hold function is to allow the player to rotate direction without moving*/
			{
				px = movementchecker(px, py, ex, ey, direction, row, col);
				/*takes the return value from movementchecker equal to px*/
			}
	
		}
		free(array);
	}

	return 0;
}
