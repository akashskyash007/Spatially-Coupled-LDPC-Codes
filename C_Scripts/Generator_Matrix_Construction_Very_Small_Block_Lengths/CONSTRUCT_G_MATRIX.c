#include <stdio.h>
#include <stdlib.h>

#define c 2
#define t 5
#define b 88
#define l 2
#define r 175
#define num_rows_in_G_sub (t - l) * b
#define num_columns_in_G_sub t * b
#define num_rows_in_Q l * b - r
#define num_columns_in_Q t * b
#define num_rows_in_G t * b - r
#define num_columns_in_G t * b

void generate_G_matrix() {
	FILE* fptr;
	fptr = fopen("G_SUBMATRIX.txt", "r");
	static int G_SUB[num_rows_in_G_sub][num_columns_in_G_sub];
	for (int i = 0; i < num_rows_in_G_sub; i++) {
		for (int j = 0; j < num_columns_in_G_sub; j++) {
			char ch = fgetc(fptr);
			G_SUB[i][j] = ch - 48;
			ch = fgetc(fptr);
		}
		char ch = fgetc(fptr);
	}
	fclose(fptr);
	fptr = fopen("Q_SUBMATRIX.txt", "r");
	static int Q[num_rows_in_Q][num_columns_in_Q];
	for (int i = 0; i < num_rows_in_Q; i++) {
		for (int j = 0; j < num_columns_in_Q; j++) {
			char ch = fgetc(fptr);
			Q[i][j] = ch - 48;
			ch = fgetc(fptr);
		}
		char ch = fgetc(fptr);
	}
	fclose(fptr);
	static int G[num_rows_in_G][num_columns_in_G];
	for (int i = 0; i < num_rows_in_G_sub; i++) {
		for (int j = 0; j < num_columns_in_G_sub; j++) {
			G[i][j] = G_SUB[i][j];
		}
	}
	for (int i = num_rows_in_G_sub; i < num_rows_in_G; i++) {
		for (int j = 0; j < num_columns_in_G; j++) {
			G[i][j] = Q[i - num_rows_in_G_sub][j];
		}
	}
	fptr = fopen("G_MATRIX.txt", "w");
	for (int i = 0; i < num_rows_in_G; i++) {
		for (int j = 0; j < num_columns_in_G; j++) {
			fprintf(fptr, "%d ", G[i][j]);
		}
		fprintf(fptr, "\n");
	}
	fclose(fptr);
}

int main(void) {
	generate_G_matrix();
	system("vim G_MATRIX.txt");
	return 0;
}
