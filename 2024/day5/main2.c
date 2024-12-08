#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define LEN 1200

typedef struct {
	int before;
	int after;
} Order;

int cmp (int a, int b, Order input[LEN]) {
	for (int i = 0; i < LEN && input[i].before; i++) {
		if (a == input[i].before && b == input[i].after) return 1;
		else if (a == input[i].after && b == input[i].before) return -1;
	}
	return 0;
}

void sort (int pages[30], int pageCount, Order input[LEN]) {
	Order pairs[435] = 0; // ncr 30 items, paired = 435
	for (int i = 0; i < 435; i++) {
	}
}

int main (void) {
	FILE* infile = fopen("input.txt", "r");
	if (!infile) return 1;
	Order input[LEN] = {0};
	char line[80];
	for (int i = 0; i < LEN; i++) {
		fgets(line, sizeof(line), infile);
		if (strlen(line) < 2) break;
		char* tok = line;
		input[i].before = atoi(strsep(&tok, "|"));
		input[i].after = atoi(strsep(&tok, "\n"));
	}
	FILE* outfile = fopen("outfile.txt", "w+");
	if (!outfile) return 1;
	while (fgets(line, sizeof(line), infile)) {
		int pages[30] = {0};
		char* tok = line;
		for (int i = 0; i < 30 && tok; i++) pages[i] = atoi(strsep(&tok, ","));
		for (int i = 0; i < 30 && pages[i]; i++) {
			for (int j = 0; j < LEN && input[j].before; j++) {
				if (pages[i] == input[j].after) {
					for (int k = i; k < 30 && pages[k]; k++) {
						if (pages[k] == input[j].before) fprintf(outfile, "%s\n", line);
					}
				}
			}
		}
	}
	fclose(infile);
	fseek(outfile, 0, SEEK_SET);
	int ret = 0;
	while (fgets(line, sizeof(line), outfile)) {
		int pages[30] = {0};
		char* tok = line;
		for (int i = 0; i < 30 && tok; i++) pages[i] = atoi(strsep(&tok, ","));
		int pageCount = 0;
		for (int i = 0; i < 30 && pages[i]; i++) pageCount++;
		sort(pages, pageCount, input);
		ret += pages[pageCount / 2];
	}
	fclose(outfile);
	printf("%d\n", ret);
	return 0;
}
