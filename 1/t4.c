// t4.c

#include <stdio.h>
#include <math.h>

int main() {
	double floor(double x);
	double round(double x);
	double ceil(double x);
	double i;
	int a=0;

	
	a = scanf("%lf", &i);

	if ( a == 0 ) {
		printf("scanf error: (%d)\n", a);
	} else {
		printf("%d", (int) floor(i));
		printf(" ");
		printf("%d", (int) round(i));
		printf(" ");
		printf("%d\n", (int) ceil(i));
	}
	
	
	return 0;
}


