#include <stdint.h>
#include <stdio.h>

uint32_t leftrotate (uint32_t a, uint32_t b) {
	return (a << b) | (a >> 32 - b);
}

int main () {
	int a = 2, b = 1;
	printf("%d, %d, leftrotate %d\n", a, b, leftrotate(a, b));
}
