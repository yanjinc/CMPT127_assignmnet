// t3.c

#include <stdio.h>
#include <math.h>

int main() {
	double floor(double x);
	double round(double x);
	double ceil(double x);
	double i;

	
	scanf("%lf", &i);

	printf("%d", (int) floor(i));
	printf(" ");
	printf("%d", (int) round(i));
	printf(" ");
	printf("%d\n", (int) ceil(i));
	
	return 0;
}