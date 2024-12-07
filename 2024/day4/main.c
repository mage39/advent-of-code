#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define LEN 140

typedef struct {
	char mat[3][3];
} Mat;

typedef struct {
	int i;
	int j;
} Pos;

enum {
	NOTOP = 1,
	NOBOT = 1 << 1,
	NOLEFT = 1 << 2,
	NORIGHT = 1 << 3
};

static int boundsCheck (int i, int j) {
	if (i < 0 || i > 139) return 0;
	if (j < 0 || j > 139) return 0;
	return 1;
}

static Mat searchM (char input[LEN][LEN], Pos pos, unsigned boundFlags) {
	Mat m = {0};
	int i = 0, j = 0, iStop = 3, jStop = 3;
	if (boundFlags & NOTOP) i = 1;
	if (boundFlags & NOLEFT) j = 1;
	if (boundFlags & NOBOT) iStop = 2;
	if (boundFlags & NORIGHT) jStop = 2;
	for (; i < iStop; i++) {
		for (; j < jStop; j++) {
			int iOff = pos.i + (i - 1);
			int jOff = pos.j + (j - 1);
			if (input[iOff][jOff] == 'M') m.mat[i][j] = 1;
		}
	}
	return m;
}

static Mat search (char input[LEN][LEN], Pos pos, Mat mat, char find, int scalar) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (!mat.mat[i][j]) continue;
			int iOff = pos.i + (i - 1) * scalar;
			int jOff = pos.j + (j - 1) * scalar;
			if (!boundsCheck(iOff, jOff)) exit(1);
			// above never runs, but it makes -fanalyzer shut up
			if (input[iOff][jOff] == find);
			else mat.mat[i][j] = 0;
		}
	}
	return mat;
}

int main (void) {
	FILE* infile = fopen("input.txt", "r");
	if (!infile) return 1;
	char input[LEN][LEN];
	for (int i = 0; i < LEN; i++) {
		fread(input[i], 1, LEN, infile);
		fseek(infile, 1, SEEK_CUR);
	}
	fclose(infile);
	int ret = 0;
	for (int i = 0; i < LEN; i++) {
		for (int j = 0; j < LEN; j++) {
			if (input[i][j] != 'X') continue;
			unsigned boundFlags = 0;
			if (i < 3) boundFlags |= NOTOP;
			if (j < 3) boundFlags |= NOLEFT;
			if (i > 136) boundFlags |= NOBOT;
			if (j > 136) boundFlags |= NORIGHT;
			Pos p = {i, j};
			Mat m = searchM(input, p, boundFlags);
			m = search(input, p, m, 'A', 2);
			m = search(input, p, m, 'S', 3);
			for (int k = 0; k < (int)sizeof(m); k++) if (((char*)&m)[k]) ret++;
		}
	}
	printf("%d\n", ret);
	return 0;
}
