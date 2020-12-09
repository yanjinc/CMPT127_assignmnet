// scrambled.c
#include <stdio.h>

int scrambled(unsigned int arr1[], unsigned int arr2[],unsigned int len)
{
	int flag[100]={0}, i, j, tempflag; //flag[100] array is used for differentiating same elements getting repeated
	
	if(len==0)
		return 1;
	else
	{
		for (i=0; i<len; i++) 
		{
			tempflag = 0; //tempflag for individual iteration whether the element is found or not
			for (j=0; j<len; j++) 
			{
				if (arr1[i] == arr2[j] && flag[j] == 0) 
				{
					flag[j] = 1;
					tempflag = 1;
					break;
				}
			}

			if(tempflag == 0)
				return 0;
		}
	}

	return 1;
}

/*
int main( void )
{
  	unsigned int arr1[4] = {7, 23, 7, 4};
  	unsigned int arr2[4] = {7, 4, 23, 23};
 
  	if( scrambled( arr1, arr2, 4 ) == 1 )
 	{
     	printf( "arr2 is a scrambled version of arr1\n" );
  	} else {
     	printf( "arr2 has different contents to arr1\n" );
  	}
 
  	return 0;
}
*/
