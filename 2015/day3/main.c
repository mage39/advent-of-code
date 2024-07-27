#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int count;
	int addr[2];
} house;

uint64_t hashf (house data) {
	uint64_t hash = 0xcbf29ce484222325;
	for (int i = sizeof(int); i < sizeof(house); i++) {
		hash ^= *((char*)&data + i);
		hash *= 0x100000001b3;
	}
	return hash;
}

void rehashExpand (house* addrs, int* arrLen) { // aborts. i now suspect the infinite loop i undoubtedly created with my fancy gotos
	size_t size = sizeof(house) * *arrLen;
	house* temp = malloc(size);
	memcpy(temp, addrs, size);
	*arrLen *= 2;
	size *= 2;
	addrs = realloc(addrs, size);
	memset(addrs, 0, size);
	for (int i = 0; i < *arrLen; i++) {
		if (!temp[i].count) continue;
		int j = hashf(temp[i]) % *arrLen;
		for (int k = 0; k < *arrLen / 2; k++) {
			int offset = j + k;
			if (offset >= *arrLen) offset -= *arrLen;
			if (!addrs[offset].count) {
				memcpy(addrs + offset, temp + i, sizeof(house));
				break;
			}
		}
	}
	free(temp);
}

int main () {
	FILE* input = fopen("day3/input", "r");
	if (!input) {
		printf("WTF\n");
		exit(-1);
	}

	int arrLen = 32;
	int letter = getc(input);
	house* addrs = malloc(sizeof(house) * arrLen);
	memset(addrs, 0, sizeof(house) * arrLen);
	house currentPos = {.count = 1};
	while (letter != EOF) {
		if (letter == '^') currentPos.addr[0]++;
		if (letter == '>') currentPos.addr[1]++;
		if (letter == 'v') currentPos.addr[0]--;
		if (letter == '<') currentPos.addr[1]--;
		failure:
		int i = hashf(currentPos) % arrLen;
		for (int j = 0; j < arrLen / 4; j++) {
			int offset = i + j;
			if (offset >= arrLen) offset -= arrLen;
			if (addrs[offset].count) {
				if (addrs[offset].addr[0] == currentPos.addr[0] && addrs[offset].addr[1] == currentPos.addr[1]) {
					addrs[offset].count++;
					goto success;
				}
			} else {
				memcpy(addrs + offset, &currentPos, sizeof(house));
				addrs[offset].count = 1;
				currentPos.count++;
				goto success;
			}
		}
		// im just trying to get python's for..else here, ISTG im not doing gratuitous gotos
		rehashExpand(addrs, &arrLen);
		goto failure;
		success:
		letter = getc(input);
	}

	printf("%d\n", currentPos.count);
	return 0;
}
