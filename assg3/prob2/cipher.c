#include <stdio.h>
#include <ctype.h>
/*
* File: cipher.c
* Author: Merle Crutchfield
* Purpose: This program is meant to set up a cipher when the
* user enters a number, and shift the value of all characters
* by the numeber entered. It doesn't change non-alpha
* characters, but only the alpha ones to the coresponding value.
*/

/*
* cipher(str[], num) -- This takes in the value and makes sure
* that it isnt just a number. Once that is true, it iterates
* through the string and checks to see if it is am alpha 
* character, and if not just prints it out. If it is, then it
* uses the cipher code to appropriately shift the value.
*/
int cipher(char str[], int num) {
	int isntValid = 0;
	for (int i = 0; str[i] != '\0'; i++) {
		if (isalpha(str[i])) {
			isntValid = 1;
		}
	}
	if (!(isntValid)) {
		printf("Not alpha-numeric string: %s\n", str);
		return 1;
	}
	for (int i = 0; str[i] != '\0'; i++) {
		if (!(isalpha(str[i]))) {
			printf("%c", str[i]);
		} else {
			char val = str[i] + num;
			if ((val >= 'a' && val <= 'z') || (val >= 'A' && val <= 'Z')) {
				printf("%c", val);
			} else {
				if (val > 'z') {
					val = val - 26;
				}
				else if (val > 'Z' && val < 'a' && num > 0) {
					val = val - 26;
				} else if (val > 'Z' && val < 'a' && num < 0) {
					val = val + 26;
				} else if (val < 'A') {
					val = val + 26;
				}
			printf("%c", val);
			}
		}
	}
	printf("\n");
	return 0;
}


int main(void)
{
	int num;
	char str[256];
	int r = scanf("%d", &num);
	if (r == 0) {
		fprintf(stderr, "No rotation value input\n");
		return 1;
	}
	int val = 0;
	while (r > 0) {
		r = scanf("%255s", str);
		val = cipher(str, num);
	}
	if (r == 0) {
		fprintf(stderr, "Illegal input\n");
		return 1;
	}
	return val;
}