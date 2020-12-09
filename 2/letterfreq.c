// letterfreq.c
#include <stdio.h>

int main (void) {
	int c;
	int letterCount[26];
	int totalLetters = 0;
	double freq;
	int i;

	//set lettercount array to 0
	for (i=0; i<26; i++) {
		letterCount[i] = 0;
	}

	//run while loop until EOF is reached
	while ((c = getchar( )) != EOF) {
		//lower case
		if (c>='a' && c<='z') {
			letterCount[c-97] += 1;
			totalLetters += 1;
		}
		//upper case
		if (c>='A' && c<='Z') {
			letterCount[c-65] += 1;
			totalLetters += 1;
		}
	} //while loop end
	//printf("\n");
	
	//use loop to calculate freq
	for (i=0; i<26; i++) {
		if (letterCount[i] != 0) {
			int letter = i+97;
			freq = (double) letterCount[i] / (double) totalLetters;
			printf( "%c %.4f\n", letter, freq);
		}
	}
	return 0;
}