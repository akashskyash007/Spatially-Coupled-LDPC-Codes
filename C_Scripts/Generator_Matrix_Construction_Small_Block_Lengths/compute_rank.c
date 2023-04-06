#include <stdio.h>
#include <stdlib.h>

#define J 4
#define K 10
#define EXPANSION_FACTOR 88
#define num_rows J * EXPANSION_FACTOR
#define num_columns K * EXPANSION_FACTOR

int main(void) {
	FILE* fptr;
	fptr = fopen("H_MATRIX_RREF.txt", "r");
	static int matrix[num_rows][num_columns];
	char ch;
	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < num_columns; j++) {
			matrix[i][j] = fgetc(fptr) - 48;
			ch = fgetc(fptr);
		}
		ch = fgetc(fptr);
	}
	int rank = 0;
	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < num_columns; j++) {
			if (matrix[i][j] == 1) {
				rank++;
				break;
			}
		}
	}
	printf("Rank = %d\n", rank);
	return 0;
}
