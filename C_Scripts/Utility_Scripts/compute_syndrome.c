#include <stdio.h>
#include <stdlib.h>

#define c 16
#define t 40
#define b 88
#define num_rows t * b
#define num_columns c * b

void compute_syndrome() {
	FILE* fptr;
	fptr = fopen("H_MATRIX_TRANSPOSE.txt", "r");
	static int H_T[num_rows][num_columns];
	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < num_columns; j++) {
			H_T[i][j] = fgetc(fptr) - 48;
			char ch = fgetc(fptr);
		}
		char ch = fgetc(fptr);
	}
	fclose(fptr);
	fptr = fopen("code_vector.txt", "r");
	static int code_vector[num_rows];
	for (int i = 0; i < num_rows; i++) {
		code_vector[i] = fgetc(fptr) - 48;
	}
	static int syndrome[num_columns];
	for (int i = 0; i < num_columns; i++) {
		syndrome[i] = 0;
	}
	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < num_columns; j++) {
			syndrome[j] = (syndrome[j] + code_vector[i] * H_T[i][j]) % 2;
		}
	}
	fptr = fopen("syndrome.txt", "w");
	for (int i = 0; i < num_columns; i++) {
		fprintf(fptr, "%d", syndrome[i]);
	}
	fclose(fptr);
}

int main(void) {
	compute_syndrome();
	system("vim syndrome.txt");
	return 0;
}
