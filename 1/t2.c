//t2.c

#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
	

	printf("%ld", sizeof(char)*CHAR_BIT); 
    printf(" ");
	printf("%ld", sizeof(unsigned char)*CHAR_BIT);
	printf(" ");
	printf("%ld", sizeof(int)*CHAR_BIT);
	printf(" ");
	printf("%ld", sizeof(unsigned int)*CHAR_BIT);
	printf(" ");
	printf("%ld", sizeof(long)*CHAR_BIT);
	printf(" ");
	printf("%ld", sizeof(unsigned long)*CHAR_BIT);
	printf(" ");
	printf("%ld", sizeof(float)*CHAR_BIT);
	printf(" ");
	printf("%ld", sizeof(double)*CHAR_BIT);
	printf(" ");
	printf("%ld", sizeof(long double)*CHAR_BIT);

	printf("\n");
	
}

