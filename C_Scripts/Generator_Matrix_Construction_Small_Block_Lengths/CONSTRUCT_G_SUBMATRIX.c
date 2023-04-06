#include <stdio.h>
#include <stdlib.h>

#define c 4
#define t 10
#define b 88
#define r 349
#define l 4
#define num_rows_in_D c * b
#define num_columns_in_D l * b
#define num_rows_in_G (t - l) * b
#define num_columns_in_G t * b
#define num_rows_in_H c * b
#define num_columns_in_H t * b
#define num_linearly_dependent_columns num_columns_in_D - r
#define num_elements_in_rhs c * b

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

void perform_gaussian_elimination(int* rhs) {
	static int D[num_rows_in_D][num_columns_in_D];
	FILE* fptr;
	fptr = fopen("D_MATRIX.txt", "r");
	for (int i = 0; i < c * b; i++) {
		for (int j = 0; j < l * b; j++) {
			char ch = fgetc(fptr);
			D[i][j] = ch - 48;
			ch = fgetc(fptr);
		}
		char ch = fgetc(fptr);
	}
	fclose(fptr);
	int rref_curr_pivot_row = 0;
	for (int rref_curr_col = 0; rref_curr_col < num_columns_in_D; rref_curr_col++) {
		if (D[rref_curr_pivot_row][rref_curr_col] == 0) {
			for (int rref_curr_row = rref_curr_pivot_row + 1; rref_curr_row < num_rows_in_D; rref_curr_row++) {
				if (D[rref_curr_row][rref_curr_col] == 1) {
					for (int rref_col_iterator = 0; rref_col_iterator < num_columns_in_D; rref_col_iterator++) {
						D[rref_curr_pivot_row][rref_col_iterator] = (D[rref_curr_pivot_row][rref_col_iterator] + D[rref_curr_row][rref_col_iterator]) % 2;
					}
					rhs[rref_curr_pivot_row] = (rhs[rref_curr_pivot_row] + rhs[rref_curr_row]) % 2;
					break;
				}
			}
		}
		if (D[rref_curr_pivot_row][rref_curr_col] == 1) {
			for (int rref_curr_row = 0; rref_curr_row < num_rows_in_D; rref_curr_row++) {
				if (rref_curr_row == rref_curr_pivot_row) {
					continue;
				}
				if (D[rref_curr_row][rref_curr_col] == 1) {
					for (int rref_col_iterator = 0; rref_col_iterator < num_columns_in_D; rref_col_iterator++) {
						D[rref_curr_row][rref_col_iterator] = (D[rref_curr_row][rref_col_iterator] + D[rref_curr_pivot_row][rref_col_iterator]) % 2;
					}
					rhs[rref_curr_row] = (rhs[rref_curr_row] + rhs[rref_curr_pivot_row]) % 2;
				}
			}
			rref_curr_pivot_row++;
		}
	}
}

void find_G_submatrix(int* linearly_dependent_columns) {
	static int G[num_rows_in_G][num_columns_in_G];
	FILE* fptr;
	fptr = fopen("BASE_MATRIX.txt", "r");
	int H_protograph[c][t];
	for (int i = 0; i < c; i++) {
		for (int j = 0; j < t; j++) {
			int curr_value = 0;
			int flag = 1;
			while (flag) {
				char ch = fgetc(fptr);
				if (ch < 48 || ch > 57) {
					break;
				}
				curr_value = curr_value * 10 + (ch - 48);
			}
			H_protograph[i][j] = curr_value;
		}
		char ch = fgetc(fptr);
	}
	fclose(fptr);
        fptr = fopen("D_MATRIX_RREF.txt", "r");
	static int D_rref[num_rows_in_D][num_columns_in_D];
        for (int i = 0; i < c * b; i++) {
                for (int j = 0; j < l * b; j++) {
                        char ch = fgetc(fptr);
                        D_rref[i][j] = ch - 48;
                        ch = fgetc(fptr);
                }
                char ch = fgetc(fptr);
        }
	fclose(fptr);
	fptr = fopen("G_MATRIX_ROWS.txt", "w");
	for (int i = 0; i < (t - l); i++) {
		static int rhs[num_elements_in_rhs];
		int mi_block[c];
		for (int j = 0; j < c; j++) {
			mi_block[j] = H_protograph[j][i];
		}
		for (int j = 0; j < c; j++) {
			int temp[b];
			int one_position = (b - mi_block[j] + 1) % b;
			for (int k = 0; k < b; k++) {
				if (k == one_position) {
					temp[k] = 1;
				}
				else {
					temp[k] = 0;
				}
			}
			int start_position_in_rhs = j * b;
			for (int k = 0; k < b; k++) {
				rhs[start_position_in_rhs + k] = temp[k];
			}
		}
		perform_gaussian_elimination(rhs);
		int zi[l * b];
		for (int j = 0; j < l * b; j++) {
			if (check_element_prescence_in_array(linearly_dependent_columns, l * b - r, j)) {
				zi[j] = 0;
			}
			else {
				for (int k = 0; k < c * b; k++) {
					if (D_rref[k][j] == 1) {
						zi[j] = rhs[k];
						break;
					}
				}
			}
		}
		for (int j = 0; j < l * b; j++) {
			fprintf(fptr, "%d", zi[j]);
		}
		fprintf(fptr, "\n");
		int gi[t * b];
		for (int j = 0; j < (t - l) * b; j++) {
			gi[j] = 0;
		}
		gi[i * b] = 1;
		int start_pos_gi = (t - l) * b;
		for (int j = 0; j < l * b; j++) {
			gi[start_pos_gi + j] = zi[j];
		}
		int start_row_G_submatrix = b * i;
		for (int curr_row = 0; curr_row < b; curr_row++) {
			for (int j = 0; j < t * b; j++) {
				G[start_row_G_submatrix + curr_row][j] = gi[j];
			}
			for (int iterator = 0; iterator < t; iterator++) {
				int temp = gi[iterator * b + b - 1];
				for (int j = iterator * b + b - 1; j > iterator * b; j--) {
					gi[j] = gi[j - 1];
				}
				gi[iterator * b] = temp;
			}
		}
	}
	fclose(fptr);
	fptr = fopen("G_SUBMATRIX.txt", "w");
	for (int i = 0; i < (t - l) * b; i++) {
		for (int j = 0; j < t * b; j++) {
			fprintf(fptr, "%d ", G[i][j]);
		}
		fprintf(fptr, "\n");
	}
	fclose(fptr);
}

int main(void) {
	static int linearly_dependent_columns[num_linearly_dependent_columns];
	find_linearly_dependent_columns(linearly_dependent_columns);
	find_G_submatrix(linearly_dependent_columns);
	system("vim G_SUBMATRIX.txt");
	return 0;
}
