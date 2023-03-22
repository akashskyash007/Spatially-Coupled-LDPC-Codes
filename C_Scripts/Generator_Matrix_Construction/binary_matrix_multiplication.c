#include <stdio.h>
#include <stdlib.h>

#define c 16
#define t 40
#define b 88
#define r 1393
#define l 16
#define r1 t * b - r
#define c1 t * b
#define r2 t * b
#define c2 c * b

void matrix_multiply() {
	static int A[r1][c1];
	static int B[r2][c2];
	static int P[r1][c2];
	FILE* fptr;
	fptr = fopen("G_MATRIX.txt", "r");
	char ch;
	for (int i = 0; i < r1; i++) {
		for (int j = 0; j < c1; j++) {
			A[i][j] = fgetc(fptr) - 48;
			ch = fgetc(fptr);
		}
		ch = fgetc(fptr);
	}
	fclose(fptr);
	fptr = fopen("H_MATRIX_TRANSPOSE.txt", "r");
	for (int i = 0; i < r2; i++) {
		for (int j = 0; j < c2; j++) {
			B[i][j] = fgetc(fptr) - 48;
			ch = fgetc(fptr);
		}
		ch = fgetc(fptr);
	}
	fclose(fptr);
	for (int i = 0; i < r1; i++) {
		for (int j = 0; j < c2; j++) {
			P[i][j] = 0;
		}
	}
	for (int i = 0; i < r1; i++) {
		for (int j = 0; j < c2; j++) {
			for (int k = 0; k < r2; k++) {
				P[i][j] = (P[i][j] + A[i][k] * B[k][j]) % 2;
			}
		}
	}
	fptr = fopen("G_MATRIX_TEST_RESULTS.txt", "w");
	for (int i = 0; i < r1; i++) {
		for (int j = 0; j < c2; j++) {
			fprintf(fptr, "%d ", P[i][j]);
		}
		fprintf(fptr, "\n");
	}
	fclose(fptr);
}

int main(void) {
	matrix_multiply();
	system("vim G_MATRIX_TEST_RESULTS.txt");
	return 0;
}
