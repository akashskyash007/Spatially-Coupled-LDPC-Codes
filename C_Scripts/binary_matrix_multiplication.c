#include <stdio.h>
#include <stdlib.h>

void matrix_multiply(int r1, int c1, int r2, int c2) {
	int A[r1][c1];
	int B[r2][c2];
	int P[r1][c2];
	FILE* fptr;
	fptr = fopen("QC_LDPC_G_Matrix_Full.txt", "r");
	char ch;
	for (int i = 0; i < r1; i++) {
		for (int j = 0; j < c1; j++) {
			A[i][j] = fgetc(fptr) - 48;
			ch = fgetc(fptr);
		}
		ch = fgetc(fptr);
	}
	fclose(fptr);
	fptr = fopen("QC_LDPC_H_Matrix_Full_Transpose.txt", "r");
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
	for (int i = 0; i < r1; i++) {
		for (int j = 0; j < c2; j++) {
			printf("%d ", P[i][j]);
		}
		printf("\n");
	}
}

int main(void) {
	int r1 = 33;
	int c1 = 64;
	int r2 = 64;
	int c2 = 32;
	matrix_multiply(r1, c1, r2, c2);
	return 0;
}
