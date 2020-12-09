// verticalgraph.c
#include <stdio.h>
#include <stdlib.h>

int main() {
	int n, count=0;
	int arr[80];
	int i, r, c;

	//store input into arr[]
	while (scanf("%d", &arr[count]) != EOF && count < 80) {
		++ count; 
	}

	if (count == 0) return 1;

	//find max
	int max = arr[0];
	for (i=0; i<count; i++) {
		if (arr[i]>max) {
			max = arr[i];
		}
	}

	//memory allocation
	//2d array matrix
	//Allocate row pointers
	char **matrix;
	matrix = (char**) malloc (max*sizeof(char*)); //max menas rows
	//Allocate each row separately
	for (r=0; r<max; r++) {
		matrix[r] = (char*) malloc (count*sizeof(char)); //count means columns
	}

	//draw the graph
	for (r=max-1; r>=0; r--) {
		for (c=0; c<count; c++) {
			if(arr[c] > r) {
				matrix[r][c] = '#';
			} else {
				matrix[r][c] = ' ';
			}
		}
	}

	//print the graph
	for (r=max-1; r>=0; r--) {
		for (c=0; c<count; c++) {
			printf("%c", matrix[r][c]);
		}
		printf("\n");
	} 

	return 0;
}
