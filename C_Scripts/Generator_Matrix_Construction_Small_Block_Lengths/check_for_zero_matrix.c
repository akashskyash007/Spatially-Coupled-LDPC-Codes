#include <stdio.h>
#include <stdlib.h>

#define c 4
#define t 10
#define b 88
#define l 4
#define r 349
#define num_rows t * b - r
#define num_columns c * b

void check() {
	static int matrix[num_rows][num_columns];
	FILE* fptr;
	fptr = fopen("G_MATRIX_TEST_RESULTS.txt", "r");
	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < num_columns; j++) {
			char ch = fgetc(fptr);
			matrix[i][j] = ch - 48;
			ch = fgetc(fptr);
		}
		char ch = fgetc(fptr);
	}
	int num_errors = 0;
	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < num_columns; j++) {
			num_errors += matrix[i][j];
		}
	}
	printf("Number of Non - Zero Values = %d\n", num_errors);
}

int main(void) {
	check();
	return 0;
}
