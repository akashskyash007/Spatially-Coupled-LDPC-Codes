#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define c 4
#define t 10
#define b 88
#define r 349
#define num_rows c * b
#define max_num_columns t * b

int weight(int* selection_vector) {
	int res = 0;
	for (int i = 0; i < t; i++) {
		res += selection_vector[i];
	}
	return res;
}

void generate_D_submatrix() {
	int H_protograph[c][t];
	FILE* fptr;
	fptr = fopen("BASE_MATRIX.txt", "r");
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
	int selection_vector[t];
	for (int i = 0; i < t; i++) {
		selection_vector[i] = 0;
	}
	long int num_permutations = (int)(pow(2, t));
	for (int curr_weight = c; curr_weight <= t; curr_weight++) {
		for (int i = 0; i < t; i++) {
			selection_vector[i] = 0;
		}
		int count = 0;
		for (long int i = 0; i < num_permutations; i++) {
			for (int j = t - 1; j >= 0; j--) {
				long int position_power_2 = pow(2, j);
				if (i >= position_power_2 && i % position_power_2 == 0) {
					selection_vector[t - j - 1] ^= 1;			
				}
			}
			if (weight(selection_vector) == curr_weight) {
				int candidate_D_matrix_protograph[c][curr_weight];
				for (int k = 0; k < c; k++) {
					int curr_column = 0;
					for (int j = 0; j < t; j++) {
						if (selection_vector[j] == 1) {
							candidate_D_matrix_protograph[k][curr_column++] = H_protograph[k][j];
						}
					}
				}
				int num_columns = curr_weight * b;
				static int candidate_D_matrix[num_rows][max_num_columns];
				static int candidate_D_matrix_copy[num_rows][max_num_columns];
				for (int m = 0; m < c; m++) {
					for (int n = 0; n < curr_weight; n++) {
						int current_shift_factor = candidate_D_matrix_protograph[m][n];
						int current_expanded_matrix[b][b];
						if (current_shift_factor == 0) {
							for (int k = 0; k < b; k++) {
								for (int l = 0; l < b; l++) {
									current_expanded_matrix[k][l] = 0;
								}
							}
						}
						else {
							for (int k = 0; k < b; k++) {
								for (int l = 0; l < b; l++) {
									if (l + 1 == current_shift_factor) {
										current_expanded_matrix[k][l] = 1;
									}
									else {
										current_expanded_matrix[k][l] = 0;
									}
								}
								current_shift_factor = (current_shift_factor + 1) % (b + 1);
								if (current_shift_factor == 0) {
									current_shift_factor++;
								}
							}
						}
						int curr_row = m * b;
						int curr_column = n * b;
						for (int k = 0; k < b; k++) {
							for (int l = 0; l < b; l++) {
								candidate_D_matrix[curr_row + k][curr_column + l] = current_expanded_matrix[k][l];
								candidate_D_matrix_copy[curr_row + k][curr_column + l] = current_expanded_matrix[k][l];
							}
						}
					}
				}
				int rref_curr_pivot_row = 0;
				for (int rref_curr_col = 0; rref_curr_col < num_columns; rref_curr_col++) {
					if (candidate_D_matrix[rref_curr_pivot_row][rref_curr_col] == 0) {
						for (int rref_curr_row = rref_curr_pivot_row + 1; rref_curr_row < num_rows; rref_curr_row++) {
							if (candidate_D_matrix[rref_curr_row][rref_curr_col] == 1) {
								for (int rref_col_iterator = 0; rref_col_iterator < num_columns; rref_col_iterator++) {
									candidate_D_matrix[rref_curr_pivot_row][rref_col_iterator] = (candidate_D_matrix[rref_curr_pivot_row][rref_col_iterator] + candidate_D_matrix[rref_curr_row][rref_col_iterator]) % 2;
								}
								break;
							}
						}
					}
					if (candidate_D_matrix[rref_curr_pivot_row][rref_curr_col] == 1) {
						for (int rref_curr_row = 0; rref_curr_row < num_rows; rref_curr_row++) {
							if (rref_curr_row == rref_curr_pivot_row) {
								continue;
							}
							if (candidate_D_matrix[rref_curr_row][rref_curr_col] == 1) {
								for (int rref_col_iterator = 0; rref_col_iterator < num_columns; rref_col_iterator++) {
									candidate_D_matrix[rref_curr_row][rref_col_iterator] = (candidate_D_matrix[rref_curr_row][rref_col_iterator] + candidate_D_matrix[rref_curr_pivot_row][rref_col_iterator]) % 2;
								}
							}
						}
						rref_curr_pivot_row++;
					}
				}
				int rank = 0;
				for (int m = 0; m < num_rows; m++) {
					for (int n = 0; n < num_columns; n++) {
						if (candidate_D_matrix[m][n] == 1) {
							rank++;
							break;
						}
					}
				}
				printf("Current Weight = %d        Current Count = %d             Current Rank = %d\n", curr_weight, count, rank);
				count++;
				if (rank == r) {
					fptr = fopen("D_MATRIX.txt", "w");
					for (int m = 0; m < num_rows; m++) {
						for (int n = 0; n < num_columns; n++) {
							fprintf(fptr, "%d ", candidate_D_matrix_copy[m][n]);
						}
						fprintf(fptr, "\n");
					}
					fclose(fptr);
					fptr = fopen("D_MATRIX_RREF.txt", "w");
					for (int m = 0; m < num_rows; m++) {
						for (int n = 0; n < num_columns; n++) {
							fprintf(fptr, "%d ", candidate_D_matrix[m][n]);
						}
						fprintf(fptr, "\n");
					}
					fclose(fptr);
					system("vim D_MATRIX.txt");
					for (int z = 0; z < t; z++) {
						printf("%d ", selection_vector[z]);
					}
					printf("\n");
					exit(0);
				}
			}
		}
	}
}

int main(void) {
	generate_D_submatrix();
	return 0;
}
