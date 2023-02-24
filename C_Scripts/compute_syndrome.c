#include <stdio.h>
#include <stdlib.h>

void compute_syndrome(int num_rows, int num_columns, int* code_word) {
	int H_T[num_rows][num_columns];
	FILE* fptr;
	char ch;
	fptr = fopen("QC_LDPC_H_Matrix_Full_Transpose.txt", "r");
	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < num_columns; j++) {
			H_T[i][j] = fgetc(fptr) - 48;
			ch = fgetc(fptr);
		}
		ch = fgetc(fptr);
	}
	fclose(fptr);
	int syndrome[num_columns];
	for (int i = 0; i < num_columns; i++) {
		syndrome[i] = 0;
	}
	for (int i = 0; i < num_rows; i++) {
		if (code_word[i] == 0) {
			continue;
		}
		else {
			for (int j = 0; j < num_columns; j++) {
				syndrome[j] = (syndrome[j] + H_T[i][j]) % 2;
			}
		}
	}
	for (int i = 0; i < num_columns; i++) {
		printf("%d ", syndrome[i]);
	}
	printf("\n");
}

int main(void) {
	int num_rows = 64;
	int num_columns = 32;
	int code_word[] = {1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0};
	compute_syndrome(num_rows, num_columns, code_word);
	return 0;
}
