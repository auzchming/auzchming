#include <stdio.h>
#include <stdlib.h>

char direction(char direction); /*calling direction to check direction*/
void newSleep(float sec);

/*the main function that help enemy shoot lazer*/
int enemyshoot(char** array, int row, int col, int px, int py, char direc, int ex, int ey, char edirec, char elaserdirec, char** mirror, int max_size) 
{

	int elazerx = ex;
	int elazery = ey;
	
	int i;
	int k;	
	
	char direct = direction(direc);
	char edirect = direction(edirec);
	
	int end = 0;
	
	while ((elazerx != 0 && elazerx != row-1) && (elazery != 0 && elazery != col-1) )
	/*prevents the lazer to go outside border and loop the lazer updated position*/
	{
		newSleep(0.5); /*delay the animation of the lazer so player can see*/
		system("clear"); /*remove the previous graph*/
		
		
		if (edirect == 'v')
		{
			elazerx += 1;
		}
		else if (edirect == '^')
		{
			elazerx -= 1;
		}
		else if (edirect == '<')   /*checks the direction of the enemy and determine the lazer moving direction*/
		{
			elazery -= 1;
		}
		else if (edirect == '>')
		{
			elazery += 1;
		}
		
		if (col <= 5 || row <= 5)
		{
			printf("col should be more than 5 \n"); /*check if col or row smaller or equal to 5*/
		}
		else 
		{
	
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
					else 
					{
						if (i == px && k == py)  /* a condition to locate the player location*/
			    			{
							if (elazerx == px && elazery == py) /*if the lazer hits player then kill player*/
							{
								direct = 'X'; /*changing the state of the player*/
								array[i][k] = direct; 
								elazerx = 0;/*ending the animation*/
								end = 1; /*ending the program*/
							} 
							else 
							{
			    					array[i][k] = direct; 
						/*if no lazer is fired then continue to print the location of the player*/
							}
			    			}
			    			
						else if ( i == ex && k == ey) /*print the location of the enemy*/
						{
							array[i][k] = edirect;
						}
						

						else if (i == elazerx && k == elazery) /*print the enemy lazer location*/
						{
							
							array[i][k] = elaserdirec;
							
						}

						else
						{
							array[i][k] = ' '; /*if no other condition is met print empty space*/
						}
					}
				}
			}
	
			for (i = 0; i < row ; i++) 
			{
				for (k = 0; k < col ; k++) /*a loop to locate all x and y within the array*/
				{
					if (array[i][k] == '-' || array[i][k] == '|') 
			/*condition to check if the column or row is a lazer, if it is a lazer then change the lazer color to red*/
					{
						printf("\033[0;31m");
						printf("%c", array[i][k]);
						printf("\033[0m");
					}
					else
					{
			/*if not lazer position then just normally print the array*/
						printf("%c", array[i][k]);
					}
				}
				printf("\n");
				free(array[i]);
			}
			if(direct == 'X')
			{
				printf("You lose!\n"); /*condition to check if player is dead, if dead then just print You lose!*/
				
			}
			else
			{
				printf("w to walk up \n"); /*instruction*/
				printf("s to walk down \n");
				printf("a to walk left \n");
				printf("d to walk right \n");
				printf("f to Shoot laser \n");
				printf("Action: \n");
			}	 
		}
	}
	return end;
}
