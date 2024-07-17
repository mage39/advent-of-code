#include <stdio.h>

int main () {
	FILE* input = fopen("input", "r");
	if (!input) {
		printf("WTF\n");
		return -1;
	}

	int i = fgetc(input);
	int output = 0;

	while (i != EOF) {
		if (i == '(') output++;
		if (i == ')') output--;
		i = fgetc(input);
	}

	printf("%d\n", output);
	return 0;
}
