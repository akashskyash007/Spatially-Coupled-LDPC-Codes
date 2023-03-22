#include <stdio.h>
#include <stdlib.h>

#define s 16
#define t 40
#define b 88
#define r s * b
#define c t * b

void find_transpose() {
	static int H_T[c][r];
	static int H[r][c];
	FILE* fptr;
	fptr = fopen("H_MATRIX.txt", "r");
	char ch;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			H[i][j] = fgetc(fptr) - 48;
			ch = fgetc(fptr);
		}
		ch = fgetc(fptr);
	}
	fclose(fptr);
	for (int i = 0; i < c; i++) {
		for(int j = 0; j < r; j++) {
			H_T[i][j] = H[j][i];
		}
	}
	fptr = fopen("H_MATRIX_TRANSPOSE.txt", "w");
	for (int i = 0; i < c; i++) {
		for (int j = 0; j < r; j++) {
			fprintf(fptr, "%d ", H_T[i][j]);
		}
		fprintf(fptr, "\n");
	}
	fclose(fptr);
}

int main(void) {
	find_transpose();
	system("vim H_MATRIX_TRANSPOSE.txt");
	return 0;
}
