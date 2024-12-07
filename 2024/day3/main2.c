#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#define LEN 20000

typedef struct {
	char* mul;
	char* enable;
	char* disable;
} Triple;

enum {
	SEARCHMUL = 1,
	SEARCHEN = 1 << 1,
	SEARCHDIS = 1 << 2
};

static Triple search (Triple a, unsigned flags) {
	if (flags & SEARCHMUL) a.mul = strstr(a.mul, "mul(");
	if (flags & SEARCHEN) {
		a.enable = strstr(a.enable, "do()") + strlen("do()");
		a.mul = a.enable;
		a.mul = strstr(a.mul, "mul(");
		a.disable = strstr(a.disable, "don't()") + strlen("don't()");
	}
	return a;
}

int main (void) {
	FILE* infile = fopen("input.txt", "r");
	char input[LEN] = {0};
	fread(input, 1, LEN, infile);
	fclose(infile);
	Triple data = search((Triple){input, input, input}, -1);
	long ret = 0;
	while (mul) {
		if (data.mul > data.disable) {
			data = search(data, SEARCHEN);
		}
		data.mul += 4;
		if (data->mul == ' ') goto cont;
		char* endptr;
		long a = strtol(mul, &endptr, 10);
		if (*endptr != ',' || endptr == mul) goto cont;
		data.mul = endptr + 1;
		long b = strtol(mul, &endptr, 10);
		if (*endptr != ')' || endptr == mul) goto cont;
		ret += a * b;
cont:
		data = search(data, SEARCHMUL);
	}
	printf("%ld\n", ret);
	return 0;
}
