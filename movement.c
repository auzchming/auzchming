
#include <stdio.h>
#include <stdlib.h>

char direction(char direction) /*a function that checks the direction and input of the player*/
{
	int i;
	char input[4] = {'w', 'a', 's', 'd'}; /*takes the string and allign it*/
	char direc[4] = {'^', '<', 'v', '>'};
	char ans = direc[3];


	for (i = 0; i < 5; i++)
	{
		if (direction == input[i])
		{
			ans = direc[i];
		}    
	}

	return ans; /*return ans that contains the direction*/
}


int movementy(int playery, int row, char direct) /*controls and limit the movement in the direction of y */
{
	int py = playery;
	int border = row - 2;

	if (direct == 'w' && py > 1) /*if direction is w and within the border(it's 1 because top right corner of the map is 1) */
	{
		py -= 1;
	}
	else if (direct == 's' && py < border) /*if direction is w and within the border */
	{
		py += 1;
	}

	return py; /*returns the new location of py*/
}



int movementx(int playerx, int col, char direct)
/*same as movementy but everything in x direction*/
{
	int px = playerx;
	int border = col - 2;

	if (direct == 'a' && px > 1)
	{
		px -= 1;
	}
	else if (direct == 'd' && px < border)
	{
		px += 1;
	}
	return px;
}

int check(char direction) /*a function that checks the direction*/
{
	int ans = 0;
	if (direction == 'w' || direction == 'a' || direction == 's' || direction == 'd' || direction == 'f' || direction == 'l')
	{
		ans = 1;
	}
	return ans; /* if direction is within one of these option then it will return the variable 1*/
}

int count(char *input) /*a counter*/
{    
	int count = 0;
	int i = 0;
	while(input[i] != '\0') /*while input have something then it count*/
	{
		count ++;
		i++;
	}
	return count;
}

int movementchecker(int playerx, int playery, int enemyx, int enemyy, char direction, int row, int col, int** mirror, int max_size) 
/*the function that uses movementx and movementy to move the player */
{
	int p;
	int px = playerx;
	int py = playery;
	int ex = enemyx;
	int ey = enemyy;
	int ans = 0;

	if (direction == 'a' || direction == 'd') /*checks if the direction is left or right*/
	{
		px = movementx(px, col, direction);
		if (py == ex && px == ey && direction == 'd') 
/*calls the movement function and if its right then the character will move right*/
		{
			px -= 1;
		}
		else if (py == ex && px == ey && direction == 'a')/*if its left then the character will move left*/
		{
			px += 1;
		}
		ans = px; /*return the new location of px*/

	}
	else if (direction == 'w' || direction == 's') /*same thing above but up and down*/
	{
		py = movementy(py, row, direction);
		if (py == ex && px == ey && direction == 'w')
		{
			py += 1;
		}
		else if (py == ex && px == ey && direction == 's')
		{
			py -= 1;
		}
		ans = py;

	}
	for (p= 0; p< max_size; ++p) 
/*similar to above, this checks if the location of mirror is equal to player it will move the player back (which equal to the player not moving*/
	/*loops through the max_size(the number of mirror available)*/
	{
		if (direction == 'a' || direction == 'd') /*checks the direction of the player*/
		{
			if ( py == mirror[p][0] && px == mirror[p][1] && direction == 'd')
			/*using the direction of the player to determine where to move the player back (by the time i created this I know there are better ways to do this but im too late) */
			{
				px -= 1;
			}
			else if (py == mirror[p][0] && px == mirror[p][1] && direction == 'a')
			{
				px += 1;
			}
			ans = px;
		}
		else if (direction == 'w' || direction == 's') /*same as above but this checks for the direction for up and down*/
		{

			if (py == mirror[p][0] && px == mirror[p][1] && direction == 'w')
			{
				py += 1;
			}
			else if (py == mirror[p][0] && px == mirror[p][1] && direction == 's')
			{
				py -= 1;
			}
			ans = py;
		}
	}
						
	return ans;/* return the new location of py*/
}
