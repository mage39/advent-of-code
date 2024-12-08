#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define LEN 1200

typedef struct {
	int before;
	int after;
} Order;

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
	int ret = 0;
	while (fgets(line, sizeof(line), infile)) {
		int pages[30] = {0};
		char* tok = line;
		for (int i = 0; i < 30 && tok; i++) pages[i] = atoi(strsep(&tok, ","));
		for (int i = 0; i < 30 && pages[i]; i++) {
			for (int j = 0; j < LEN && input[j].before; j++) {
				if (pages[i] == input[j].after) {
					for (int k = i; k < 30 && pages[k]; k++) {
						if (pages[k] == input[j].before) goto fail;
					}
				}
			}
		}
		int pageCount = 0;
		for (int i = 0; i < 30 && pages[i]; i++) pageCount++;
		ret += pages[pageCount / 2];
fail:;
	}
	fclose(infile);
	printf("%d\n", ret);
	return 0;
}
