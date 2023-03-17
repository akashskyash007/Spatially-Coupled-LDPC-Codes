#include <stdio.h>
#include <stdlib.h>

#define J 88
#define K 88
#define EXPANSION_FACTOR 88
#define num_rows J * EXPANSION_FACTOR
#define num_columns K * EXPANSION_FACTOR

void debug() {
	FILE* fptr;
	fptr = fopen("H_MATRIX.txt", "r");
	static int H[num_rows][num_columns];
	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < num_columns; j++) {
			char ch = fgetc(fptr);
			H[i][j] = ch - 48;
			ch = fgetc(fptr);
		}
		char ch = fgetc(fptr);
	}
	/*
	for (int s = 0; s < num_rows - 1; s++) {
		for (int t = s + 1; t < num_rows; t++) {
			int matches = 0;
			for (int i = 0; i < num_columns; i++) {
				if (H[s][i] == 1 && H[t][i] == 1) {
					matches++;
				}
			}
			if (matches > 1) {
				printf("Graph 4 Length formed by rows %d and %d\n", s, t);
				exit(0);
			}
			else {
				printf("Tested rows %d and %d\n", s, t);
			}
		}
	}
	*/
	int column_index = 0;
	for (int i = 0; i < EXPANSION_FACTOR; i++) {
		printf("%d ", H[0][column_index * EXPANSION_FACTOR + i]);
	}
	printf("\n");
	for (int i = 0; i < EXPANSION_FACTOR; i++) {
		printf("%d ", H[88][column_index * EXPANSION_FACTOR + i]);
	}
}

int main(void) {
	debug();
	return 0;
}
