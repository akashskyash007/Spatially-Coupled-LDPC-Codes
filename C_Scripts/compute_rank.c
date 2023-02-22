#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int num_rows = 32;
	int num_columns = 32;
	FILE* fptr;
	fptr = fopen("D_Matrix_Row_Reduced_Form.txt", "r");
	int matrix[num_rows][num_columns];
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
