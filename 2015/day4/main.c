#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define F(b, c, d) (b & c | ~b & d)
#define G(b, c, d) (b & d | c & ~d)
#define H(b, c, d) (b ^ c ^ d)
#define I(b, c, d) (c ^ (b | ~d))

typedef struct {
	char data[16];
} hash_t;

static hash_t MD5 (char messgdata[], size_t length) {
#define LEN 64
	int s[LEN], K[LEN];
	for (int i = 0; i < 16; i += 4) {
		int init[] = {7, 12, 17, 22};
		memcpy(s + i, init, sizeof(init));
	}
	for (int i = 16; i < 32; i += 4) {
		int init[] = {5, 9, 14, 20};
		memcpy(s + i, init, sizeof(init));
	}
	for (int i = 32; i < 48; i += 4) {
		int init[] = {4, 11, 16, 23};
		memcpy(s + i, init, sizeof(init));
	}
	for (int i = 48; i < 64; i += 4) {
		int init[] = {6, 10, 15, 21};
		memcpy(s + i, init, sizeof(init));
	}
	for (int i = 0; i < LEN;) {
		double t = abs(sin(++i));
		K[i] = floor(pow(2, 32) * t);
	}
	int hash[4] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476};
	char* message = malloc(length);
	strncpy(message, messgdata, length);
	size_t newLen = length + 9; // required minumum padding
	{
		int t;
		if (t = length % 64) {
			newLen += 64 - t;
		}
	} 
	realloc(message, newLen);
	message[length] = 0x80;
	{
		int idx = length + 1;
		memcpy(message + idx, 0, newLen - idx);
	}
	*(uint64_t*)(message + newLen - sizeof(uint64_t)) = length * 8; // allat for a negative one index. python would be proud
	// now for the real stuff
	for (int i = 0; i < newLen; i += LEN) {
		int M[16];
		memcpy(M, message + i, sizeof(M));
		int temp[4];
		memcpy(temp, hash, sizeof(hash));
		for (int j = 0; j < LEN; j++) {
			int F, g;
			if (j < 16) {
				F = F(temp[1], temp[2], temp[3]);
				g = i;
			} else if (j < 32) {
				F = G(temp[1], temp[2], temp[3]);
				g = (5 * i + 1) % 16;
			} else if (j < 48) {
				F = H(temp[1], temp[2], temp[3]);
				g = (5 * i + 5) % 16;
			} else {
				F = I(temp[1], temp[2], temp[3]);
				g = (7 * i) % 16;
			}
			F += temp[0] + K[i] + M[g];
			temp[0] = temp[3];
			temp[3] = temp[2];
			temp[2] = temp[1];
			temp[1] += (F << s[i]) | (F >> 32 - s[i]);
		}
		for (int j = 0; j < 4; j++) hash[j] += temp[j];
	}
	free(message);
	hash_t ret;
	memcpy(ret.data, hash, sizeof(hash));
	return ret;
#undef LEN
}

int main () {
	return 0;
}
