#include <stdio.h>

int main () {
	FILE* input = fopen("input", "r");
	if (!input) {
		printf("WTF\n");
		return -1;
	}

	int c = fgetc(input);
	int output = 0;
	int i = 1;

	while (c != EOF) {
		if (c == '(') output++;
		if (c == ')') output--;
		if (output < 0) break;
		c = fgetc(input);
		i++;
	}

	printf("%d\n", i);
	return 0;
}
