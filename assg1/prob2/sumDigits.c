#include <stdio.h>
/*
* File: sumDigits.c
* Author: Merle Crutchfield
* Purpose: Takes in a number and calculates the
* sum of all the digits using logic, instead of
* using string manipulation or arrays. 
*/ 

int main(void)
{
	int n;
	int spot;
	int r = scanf("%d", &n);
	int val = 0;
	while (r > 0) {
		int check = 1;
		int sum = 0;
		if (n < 1) {
			fprintf(stderr, "ERROR: %d is not positive\n", n);
			val = 1;
			check = 0;
		}
		while (n > 0) {
			spot = n % 10;
			sum = sum + spot;
			n = n/10;
		}
		if (check) {
			printf("%d\n", sum);
		}
		r = scanf("%d", &n);
	}
	if (r == 0) {
		fprintf(stderr, "Non-integer input.\n");
		return 1;
	}
	return val;
}