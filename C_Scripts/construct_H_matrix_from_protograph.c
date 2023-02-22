#include <stdio.h>
#include <stdlib.h>

void construct_parity_check_matrix(int num_rows_in_protograph, int num_columns_in_protograph, int expansion_factor) {
	int H_protograph[num_rows_in_protograph][num_columns_in_protograph];
	FILE* fptr;
	fptr = fopen("QC_LDPC_Protograph.txt", "r");
	for (int i = 0; i < num_rows_in_protograph; i++) {
		for (int j = 0; j < num_columns_in_protograph; j++) {
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
	}
	int num_rows = num_rows_in_protograph * expansion_factor;
	int num_columns = num_columns_in_protograph * expansion_factor;
	int H[num_rows][num_columns];
	for (int i = 0; i < num_rows_in_protograph; i++) {
		for (int j = 0; j < num_columns_in_protograph; j++) {
			int current_shift_factor = H_protograph[i][j];
			int current_expanded_matrix[expansion_factor][expansion_factor];
			for (int k = 0; k < expansion_factor; k++) {
				for (int l = 0; l < expansion_factor; l++) {
					if (l + 1 == current_shift_factor) {
						current_expanded_matrix[k][l] = 1;
					}
					else {
						current_expanded_matrix[k][l] = 0;
					}
				}
				current_shift_factor = (current_shift_factor + 1) % (expansion_factor + 1);
				if (current_shift_factor == 0) {
					current_shift_factor++;
				}
			}
			int curr_row = i * expansion_factor;
			int curr_column = j * expansion_factor;
			for (int k = 0; k < expansion_factor; k++) {
				for (int l = 0; l < expansion_factor; l++) {
					H[curr_row + k][curr_column + l] = current_expanded_matrix[k][l];
				}
			}
		}
	}
	fclose(fptr);
	fptr = fopen("QC_LDPC_H_Matrix_Full.txt", "w");
	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < num_columns; j++) {
			fprintf(fptr, "%d ", H[i][j]);
		}
		fprintf(fptr, "\n");
	}
	fclose(fptr);
}

int main(void) {
	int num_rows_in_protograph = 2;
	int num_columns_in_protograph = 4;
	int expansion_factor = 16;
	construct_parity_check_matrix(num_rows_in_protograph, num_columns_in_protograph, expansion_factor);
	system("vim QC_LDPC_H_Matrix_Full.txt");
	return 0;
}
