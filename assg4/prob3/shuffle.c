#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/*
* File: shuffle.c
* Author: Merle Crutchfield
* Purpose: This is used to take in two arrays of numbers and
* to shuffle them when combining them together alternating.
* It uses getline and sscanf similar to the sumLine.c file
* to read in the values, and then passes both of the arrays
* to a separate method to put them together.
*/

/*
* digitCount(int) -- This is used to count how many digits
* are in an integer. Returns the number of digits.
*/
int digitCount(int n) {
	int count = 0;
	while (n != 0) {
		n = n/10;
		count = count + 1;
	}
	return count;
}

/*
* combineArrays(int[], int[], int, int) -- This takes in two arrays
* of ints and their sizes. It uses a while loop to iterate through
* and print out the appropriate values in the order to put them
* together alternating.
*/
void combineArrays(int arr1[256], int arr2[256], int i, int j) {
	int k = 0;
	while (k < i || k < j) {
		if (k < i) {
			printf("%d\n", arr1[k]);
		}
		if (k < j) {
			printf("%d\n", arr2[k]);
		}
		k++;
	}
}

int main(void)
{
	int val = 0;
	int block = 1;
	char* line = NULL;
	size_t len = 0;
	int i = 0;
	int j = 0;
	while (getline(&line, &len, stdin) != EOF) {
		int arr1[256], arr2[256];
		int num;
		int good = 1;
		while (sscanf(line, "%d", &num) < len) {
			if (isdigit(line[0]) || (line[0] == '-' && isdigit(line[1]))) {
				if (block == 1) {
					arr1[i] = num;
					i++;
				}
				if (block == 2) {
					arr2[j] = num;
					j++;
				}
				line = line + sizeof(num)/sizeof(int)+digitCount(num);
			}
			else {
				if (line[0] != ' ') {
					good = 0;
					val = 1;
				}
				line = line + sizeof(line[0])/sizeof(char);
			}
		}
		if (!(good)) {
			if (block == 1) {
				fprintf(stderr, "Error in 1st line\n");
				return 1;
			} 
			if (block == 2) {
				fprintf(stderr, "Error in 2nd line\n");
				return 1;
			}
		}
		if (block == 2) {
			combineArrays(arr1, arr2, i, j);
			return 0;
		}
		block++;
	}
	return val;
}