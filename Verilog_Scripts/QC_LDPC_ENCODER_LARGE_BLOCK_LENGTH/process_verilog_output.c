#include <stdio.h>
#include <stdlib.h>

#define k 2127
#define n 3520
#define b 88
#define l 16
#define num_result_bits l * b
#define num_systematic_bits n - l * b

int main(void) {
	FILE* fptr;
	fptr = fopen("information_vector.txt", "r");
	static int code_vector[n];
	for (int i = 0; i < num_systematic_bits; i++) {
		char ch = fgetc(fptr);
		code_vector[i] = ch - 48;
	}
	fclose(fptr);
	fptr = fopen("result_vector.txt", "r");
	for (int i = num_systematic_bits; i < n; i++) {
		char ch = fgetc(fptr);
		code_vector[i] = ch - 48;
	}
	fclose(fptr);
	fptr = fopen("code_vector.txt", "w");
	for (int i = 0; i < n; i++) {
		fprintf(fptr, "%d", code_vector[i]);
	}
	fclose(fptr);
	system("vim code_vector.txt");
	return 0;
}
