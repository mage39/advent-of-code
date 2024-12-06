#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define LEN 32
#define NUM "0123456789"

int main (void) {
	FILE* infile = fopen("input.txt", "r");
	int result = 0;
	for (int i = 0; i < 1000; i++) {
		char input[LEN], *inptr = input;
		fgets(input, sizeof(input), infile);
		int nums = 1;
		for (int j = 0; input[j]; j++) if (input[j] == ' ') nums++;
		int level[8], rising = 0, j = 0;
		for (; j < nums; j++) {
			level[j] = atoi(strsep(&inptr, " \t\n"));
			if (j) {
				if (level[j - 1] < level[j] && j < 2) rising = 1;
				if (rising) {
					if (level[j - 1] >= level[j]) break;
					else if (level[j - 1] < level[j] - 3) break;
				} else {
					if (level[j - 1] <= level[j]) break;
					else if (level[j - 1] > level[j] + 3) break;
				}
			}
		}
		if (j > nums - 1) result++;
	}
	fclose(infile);
	printf("%d\n", result);
	return 0;
}
