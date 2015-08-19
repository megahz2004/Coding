#include <stdio.h>

/* Description: fill 1~9 in 9x9 matix. For each row and column, the sum is 15. */

int edge[] = {0,0/*1*/, 0,2/*2*/, 2,0/*3*/, 2,2/*4*/}; // number 8 has 4 position could be filled 
int cross[] = {0,1/*up*/, 1,2/*right*/, 2,1/*down*/, 1,0/*left*/}; // 4 cross positions for filling number 7 and 9
int sum = 15;

void verify( int arr[3][3])
{
	int x,y;
	for(x=0; x<3; x++)
	{
		int sum = 0;
		for(y=0; y<3; y++)
		{
			sum = sum + arr[x][y];
		}
		if(sum != 15)
		{
			printf("error!, sum = %d\n", sum);
			exit(1);
		}
	}
	for(y=0; y<3; y++)
	{
		int sum = 0;
		for(x=0; x<3; x++)
		{
			sum = sum + arr[x][y];
		}
		if(sum != 15)
		{
			printf("error!, sum = %d\n", sum);
			exit(1);
		}
	}
}

main ()
{
	int i, j;
	for(i = 0; i < 8; i=i+2)
	{
		int nine[3][3] = {{0,0,0}, {0,5,0}, {0,0,0}}; // number 5 is always in the center
		int eight_x = edge[i];
		int eight_y = edge[i+1];
		int seven_x, seven_y;
		int nine_x, nine_y;
		// fill 8
		nine[eight_x][eight_y] = 8;

#if DEBUG
		printf( "8_x %d, 8_y %d\n", eight_x, eight_y);
#endif

		for(j = 0; j < 8; j=j+2)
		{
			// fill 7
			if((cross[j] != eight_x) && (cross[j+1] != eight_y))
			{	
				int a, b;
				seven_x = cross[j];
				seven_y = cross[j+1];
				nine[seven_x][seven_y] = 7;
#if DEBUG
				printf("7_x %d, 7_y %d\n", seven_x, seven_y);
#endif

				// fill 9
				nine_x = 3 - eight_x - seven_x;
				nine_y = 3 - eight_y - seven_y;
				nine[nine_x][nine_y] = 9;
#if DEBUG
				printf("9_x %d, 9_y %d\n", nine_x, nine_y);
#endif

				// fill remaining numbers
				// find 7, fill 3 
				if( seven_x == 1 )
					nine[seven_x][2 - seven_y] = 3;
				else if( seven_y == 1 )
					nine[2 - seven_x][seven_y] = 3;

				// find 9, fill 1
				if( nine_x == 1 )
					nine[nine_x][2 - nine_y] = 1;
				else if( nine_y == 1 )
					nine[2 - nine_x][nine_y] = 1;

				// find 8, fill 2, 
				nine[2 - eight_x][2 - eight_y] = sum - 8 - 5; 

				// fill 4, 6
				nine[2 - eight_x][eight_y] = sum - 8 - nine[1][eight_y];
				nine[eight_x][2 - eight_y] = sum - 8 - nine[eight_x][1];

				for(a = 0; a < 3; a++)
				{
					for(b = 0; b < 3; b++)
						printf("%d ", nine[a][b]);
					printf("\n");
				}
				printf("\n");

				verify(nine);

			}

		}
	}

}
