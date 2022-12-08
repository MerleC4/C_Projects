#include <stdio.h>
/*
* File: isFib.c
* Author: Merle Crutchfield
* Purpose: Takes in a value and checks to see if
* it is in the fibanacci sequence using a for loop.
* It will keep runing until the end of file or until
* something other than an integer is entered.
*/ 

/*
* isFib(n) -- This method runs a for loop that
* each loop produces a number in the fibanacci
* sequence and then checks to see if it matches
* the number entered. If it does, then the number
* is in the sequence, but if it is ever bigger
* than the number then it can't be in the sequence.
*/
void isFibanacci(int n) {
	int front = 1;
	int back = 2;
	int total;
	int i;
	for (i = 0; i < n; i = i + 1) {
		if (n == front || n == back) {
			printf("%d is fib\n", n);
			return;
		}
		else if (front > n) {
			printf("%d is not fib\n", n);
			return;
		}
		total = front + back;
		front = back;
		back = total;
	}
}

int main(void)
{
	int n;
	int r = scanf("%d", &n);
	int val = 0;
	while (r > 0) {
		if (n < 1) {
			fprintf(stderr, "ERROR: %d is not a positive integer\n", n);
			val = 1;
		}
		else {
			isFibanacci(n);
		}
		r = scanf("%d", &n);
	}
	if (r == 0) {
		fprintf(stderr, "Non-integer input\n");
		return 1;
	}
	return val;
}