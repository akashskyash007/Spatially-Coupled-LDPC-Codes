#include <stdio.h>
#include <stdlib.h>

#define num_rows_in_protograph 2
#define num_columns_in_protograph 5
#define expansion_factor 88
#define num_rows num_rows_in_protograph * expansion_factor
#define num_columns num_columns_in_protograph * expansion_factor

void construct_parity_check_matrix() {
	int H_protograph[num_rows_in_protograph][num_columns_in_protograph];
	FILE* fptr;
	fptr = fopen("BASE_MATRIX.txt", "r");
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
		char ch = fgetc(fptr);
	}
	printf("%d\n", H_protograph[4][7]);
	static int H[num_rows][num_columns];
	for (int i = 0; i < num_rows_in_protograph; i++) {
		for (int j = 0; j < num_columns_in_protograph; j++) {
			int current_shift_factor = H_protograph[i][j];
			int current_expanded_matrix[expansion_factor][expansion_factor];
			if (current_shift_factor == 0) {
				for (int k = 0; k < expansion_factor; k++) {
					for (int l = 0; l < expansion_factor; l++) {
						current_expanded_matrix[k][l] = 0;
					}
				}
			}
			else {
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
	fptr = fopen("H_MATRIX.txt", "w");
	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < num_columns; j++) {
			fprintf(fptr, "%d ", H[i][j]);
		}
		fprintf(fptr, "\n");
	}
	fclose(fptr);
}

int main(void) {
	construct_parity_check_matrix();
	system("vim H_MATRIX.txt");
	return 0;
}
