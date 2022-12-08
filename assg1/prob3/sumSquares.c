#include <stdio.h>
#include <math.h>
/*
* File: sumSquares.c
* Author: Merle Crutchfield
* Purpose: Takes in two integers as a range and
* finds each value in that range that is the 
* sum of two squares.
*/ 


/*
* squaresCalc(val) -- Runs a nested for loop to
* iterate over the numbers from 1 to the square
* root of the val entered, since you don't need
* to go more without having overlap, and checks
* to see if it finds a perfect square.
*/ 
void squaresCalc(int val) {
	int i;
	int j;
	for (i = 1; i < sqrt(val); i = i + 1) {
		for (j = 1; j < sqrt(val); j = j + 1) {
			if (i * i + j * j == val) {
				printf("%d\n", val);
				return;
			}
		}
	}
}

int main(void)
{
	int m;
	int n;
	int r = scanf("%d", &m);
	int r2 = scanf("%d", &n);
	if (r > 0 && r2 > 0) {
		if (m > n) {
			return 0;
		}
		if (n < 1 || m < 1) {
			fprintf(stderr, "Both range values must be positive\n");
			return 1;
		}
		int i;
		for (i = m; i <= n; i= i + 1) {
			squaresCalc(i);
		}
	}
	if (r == 0 || r2 == 0) {
		fprintf(stderr, "Usage: sumSquares m n\n");
		return 1;
	}
	return 0;
}