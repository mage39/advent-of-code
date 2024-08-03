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

house* rehashExpand (house* addrs, int* arrLen) {
	*arrLen *= 2;
	size_t size = sizeof(house) * *arrLen;
	house* new = malloc(size);
	if (!new) {
		printf("WTF\n");
		exit(1);
	}
	memset(new, 0, size);
	for (int i = 0; i < *arrLen / 2; i++) {
		if (!addrs[i].count) continue;
		int j = hashf(addrs[i]) % *arrLen;
		for (int k = 0; k < *arrLen / 4; k++) {
			int offset = j + k;
			if (offset >= *arrLen) offset -= *arrLen;
			if (!new[offset].count) {
				memcpy(new + offset, addrs + i, sizeof(house));
				break;
			}
		}
	}
	free(addrs);
	return new;
}

int placeHash (house* addrs, house* currentPos, int arrLen) {
	int i = hashf(*currentPos) % arrLen;
	for (int j = 0; j < arrLen / 4; j++) {
		int offset = i + j;
		if (offset >= arrLen) offset -= arrLen;
		if (addrs[offset].count) {
			if (!memcmp(addrs[offset].addr, currentPos->addr, sizeof(int) * 2)) {
				addrs[offset].count++;
				return 0;
			}
		} else {
			memcpy(addrs + offset, currentPos, sizeof(house));
			addrs[offset].count = 1;
			currentPos->count++;
			return 0;
		}
	}
	return 1;
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
	if (!addrs) {
		printf("WTF\n");
		exit(1);
	}
	memset(addrs, 0, sizeof(house) * arrLen);
	house currentPos = {0};
	placeHash(addrs, &currentPos, arrLen);
	while (letter != EOF) {
		if (letter == '^') currentPos.addr[0]++;
		if (letter == '>') currentPos.addr[1]++;
		if (letter == 'v') currentPos.addr[0]--;
		if (letter == '<') currentPos.addr[1]--;
		int err = placeHash(addrs, &currentPos, arrLen);
		if (err) {
			addrs = rehashExpand(addrs, &arrLen);
			err = placeHash(addrs, &currentPos, arrLen);
			if (err) {
				printf("WTF\n");
				exit(2);
			}
		}
		letter = getc(input);
	}
	free(addrs);
	printf("%d\n", currentPos.count);
	return 0;
}
