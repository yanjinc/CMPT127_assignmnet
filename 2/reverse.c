// reverse.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//declaration of function implemented in reverse.c
void reverse( int arr[], unsigned int len );

void reverse( int arr[], unsigned int len ) 
{
	int end = len-1;
	for (unsigned int i=0; i<len/2; i++) 
	{
		int t = arr[i];
		arr[i] = arr[end];
		arr[end] = t;
		end--;
	}
}
