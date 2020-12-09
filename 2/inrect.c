//inrect.c
#include <stdio.h>
#include <stdlib.h>

// function 
int InRectangle( float pt[2], float rect[4] ) {
	
	if (rect[0] < rect[2] && rect[1] < rect[3]) {
		if (pt[0]>=rect[0] && pt[0]<=rect[2] && pt[1]>= rect[1] && pt[1]<=rect[3]) {
			return 1; // true
		}
		else {
			return 0;
		}
	} else if (rect[2] < rect[0] && rect[3] < rect[1]) {
		if (pt[0]>=rect[2] && pt[0]<=rect[0] && pt[1]>= rect[3] && pt[1]<=rect[1]) {
			return 1;
		}
		else {
			return 0;
		}
	} else if (rect[0] < rect[2] && rect[1] > rect[3]) {
		if (pt[0]>=rect[0] && pt[0]<=rect[2] && pt[1]>= rect[3] && pt[1]<=rect[1]) {
			return 1;
		}
		else {
			return 0;
		}
	} else if (rect[2] < rect[0] && rect[3] > rect[1]) {
		if (pt[0]>=rect[2] && pt[0]<=rect[0] && pt[1]>= rect[1] && pt[1]<=rect[3]) {
			return 1;
		}
		else {
			return 0;
		}
	}

	return 0; // false; point outside
}
