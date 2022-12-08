#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/*
* File: sumLine.c
* Author: Merle Crutchfield
* Purpose: This is used to read in different lines and to
* get the sum of them. They will be separated with different
* sizes of whitespace, and we have to use sscanf and getline
* methods to read them in. It then prints out the total of 
* each line.
*/

/*
* digitCount(int) -- This is used to count how many digits
* are in an integer. Returns the number of digits.
*/
int digitCount(int n) {
	if (n == 0) {
		return 1;
	}
	int count = 0;
	while (n != 0) {
		n = n/10;
		count = count + 1;
	}
	return count;
}

int main(void)
{
	int val = 0;
	int block = 1;
	char* line = NULL;
	size_t len = 0;

	while (getline(&line, &len, stdin) != EOF) {
		block++;
		int sum = 0;
		int num;
		int good = 1;
		while (sscanf(line, "%d", &num) < len) {
			if (isdigit(line[0]) || (line[0] == '-' && isdigit(line[1]))) {
				if (num < 0) {
					good = 0;
					val = 1;
				} else {
					sum = sum + num;
				}
				line = line + sizeof(num)/sizeof(int)+digitCount(num);
			}
			else if (line[0] != ' ') {
				good = 0;
				val = 1;
				line = line + sizeof(line[0])/sizeof(char);
			}
			else {
				line = line + sizeof(line[0])/sizeof(char);
			}
		}
		if (good) {
			printf("Final sum: %d\n", sum);
		} else {
			fprintf(stderr, "Bad line input\n");
		}
	}
	return val;
}