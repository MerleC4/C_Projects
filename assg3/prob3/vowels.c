#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
/*
* File: vowels.c
* Author: Merle Crutchfield
* Purpose: This program is meant to check to see if the 
* input of string has the vowels in ascending order. If
* it does, then it returns 1 for the string, and if not
* then it will have 0.
*/

/*
* containsBadChar(str[]) -- This method runs a for loop that
* checks for each value in a string if they are not a letter
* of the alphabet, when lowercased, to ensure that it is a 
* valid string. Returns 1 if it is not a good string and 0
* if it is.
*/
int containsBadChar(char str[]) {
	for (int i = 0; str[i] != '\0'; i++) {
		if (tolower(str[i]) < 'a' || tolower(str[i]) > 'z') {
			return 1;
		}
	}
	return 0;
}

/*
* hasVals(str[]) -- This method runs a for loop that
* checks for each value in a string if they are a vowel.
* If it is, then it will check to make sure that it is less
* than or equal to the previous vowel, and if not then it
* returns 0. Once it iterates through the end, it will 
* return 1 to show that it is valid.
*/
int hasVals(char str[]) {
	char val ='a';
	for (int i = 0; str[i] != '\0'; i++) {
		if (tolower(str[i]) == 'a' || tolower(str[i]) == 'e' 
			|| tolower(str[i]) == 'i' || tolower(str[i]) == 'o'
			|| tolower(str[i]) == 'u') {
			if (tolower(str[i]) < val) {
				return 0;
			}
			val = str[i];
		}
	}
	return 1;
}


int main(void)
{
	char str[65];
	int r = scanf("%64s", str);
	int val = 0;
	while (r > 0) {
		if (containsBadChar(str)) {
			fprintf(stderr, "Non alpha input: %s\n", str);
			val = 1;
		} else {
			printf("%d\n", hasVals(str));
		}
		r = scanf("%64s", str);
	}
	if (r == 0) {
		fprintf(stderr, "error\n");
		return 1;
	}
	return val;
}