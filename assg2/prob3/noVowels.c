#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
/*
* File: noVowels.c
* Author: Merle Crutchfield
* Purpose: Takes in a sequence of strings and first makes sure
* the first string is valid. If it is, it uses that as reference
* and removes the vowels from it. It then checks for each of the
* other strings if they are valid and if they match if their
* vowels are removed then prints them out if they do.
*/

/*
* containsBadVal(str[]) -- This method runs a for loop that
* checks for each value in a string if they are not a letter
* of the alphabet, when lowercased, to ensure that it is a 
* valid string. Returns 1 if it is not a good string and 0
* if it is.
*/
int containsBadVal(char str[]) {
	for (int i = 0; str[i] != '\0'; i++) {
		if (tolower(str[i]) < 'a' || tolower(str[i]) > 'z') {
			return 1;
		}
	}
	return 0;
}

/*
* noVowelCompare(strFirst[], str[]) -- This method runs a for
* loop on the first string entered and then every other string
* in the sequence of strings. This for loop checks to see if
* the char at the location is a vowel, and if it is then it
* removes it when creating the new string without vowels. It
* then checks to see if they are the same and resets the 
* initial array of characters.
*/
void noVowelCompare(char strFirst[], char str[]) {
	char noValFirst[65];
	char noVal[65];
	int index = 0;
	for (int i = 0; strFirst[i] != '\0'; i++) {
		if (!(tolower(strFirst[i]) == 'a' || tolower(strFirst[i]) == 'e' 
			|| tolower(strFirst[i]) == 'i' || tolower(strFirst[i]) == 'o'
			|| tolower(strFirst[i]) == 'u')) {
			noValFirst[index] = tolower(strFirst[i]);
			index = index + 1;
		}
	}
	index = 0;
	for (int i = 0; str[i] != '\0'; i++) {
		if (!(tolower(str[i]) == 'a' || tolower(str[i]) == 'e' 
			|| tolower(str[i]) == 'i' || tolower(str[i]) == 'o'
			|| tolower(str[i]) == 'u')) {
			noVal[index] = tolower(str[i]);
			index = index + 1;
		}
	}
	if (!strcmp(noValFirst, noVal)) {

		printf("%s\n", str);
	}
	// Have to clear origional array of chars for no errors
	memset(noValFirst, 0, 65);
	memset(noVal, 0, 65);
}

int main(void)
{
	char str[65];
	char firstStr[65];
	int r = scanf("%64s", firstStr);
	if (containsBadVal(firstStr)) {
		fprintf(stderr, "First string, %s, is illegal\n", firstStr);
		return 1;
	}
	printf("%s\n", firstStr);
	int val = 0;
	// int count = 0;
	while (r > 0) {
		if (containsBadVal(str)) {
			fprintf(stderr, "Bad string input: %s\n", str);
			val = 1;
		} else {
			noVowelCompare(firstStr, str);
			// printf("we here + %d + r = %d\n", count, r);
			// printf("%d", count);
		}
		// count += 1;
		r = scanf("%64s", str);
	}
	if (r == 0) {
		fprintf(stderr, "Illegal input\n");
		return 1;
	}
	return val;
}