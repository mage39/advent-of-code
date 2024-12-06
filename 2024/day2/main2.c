#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define LEN 32

void printList (int* arr, int len) {
	for (int i = 0; i < len; i++) printf("%d ", arr[i]);
	printf("\n");
}

int isSafe (int* arr, int len) {
	int j = 0, rising = 0;
	for (; j < len; j++) {
		if (j) {
			if (arr[j - 1] < arr[j] && j < 2) rising = 1;
			if (rising) {
				if (arr[j - 1] >= arr[j]) break;
				else if (arr[j - 1] < arr[j] - 3) break;
			} else {
				if (arr[j - 1] <= arr[j]) break;
				else if (arr[j - 1] > arr[j] + 3) break;
			}
		}
	}
	if (j > len - 1) return 1;
	else return 0;
}

int* rmIdx (int* arr, int len, int idx) {
	int* ret = malloc((len - 1) * sizeof(int));
	memcpy(ret, arr, idx * sizeof(int));
	idx++;
	memcpy(ret + idx - 1, arr + idx, (len - idx) * sizeof(int));
	return ret;
}


int main (void) {
	FILE* infile = fopen("input.txt", "r");
	int result = 0;
	for (int i = 0; i < 1000; i++) {
		char input[LEN], *inptr = input;
		fgets(input, sizeof(input), infile);
		int nums = 1;
		for (int j = 0; input[j]; j++) if (input[j] == ' ') nums++;
		int level[8];
		for (int j = 0; j < nums; j++) {
			level[j] = atoi(strsep(&inptr, " \n"));
		}
		if (isSafe(level, nums)) result++;
		else {
			for (int j = 0; j < nums; j++) {
				int* arr = rmIdx(level, nums, j);
				/* DEBUG
				printf("%d, ", isSafe(arr, nums - 1));
				printList(arr, nums - 1);
				printList(level, nums);
				*/
				if (isSafe(arr, nums - 1)) {
					free(arr);
					result++;
					break;
				}
				free(arr);
			}
		}
	}
	fclose(infile);
	printf("%d\n", result);
	return 0;
}
