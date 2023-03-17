//Code to construct a wide girth QCLDPC based on finite field construction

#include <stdio.h>
#include <stdlib.h>

int evaluate_power(int alpha, int q, int t) {
	int result = 1;
	for (int i = 1; i <= t; i++) {
		result = (result * alpha) % q;
	}
	return result;
}

int find_power(int ele, int q, int alpha) {
	if (ele == 0) {
		return 0;
	}
	else {
		int res = 1;
		int curr_value = 1;
		while (curr_value != ele) {
			curr_value = (curr_value * alpha) % q;
			res++;
		}
		return res;
	}
}

void construct_H_matrix(int q, int alpha) {
	int W[q - 1][q - 1];
	for (int i = 0; i < q - 1; i++) {
		for (int j = 0; j < q - 1; j++) {
			W[i][j] = evaluate_power(alpha, q, i + j) - 1;
		}
	}
	int B[q - 1][q - 1];
	for (int i = 0; i < q - 1; i++) {
		for (int j = 0; j < q - 1; j++) {
			B[i][j] = find_power(W[i][j], q, alpha);
		}
	}
	FILE* fptr;
	fptr = fopen("BASE_MATRIX.txt", "w");
	for (int i = 0; i < 16; i++) {
		for (int j = 1; j <= 40; j++) {
			fprintf(fptr, "%d ", B[i][j]);
		}
		fprintf(fptr, "\n");
	}
	fclose(fptr);
}

int main(void) {
	int q = 89;
	int alpha = 3;
	construct_H_matrix(q, alpha);
	system("vim BASE_MATRIX.txt");
	return 0;
}
