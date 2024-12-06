#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define LEN 1000
#define NUM "0123456789"

int count (int* arr, int num) {
	int ret = 0;
	for (int i = 0; i < LEN; i++) {
		if (num == arr[i]) ret ++;
	}
	return ret;
}

int main (void) {
	FILE* infile = fopen("input.txt", "r");
	int arrLeft[LEN] = {0}, arrRight[LEN] = {0};
	for (int i = 0; i < LEN; i++) {
		char input[15], *inptr = input;
		fgets(input, sizeof(input), infile);
		arrLeft[i] = atoi(strsep(&inptr, " "));
		arrRight[i] = atoi(strpbrk(inptr, NUM));
	}
	fclose(infile);
	long result = 0;
	for (int i = 0; i < LEN; i++) {
		result += arrLeft[i] * count(arrRight, arrLeft[i]);
	}
	printf("%ld\n", result);
	return 0;
}
