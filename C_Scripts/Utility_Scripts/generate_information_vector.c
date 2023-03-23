#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define k 2127

int main(void) {
	srand(time(0));
	static int information_vector[k];
	for (int i = 0; i < k; i++) {
		information_vector[i] = (int)(rand()) % 2;
	}
	FILE* fptr;
	fptr = fopen("information_vector.txt", "w");
	for (int i = 0; i < k; i++) {
		fprintf(fptr, "%d", information_vector[i]);
	}
	fclose(fptr);
	system("vim information_vector.txt");
	return 0;
}
