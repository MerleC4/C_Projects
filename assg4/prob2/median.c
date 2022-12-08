#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
/*
* File: median.c
* Author: Merle Crutchfield
* Purpose: This is used to take in an array of numbers,
* allocate memory using malloc, and then find the median
* value of them. It uses a nested for loop to achieve this
* and prints out the median value after sorting the array
* in order.
*/

/*
* sortAndMed(int[], int) -- This is used to first sort
* the array in ascending order using a nested for loop.
* Once this is done, it declares a float and checks to
* see if it needs to be an average of two numbers or just
* the center number.
*/
void sortAndMed(int ptr[], int num) {
	for (int i = 0; i < num; i++) {
		for (int j = i + 1; j < num; j++) {
			if (ptr[i] > ptr[j]) {
				int temp = ptr[i];
				ptr[i] = ptr[j];
				ptr[j] = temp;
			}
		}
	}
	float med = 0;
	if (num % 2 == 0) {
		med = (ptr[(num-1)/2]+ptr[num/2])/2.0;
		printf("%.1lf\n", med);
	} else {
		med = ptr[num/2];
		printf("%.1lf\n", med);
	}
}

int main(void)
{
	int num;
	int* ptr;
	int r = scanf("%d", &num);
	if (num < 1) {
		fprintf(stderr, "First input must be a positive integer.\n");
		return 1;
	}
	ptr = (int *) malloc(num*sizeof(int));
	int count = 0;
	while ((r > 0) && (count < num)) {
		r = scanf("%d", &ptr[count]);
		count++;
	}
	if (r == 0) {
		fprintf(stderr, "Must input %d integers.\n", num);
		return 1;
	}
	sortAndMed(ptr, num);
	return 0;
}