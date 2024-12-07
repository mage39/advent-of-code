#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#define LEN 20000

int main (void) {
	FILE* infile = fopen("input.txt", "r");
	char input[LEN] = {0};
	fread(input, 1, LEN, infile);
	fclose(infile);
	char* mul = strstr(input, "mul(");
	char* tok = strstr(input, "don't()");
	if (tok) *tok = 0;
	tok = strstr(tok + 1, "do()");
	long ret = 0;
	while (mul) {
		mul += 4;
		// if (*mul == ' ') goto cont;
		char* endptr;
		long a = strtol(mul, &endptr, 10);
		if (*endptr != ',' || endptr == mul) goto cont;
		mul = endptr + 1;
		long b = strtol(mul, &endptr, 10);
		if (*endptr != ')' || endptr == mul) goto cont;
		ret += a * b;
cont:
		mul = strstr(mul, "mul(");
		if (mul) continue;
		if (!tok) break;
		mul = strstr(tok, "mul(");
		tok = strstr(tok, "don't()");
		if (tok) {
			*tok = 0;
			tok = strstr(tok + 1, "do()");
		}
	}
	printf("%ld\n", ret);
	return 0;
}
