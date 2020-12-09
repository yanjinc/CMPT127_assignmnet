// t9.c

#include <stdlib.h>
#include <stdio.h>
#include <math.h>


int main() 
{
	int x,y,z;
	int j,i;

	scanf("%d", &x);
	scanf("%d", &y);
	scanf("%d", &z);

	for (j=z-1; j>=0; j--) 
	{
		int left = floor( j * (x/(2.0*z)) );
		int right = ceil( (x-1) + (-j) * (x/(2.0*z)) );
		
		for (i=0; i<=right; i++) {
			if (i == left || i == right) {
				printf("#");
			} else if (i<left) {
				printf(" ");
			} else if (i>left && i<right && j!=z-1 && j!=0) {
					printf(".");
			} else if (i>left && i<right && j == z-1) {
					printf("#");
			} else if (i>left && i<right && j == 0) {
					printf("#");
			} 
		}
		printf("\n");
	}

	

	
	return 0;
}















































/*
int main(void) {

	int width, breadth, height, i, j, c=0;

	scanf("%d %d %d", &width, &breadth, &height);

	for(i=height-1; i>0; i--)
	{
		for(j=1; j<i; j++)
			printf(" ");
		printf("#");
		for(j=0; j<c; j++)
			printf(".");
		printf("#\n");
		c += 2;
	}

	for(i=0; i<width; i++)
		printf("#");

	printf("\n");
	
	return 0;

}
*/
