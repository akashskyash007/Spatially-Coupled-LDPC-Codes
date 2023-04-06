#include <stdio.h>
#include <stdlib.h>

#define c 2
#define t 5
#define b 88
#define r 175
#define l 2
#define num_rows_in_D c * b
#define num_columns_in_D l * b
#define num_rows_in_Q l * b - r
#define num_columns_in_Q t * b
#define num_linearly_dependent_columns l * b - r

int check_element_prescence_in_array(int* arr, int n, int ele) {
	int res = 0;
	for (int i = 0; i < n; i++) {
		if (arr[i] == ele) {
			res = 1;
		}
	}
	return res;
}

void find_linearly_dependent_columns(int* linearly_dependent_columns) {
	static int D_row_reduced[num_rows_in_D][num_columns_in_D];
	FILE* fptr;
	fptr = fopen("D_MATRIX_RREF.txt", "r");
	char ch;
	for (int i = 0; i < c * b; i++) {
		for (int j = 0; j < l * b; j++) {
			D_row_reduced[i][j] = fgetc(fptr) - 48;
			ch = fgetc(fptr);
		}
		ch = fgetc(fptr);
	}
	int count = 0;
	static int pivot_columns[r];
	for (int i = 0; i < c * b; i++) {
		for (int j = 0; j < l * b; j++) {
			if (D_row_reduced[i][j] == 1) {
				pivot_columns[count++] = j;
				break;
			}
		}
	}
	fclose(fptr);
	count = 0;
	for (int i = 0; i < l * b; i++) {
		if (!check_element_prescence_in_array(pivot_columns, r, i)) {
			linearly_dependent_columns[count++] = i;
		}
	}
}

void construct_Q_submatrix(int* linearly_dependent_columns) {
	static int Q[num_rows_in_Q][num_columns_in_Q];
	FILE* fptr;
	fptr = fopen("D_MATRIX_RREF.txt", "r");
	static int D_RREF[num_rows_in_D][num_columns_in_D];
	for (int i = 0; i < num_rows_in_D; i++) {
		for (int j = 0; j < num_columns_in_D; j++) {
			char ch = fgetc(fptr);
			D_RREF[i][j] = ch - 48;
			ch = fgetc(fptr);
		}
		char ch = fgetc(fptr);
	}
	fclose(fptr);
	int current_row_in_Q = 0;
	fptr = fopen("G_MATRIX_ROWS.txt", "a");
	for (int i = 0; i < l; i++) {
		int curr_col_index = i * b;
		int current_Q_block_num_rows = 0;
		for (int j = curr_col_index; j < curr_col_index + b; j++) {
			if (check_element_prescence_in_array(linearly_dependent_columns, num_linearly_dependent_columns, j)) {
				current_Q_block_num_rows++;
			}
		}
		if (current_Q_block_num_rows > 0) {
			int selected_column;
			for (int j = curr_col_index; j < curr_col_index + b; j++) {
				if (check_element_prescence_in_array(linearly_dependent_columns, num_linearly_dependent_columns, j)) {
					selected_column = j;
					break;
				}
			}
			int zi[l * b];
			for (int j = 0; j < l * b; j++) {
				if (check_element_prescence_in_array(linearly_dependent_columns, num_linearly_dependent_columns, j)) {
					if (j == selected_column) {
						zi[j] = 1;
					}
					else {
						zi[j] = 0;
					}
				}
				else {
					for (int k = 0; k < c * b; k++) {
						if (D_RREF[k][j] == 1) {
							zi[j] = D_RREF[k][selected_column];
							break;
						}
					}
				}
			}
			for (int j = 0; j < l * b; j++) {
				fprintf(fptr, "%d", zi[j]);
			}
			fprintf(fptr, "\n");
			int qi[t * b];
			for (int j = 0; j < t * b; j++) {
				if (j < (t - l) * b) {
					qi[j] = 0;
				}
				else {
					qi[j] = zi[j - (t - l) * b];
				}
			}
			for (int j = 0; j < current_Q_block_num_rows; j++) {
				for (int k = 0; k < t * b; k++) {
					Q[current_row_in_Q][k] = qi[k];
				}
				for (int iterator = 0; iterator < t; iterator++) {
					int temp = qi[iterator * b + b - 1];
					for (int m = iterator * b + b - 1; m > iterator * b; m--) {
						qi[m] = qi[m - 1];
					}
					qi[iterator * b] = temp;
				}
				current_row_in_Q++;
			}
		}
	}
	fclose(fptr);
	fptr = fopen("Q_SUBMATRIX.txt", "w");
	for (int i = 0; i < num_rows_in_Q; i++) {
		for (int j = 0; j < num_columns_in_Q; j++) {
			fprintf(fptr, "%d ", Q[i][j]);
		}
		fprintf(fptr, "\n");
	}
	fclose(fptr);
}

int main(void) {
	static int linearly_dependent_columns[num_linearly_dependent_columns];
	find_linearly_dependent_columns(linearly_dependent_columns);
	construct_Q_submatrix(linearly_dependent_columns);
	system("vim Q_SUBMATRIX.txt");
	return 0;
}
