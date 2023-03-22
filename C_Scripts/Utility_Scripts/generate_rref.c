#include <stdio.h>
#include <stdlib.h>

#define num_rows 32
#define num_columns 64

void find_rref() {
	static int H[num_rows][num_columns];
	FILE* fptr;
	fptr = fopen("INPUT_MATRIX.txt", "r");
	for (int rref_row_iterator = 0; rref_row_iterator < num_rows; rref_row_iterator++) {
		for (int rref_col_iterator = 0; rref_col_iterator < num_columns; rref_col_iterator++) {
			H[rref_row_iterator][rref_col_iterator] = fgetc(fptr) - 48;
			char ch = fgetc(fptr);
		}
		char ch = fgetc(fptr);
	}
	fclose(fptr);
	int rref_curr_pivot_row = 0;
	for (int rref_curr_col = 0; rref_curr_col < num_columns; rref_curr_col++) {
		if (H[rref_curr_pivot_row][rref_curr_col] == 0) {
			for (int rref_curr_row = rref_curr_pivot_row + 1; rref_curr_row < num_rows; rref_curr_row++) {
				if (H[rref_curr_row][rref_curr_col] == 1) {
					for (int rref_col_iterator = 0; rref_col_iterator < num_columns; rref_col_iterator++) {
						H[rref_curr_pivot_row][rref_col_iterator] = (H[rref_curr_pivot_row][rref_col_iterator] + H[rref_curr_row][rref_col_iterator]) % 2;
					}
					break;
				}
			}
		}
		if (H[rref_curr_pivot_row][rref_curr_col] == 1) {
			for (int rref_curr_row = 0; rref_curr_row < num_rows; rref_curr_row++) {
				if (rref_curr_row == rref_curr_pivot_row) {
					continue;
				}
				if (H[rref_curr_row][rref_curr_col] == 1) {
					for (int rref_col_iterator = 0; rref_col_iterator < num_columns; rref_col_iterator++) {
						H[rref_curr_row][rref_col_iterator] = (H[rref_curr_row][rref_col_iterator] + H[rref_curr_pivot_row][rref_col_iterator]) % 2;
					}
				}
			}
			rref_curr_pivot_row++;
		}
	}
	fptr = fopen("ROW_REDUCED_MATRIX.txt", "w");
	for (int rref_row_iterator = 0; rref_row_iterator < num_rows; rref_row_iterator++) {
		for (int rref_col_iterator = 0; rref_col_iterator < num_columns; rref_col_iterator++) {
			fprintf(fptr, "%d ", H[rref_row_iterator][rref_col_iterator]);
		}
		fprintf(fptr, "\n");
	}
	fclose(fptr);

}

int main(void) {
	find_rref();
	system("vim ROW_REDUCED_MATRIX.txt");
	return 0;
}
