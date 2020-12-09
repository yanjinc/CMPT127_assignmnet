// t6.c

#include <stdlib.h>
#include <stdio.h>
#include <math.h>



int main() 
{
	
	float n;
	float min = 100001;
	float max = -100001;
	int count = 0;
	float sum = 0;

	while (scanf("%f", &n) != EOF) 
	{
		// smallest value
		if (n < min) min = n;
		// largest value
		if (n > max) max = n;
		// arithmetic mean
		// sum
		sum += n;
		// count
		count ++;

	}

	float mean = sum/count;
	printf("%0.2f %0.2f %0.2f\n", min, max, mean);
}