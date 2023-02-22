#include <stdio.h>
#include <stdlib.h>

void find_transpose(int r, int c) {
	int H_T[c][r];
	int H[r][c];
	FILE* fptr;
	fptr = fopen("QC_LDPC_H_Matrix_Full.txt", "r");
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
	fptr = fopen("QC_LDPC_H_Matrix_Full_Transpose.txt", "w");
	for (int i = 0; i < c; i++) {
		for (int j = 0; j < r; j++) {
			fprintf(fptr, "%d ", H_T[i][j]);
		}
		fprintf(fptr, "\n");
	}
	fclose(fptr);
}

int main(void) {
	int r = 32;
	int c = 64;
	find_transpose(r, c);
	system("vim QC_LDPC_H_Matrix_Full_Transpose.txt");
	return 0;
}
