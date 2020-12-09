// identical.c
#include <stdlib.h>
#include <stdio.h>

// declaration of function implemented in identical.c
int identical( int arr1[], int arr2[], unsigned int len );

int identical( int arr1[], int arr2[], unsigned int len ) {
	int res = 1;

	if (len == 0) 
		return res = 1;

	for (unsigned int i=0; i<len; i++) 
	{
		if (arr1[i] != arr2[i]) 
			res = 0;
	}

	return res;

}
