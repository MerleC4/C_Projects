#include <stdio.h>
#include <ctype.h>
#include <string.h>
/*
* File: palindrome.c
* Author: Merle Crutchfield
* Purpose: This code reads in words in string format that
* are checked to see if they are a palindrome. If they are
* then it prints out 1 to show yes, and 0 to signify that
* it isn't. There were no error cases so it should always
* return 0.
*/

/*
* palindrome(str[]) -- This method runs a for loop that checks
* if the coresponding character starting from the front matches
* the one in the back. If it does, then it keeps on going until
* it reaches halfway, and prints out if it is a palindrome.
* 
*/
void palindrome(char str[]) {
	int isPal = 1;
	int length = strlen(str);
	int tail = length-1;
	for (int i = 0; i < length / 2; i++) {
		if (tolower(str[i]) != tolower(str[tail])) {
			isPal = 0;
		}
		tail = tail - 1;
	}
	printf("%d\n", isPal);
}

int main(void)
{
	char str[65];
	int r = scanf("%64s", str);
	int val = 0;
	while (r > 0) {
		palindrome(str);
		r = scanf("%64s", str);
	}
	if (r == 0) {
		fprintf(stderr, "Illegal input\n");
		return 1;
	}
	return val;
}