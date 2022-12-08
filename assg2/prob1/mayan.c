#include <stdio.h>
#include <ctype.h>
/*
* File: mayan.c
* Author: Merle Crutchfield
* Purpose: This code takes in a Mayan number that fits
* the description in the spec and converts it to base 
* 10 for us to read. This converts the string entered
* from base 20 to decimal without using if then else or
* switch statements, and instead uses Horners rule.
*/

/*
* convert(str[]) -- This method runs a for loop that makes sure the
* characters entered are valid for Mayan to be converted. It then
* adds to the result using Horners rule, and if it is a valid string
* entered prints it out and if not it prints out that it is illegal.
* Returns whether the string entered was legal or illegal.
*/
int convert(char str[]) {
	int result = 0;
	int valid = 1;
	for (int i = 0; str[i]; i++) {
		if ((tolower(str[i]) - 'a' > 19) || (tolower(str[i]) - 'a' < 0)) {
			valid = 0;
		}
		result = result * 20 + tolower(str[i]) - 'a';
	}
	if (valid) {
		printf("%d\n", result);
	} else {
		fprintf(stderr, "Illegal input\n");
		return 1;
	}
	return 0;
}

int main(void)
{
	char str[7];
	int r = scanf("%6s", str);
	int val = 0;
	int check = 0;
	while (r > 0) {
		check = convert(str);
		r = scanf("%6s", str);
		if (check) {
			val = 1;
		}
	}
	if (r == 0) {
		fprintf(stderr, "Illegal input\n");
		return 1;
	}
	return val;
}
