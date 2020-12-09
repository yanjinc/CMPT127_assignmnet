// t8.c


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
/*
int main() 
{
	int i,j;
	int x,y,z;

	scanf("%d %d %d", &x, &y, &z);
	
	for (i=1; i<=y; i++)
	{
		for (j=1; j<=x; i++) 
		{
			if (i==1 || i==y)
			{
				printf("#");
			} 
			else 
			{
				if (j==1 || j==x) 
				{
					printf("#");
				} 
				else 
				{
					printf(".");
				}
			}
		}
		printf("\n");
	}
	return 0;
} */

int main()
{
  
int x, y, z;
scanf("%d", &x);
scanf("%d", &y);
scanf("%d", &z);
  
for(int i=1; i<=y; i++)
{
	for(int j=1; j<=x; j++)
	{
		if(i==1 || i==y)
		{
			printf("#");	
		}
		else
		{
			if(j==1 || j==x)
			{
				printf("#");
			}
			else
			{
				printf(".");
			}
		}
	}
	printf("\n");
}
  
  

return 0;
}