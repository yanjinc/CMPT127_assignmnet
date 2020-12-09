// count.c
#include <stdio.h>

int main(){

	char check;
	unsigned long int charcount=0;
	unsigned long int wordcount=0;
	unsigned long int linecount=0;
	int signal = 0;  //// start with invalid character
	int invalid = 0; 

	while (check!= EOF){
		check = getchar();
		if( (check >= 'A') && (check <= 'Z') || (check >='a') && (check <= 'z') || (check == (char)39) ){
			charcount++;
			signal = 1; // when still valid
			//printf("c-%lu\t",charcount);
		}
		else{
			signal = 0;  //when start getting invalid
		}

		if(signal == 0 && invalid == 0){
			invalid = 1;
			wordcount++;
			//printf("w-%lu\n",wordcount);
		}
		else if(signal ==1 && invalid ==1){
			invalid =0;
		}
		
		if ( (check == '\n')){
			linecount++;
			charcount++;
			//printf("l-%lu\t",linecount);
			//printf("c-%lu\n",charcount);
		}
	}
	printf("%lu %lu %lu\n",charcount,wordcount,linecount);
	return 0;
}
