#include <stdio.h>
#include <stdlib.h>

#define r2 2127
#define c2 3520
#define r1 1
#define c1 2127

void matrix_multiply() {
	static int A[r1][c1];
	static int B[r2][c2];
	static int P[r1][c2];
	FILE* fptr;
	fptr = fopen("information_vector.txt", "r");
	char ch;
	for (int i = 0; i < r1; i++) {
		for (int j = 0; j < c1; j++) {
			A[i][j] = fgetc(fptr) - 48;
		}
	}
	fclose(fptr);
	fptr = fopen("G_MATRIX.txt", "r");
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
	fptr = fopen("code_vector_test.txt", "w");
	for (int i = 0; i < r1; i++) {
		for (int j = 0; j < c2; j++) {
			fprintf(fptr, "%d", P[i][j]);
		}
	}
	fclose(fptr);
}

int main(void) {
	matrix_multiply();
	system("vimdiff code_vector_test.txt code_vector.txt");
	return 0;
}
