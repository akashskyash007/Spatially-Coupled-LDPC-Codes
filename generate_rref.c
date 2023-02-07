#include <stdio.h>
#include <stdlib.h>

static int k = 4;
static int n = 7;

void row_reducer(int H[n - k][n]) {
	for (int curr_row = 0; curr_row < n - k; curr_row++) {
		if (H[curr_row][curr_row] != 1) {
			for (int row = curr_row + 1; row < n - k; row++) {
				if (H[row][curr_row] == 1) {
					for (int i = 0; i < n; i++) {
						H[curr_row][i] = (H[curr_row][i] + H[row][i]) % 2;
					}
					break;
				}
			}
		}
		for (int i = 0; i < n - k; i++) {
			if (i == curr_row) {
				continue;
			}
			if (H[i][curr_row] == 1) {
				for (int j = 0; j < n; j++) {
					H[i][j] = (H[i][j] + H[curr_row][j]) % 2;
				}
			}
		}
	}
}

int main(void) {
	int num_parity_bits = n - k;
	int H[num_parity_bits][n];
	FILE* fptr;
	fptr = fopen("parity_check_matrix.txt", "r");
	for (int i = 0; i < n - k; i++) {
		for (int j = 0; j < n; j++) {
			char ch = fgetc(fptr);
			H[i][j] = ch - 48;
			ch = fgetc(fptr);
		}
	}
	printf("Original Matrix:\n");
	for (int i = 0; i < n - k; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", H[i][j]);
		}
		printf("\n");
	}
	row_reducer(H);
	printf("Row Reduced Matrix:\n");
	for (int i = 0; i < n - k; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", H[i][j]);
		}
		printf("\n");
	}
	return 0;
}
