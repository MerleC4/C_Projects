#include <stdio.h>
#include <ctype.h>
/*
* File: splitString.c
* Author: Merle Crutchfield
* Purpose: This program takes in an input stream and
* splits it up at the '-' character without using
* any methods from the string.h library. It uses a
* for loop to iterate through each value and print it
* out appropriately.
*/

/*
* splitString(str[]) -- This takes in the string entered
* and iterates through it to check if it is the '-' is
* present. If it is, then it will remove it and split it
* to print out the strings appropriately.
*/
void splitString(char str[]) {
	int isntEmpty = 0;
	char prevChar = 'a';
	for (int i = 0; str[i]; i++) {
		if (str[i] == '-') {
			if (isntEmpty && prevChar != '-') {
				printf("\n");
			}
		} else {
			printf("%c", str[i]);
			isntEmpty = 1;
		}
		prevChar = str[i];
	}
	if (prevChar != '-') {
		printf("\n");
	}
}


int main(void)
{
	char str[256];
	int r = scanf("%255s", str);
	int val = 0;
	while (r > 0) {
		splitString(str);
		r = scanf("%255s", str);
	}
	if (r == 0) {
		fprintf(stderr, "Illegal input\n");
		return 1;
	}
	return val;
}