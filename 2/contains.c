// contains.c
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

void contains(char* str1, char* str2) 
{
	
	if (strstr(str1, str2) != NULL) {
		printf("true\n");
	} else {
		printf("false\n");
	}

}


int main( int argc, char* argv[] )
{
	if( argc != 3 ) 
  	{
  		printf( "I wanted 2 arguments\n" );
  	}

  	contains(argv[1], argv[2]);

  	return 0;
}