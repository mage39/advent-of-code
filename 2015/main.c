#include <stdio.h>
#include <stdlib.h>

int main () {
	FILE* input = fopen("input", "r");
	if (!input) {
		printf("WTF\n");
		return -1;
	}

	char line[10] = {0};
	int total = 0;
	
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
				slack = 2 * width + 2 * height;
			} else {
				slack = 2 * width + 2 * length;
			}
		} else {
			if (width > height) {
				slack = 2 * length + 2 * height;
			} else {
				slack = 2 * length + 2 * width;
			}
		}
		total += slack + length * width * height;
	}
	printf("%d\n", total);

	return 0;
}
