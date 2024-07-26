#include <stdio.h>
#include <stdlib.h>

int main () {
	FILE* input = fopen("input", "r");
	if (!input) {
		printf("WTF\n");
		return -1;
	}

	char line[10] = {0};
	int total = 0, lc = 0;
	
	while (fgets(line, 10, input)) {
		if (!line[1]) break;
		int length = 0, width = 0, height = 0, i = 0, slack = 0;
		length = atoi(line);
		for (; line[i] != 'x'; i++);
		width = atoi(line + ++i);
		for (; line[i] != 'x'; i++);
		height = atoi(line + ++i);

		if (length > width) {
			if (length > height) {
				slack = width * height;
			} else {
				slack = width * length;
			}
		} else {
			if (width > height) {
				slack = length * height;
			} else {
				slack = length * width;
			}
		}
		total += 2 * length * width + 2 * width * height + 2 * height * length + slack;
		lc++;
	}
	printf("%d, lc = %d\n", total, lc);

	return 0;
}
