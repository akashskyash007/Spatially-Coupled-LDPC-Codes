#include <stdio.h>
#include <stdlib.h>

int check_element_prescence_in_array(int* arr, int n, int ele) {
	int res = 0;
	for (int i = 0; i < n; i++) {
		if (arr[i] == ele) {
			res = 1;
		}
	}
	return res;
}

void find_linearly_dependent_columns(int* linearly_dependent_columns, int c, int l, int b, int r) {
	int D_row_reduced[c*b][l*b];
	FILE* fptr;
	fptr = fopen("D_Matrix_Row_Reduced_Form.txt", "r");
	char ch;
	for (int i = 0; i < c * b; i++) {
		for (int j = 0; j < l * b; j++) {
			D_row_reduced[i][j] = fgetc(fptr) - 48;
			ch = fgetc(fptr);
		}
		ch = fgetc(fptr);
	}
	int count = 0;
	int pivot_columns[r];
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

void perform_gaussian_elimination(int c, int t, int b, int l, int* rhs) {
	int D[c*b][l*b];
	FILE* fptr;
	fptr = fopen("D_Matrix.txt", "r");
	for (int i = 0; i < c * b; i++) {
		for (int j = 0; j < l * b; j++) {
			char ch = fgetc(fptr);
			D[i][j] = ch - 48;
			ch = fgetc(fptr);
		}
		char ch = fgetc(fptr);
	}
	fclose(fptr);
	for (int curr_row = 0; curr_row < c * b; curr_row++) {
		if (D[curr_row][curr_row] != 1) {
			for (int row = curr_row + 1; row < c * b; row++) {
				if (D[row][curr_row] == 1) {
					for (int i = 0; i < l * b; i++) {
						D[curr_row][i] = (D[curr_row][i] + D[row][i]) % 2; 
					}
					rhs[curr_row] = (rhs[curr_row] + rhs[row]) % 2;
					break;
				}
			}
		}
		for (int i = 0; i < c * b; i++) {
			if (i == curr_row) {
				continue;
			}
			if (D[i][curr_row] == 1) {
				for (int j = 0; j < l * b; j++) {
					D[i][j] = (D[i][j] + D[curr_row][j]) % 2;
				}
				rhs[i] = (rhs[i] + rhs[curr_row]) % 2;
			}
		}
	}
}

void find_G_submatrix(int* linearly_dependent_columns, int c, int l, int b, int t, int r) {
	int G[(t - l) * b][t * b];
	FILE* fptr;
	fptr = fopen("QC_LDPC_Protograph.txt", "r");
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
	}
	fclose(fptr);
        fptr = fopen("D_Matrix_Row_Reduced_Form.txt", "r");
	int D_rref[c * b][l * b];
        for (int i = 0; i < c * b; i++) {
                for (int j = 0; j < l * b; j++) {
                        char ch = fgetc(fptr);
                        D_rref[i][j] = ch - 48;
                        ch = fgetc(fptr);
                }
                char ch = fgetc(fptr);
        }
	fclose(fptr);
	for (int i = 0; i < (t - l); i++) {
		int rhs[c * b];
		int mi_block[c];
		for (int j = 0; j < c; j++) {
			mi_block[j] = H_protograph[j][i];
		}
		for (int j = 0; j < c; j++) {
			int temp[b];
			int one_position = b - mi_block[j] + 1;
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
		perform_gaussian_elimination(c, t, b, l, rhs);
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
	fptr = fopen("QC_LDPC_G_Submatrix_Full.txt", "w");
	for (int i = 0; i < (t - l) * b; i++) {
		for (int j = 0; j < t * b; j++) {
			fprintf(fptr, "%d ", G[i][j]);
		}
		fprintf(fptr, "\n");
	}
	fclose(fptr);
}

int main(void) {
	int c = 2;
	int l = 2;
	int t = 4;
	int r = 31;
	int b = 16;
	int linearly_dependent_columns[l*b - r];
	find_linearly_dependent_columns(linearly_dependent_columns, c, l, b, r);
	find_G_submatrix(linearly_dependent_columns, c, l, b, t, r);
	system("vim QC_LDPC_G_Submatrix_Full.txt");
	return 0;
}
