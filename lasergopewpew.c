#define _DEFAULT_SOURCE
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <log.h>


char direction(char direction); /*calling direction to check direction*/
void newSleep(float sec);


/*the main function that help player shoot lazer*/
int playershoot(char** array, int row, int col, int px, int py, char direc, int ex, int ey, char edirec, char laserdirec, char** mirror, int max_size, LinkedList* list) 
{		
	int lazerx = px;
	int lazery = py;
	
	int laserdx = 0;
	int laserdy = 0;
	
	int temp;
	int i;
	int k;	
	int p;
	char direct = direction(direc);
	char edirect = direction(edirec);

	int end = 0;
	switch ( direct ) 
		{
		case 'v':
			laserdy = 1;
			break;
		case '^':
			laserdy = -1;
			break;
		case '<':
			laserdx = -1;
			break;
		case '>':
			laserdx = 1;
			break;
		}
	
	while ((lazerx != 0 && lazerx != row-1) && (lazery != 0 && lazery != col-1)) 
	/*prevents the lazer to go outside border and loop the lazer updated position*/
	{
		newSleep(0.5); /*delay the animation of the lazer so player can see*/
		system("clear");/*remove the previous graph*/
		
		lazerx += laserdy;
		lazery += laserdx;

	
		
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
						if (i == px && k == py) /* a condition to locate the player location*/
			    			{
			    				array[i][k] = direct;
			    			}
			    			
						else if ( i == ex && k == ey) /* a condition to locate enemy location*/
						{

							if (lazerx == ex && lazery == ey) /*if lazer hits the enemy*/
							{
								edirect = 'X';  /*if lazer hit enemy change the symbol to 'X'*/
								array[i][k] = edirect;
								lazerx = 0; /*stop the animation*/
								end = 1; /*end the program*/
							}
							else 
							{
								array[i][k] = edirect; /*if no lazer then continue to print the location of enemy*/
							}
						}
						

						else if (i == lazerx && k == lazery)
						{
							array[i][k] = laserdirec; 
					/*condition to location the position of player's lazer within array*/

							
							
						}

						else
						{
							array[i][k] = ' ';
						/*print the empty space within the array*/
						}
						
						for (p= 0; p< max_size; ++p)
						{

							if (i == mirror[p][0] && k == mirror[p][1])
							{
								if(mirror[p][2] == 'f')
								{	
									array[i][k] = '/';
									if(lazerx == mirror[p][0] && lazery == mirror[p][1])
									{
										
										temp = laserdy;
										laserdy = -laserdx;
										laserdx = -temp;
										if (laserdx == 0)
										{
											laserdirec = '|';
			
										}
										else 
										{
											laserdirec = '-';
										}
										
									}

								}	
								
								else if (mirror[p][2] == 'b')
								{
									array[i][k] = '\\';
									if(lazerx == mirror[p][0] && lazery == mirror[p][1])
									{
									
										temp = laserdx;
										laserdx = laserdy;
										laserdy = temp;

										if(laserdx == 0) 												
										{
											laserdirec = '|';
			
										}
										else 
										{
											laserdirec = '-';
										}
										
									}
								}
							}
						}
					}
				
				}

			}
			LogFrame( list, array,row, col );
			for (i = 0; i < row ; i++) 
			{
				for (k = 0; k < col ; k++) /*a loop to locate all x and y within the array*/
				{
		/*condition to check if the column or row is a lazer, if it is a lazer then change the lazer color to red
					(why no change color? because right now it's 1 hour before due date)*/
					if (array[i][k] == '-' || array[i][k] == '|') 
	
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
			if(edirect == 'X')
			{
				printf("You won!\n"); /*condition to check if enemy is dead, if dead then just print You win!*/
			}
			else
			{
				printf("w to walk up \n");   /*instruction*/
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
