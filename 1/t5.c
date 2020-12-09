// t5.c

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main()
{

	float n;

	while (scanf("%f", &n) != EOF)
	{
		int x,y,z;

		x = floor(n); // 
		y = round(n); 
		z = ceil(n); 

		printf("%d %d %d\n",x,y,z);
	}

	printf("Done.\n");

	return 0;

} 