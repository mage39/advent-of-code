#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define LEN 1000
#define NUM "0123456789"

int cmp (const void* a, const void* b) {
	if (*(int*)a > *(int*)b) return 1;
	else if (*(int*)a < *(int*)b) return -1;
	else return 0;
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
	qsort(arrLeft, LEN, sizeof(int), &cmp);
	qsort(arrRight, LEN, sizeof(int), &cmp);
	long result = 0;
	for (int i = 0; i < LEN; i++) result += abs(arrLeft[i] - arrRight[i]);
	printf("%ld\n", result);
	return 0;
}
