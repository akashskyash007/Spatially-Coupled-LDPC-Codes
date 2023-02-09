#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int num_rows = 0;
int num_elements = 0;
int num_columns = 0;

void encode(int H[num_rows][num_columns], int* information_vector, int* encoded_vector) {
	int num_info_bits = num_columns - num_rows;
	for (int i = 0; i < num_rows; i++) {
		int current_parity_bit = 0;
		for (int j = num_rows; j < num_columns; j++) {
			if (H[i][j] == 1) {
				current_parity_bit = (current_parity_bit + information_vector[j - num_rows]) % 2;
			}
		}
		encoded_vector[i] = current_parity_bit;
	}
	for (int i = num_rows; i < num_columns; i++) {
		encoded_vector[i] = information_vector[i - num_rows];
	}
}

int sgn(float x) {
	return x >= 0 ? 1 : -1;
}

float absolute(float x) {
	return x >= 0 ? x : x * -1;
}

void decode(int H[num_rows][num_columns], float* received_vector, float* decoded_vector, int num_iterations) {
	float storage_matrix[num_rows][num_columns];
	
	//Initialization
	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < num_columns; j++) {
			if (H[i][j] == 1) {
				storage_matrix[i][j] = received_vector[j];
			}
			else {
				storage_matrix[i][j] = 0;
			}
		}
	}

	//Print Storage Matrix after Initialization
	printf("Initialized Storage Matrix:\n");
	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < num_columns; j++) {
			printf("%f ", storage_matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	//Belief Propagation
	for (int iterator = 1; iterator <= num_iterations; iterator++) {

		//Check Node Update
		for (int i = 0; i < num_rows; i++) {
			float min1 = INT_MAX;
			float min2 = INT_MAX;
			for (int j = 0; j < num_columns; j++) {
				if (H[i][j] == 0) {
					continue;
				}
				if (absolute(storage_matrix[i][j]) < min1) {
					min1 = absolute(storage_matrix[i][j]);
				}
			}
			for (int j = 0; j < num_columns; j++) {
				if (absolute(storage_matrix[i][j]) == min1 || H[i][j] == 0) {
					continue;
				}
				if (absolute(storage_matrix[i][j]) < min2) {
					min2 = absolute(storage_matrix[i][j]);
				}
			}
			int overall_sign = -1;
			for (int j = 0; j < num_columns; j++) {
				if (H[i][j] != 0) {
					overall_sign *= sgn(storage_matrix[i][j]);
				}
			}
			for (int j = 0; j < num_columns; j++) {
				if (H[i][j] != 0) {
					float current_magnitude;
					if (storage_matrix[i][j] == min1) {
						current_magnitude = min2;
					}
					else {
						current_magnitude = min1;
					}
					int current_sign = overall_sign * sgn(storage_matrix[i][j]);
					storage_matrix[i][j] = current_magnitude * current_sign;
				}
			}
		}

		//Printing Storage Matrix after Check Node Update
		printf("Iteration %d\n", iterator);
		printf("Check Node Updation:\n");
		for (int i = 0; i < num_rows; i++) {
			for (int j = 0; j < num_columns; j++) {
				printf("%f ", storage_matrix[i][j]);
			}
			printf("\n");
		}
		printf("\n");

		//Bit Node Update
		for (int i = 0; i < num_columns; i++) {
			decoded_vector[i] = received_vector[i];
		}
		for (int i = 0; i < num_rows; i++) {
			for (int j = 0; j < num_columns; j++) {
				decoded_vector[j] += storage_matrix[i][j];
			}
		}
		for (int i = 0; i < num_rows; i++) {
			for (int j = 0; j < num_columns; j++) {
				if (H[i][j] != 0) {
					storage_matrix[i][j] = decoded_vector[j] - storage_matrix[i][j];
				}
			}
		}

		//Print Sum Vector and Storage Matrix after Bit Node Updates
		printf("Sum Vector\n");
		for (int i = 0; i < num_columns; i++) {
			printf("%f ", decoded_vector[i]);
		}
		printf("\n\n");
		printf("Storage Matrix after Bit Node Update\n");
		for (int i = 0; i < num_rows; i++) {
			for (int j = 0; j < num_columns; j++) {
				printf("%f ", storage_matrix[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}
}

int main(void) {
	FILE* fptr;
	fptr = fopen("simple_LDPC_parity_check_matrix.txt", "r");
	if (fptr == NULL) {
		printf("File Could Not be Opened!!");
	}
	else {
		char ch = ' ';
		while (ch != EOF) {
			ch = fgetc(fptr);
			if (ch == '\n') {
				num_rows++;
			}
			if (ch >= 48 && ch <= 57) {
				num_elements++;
			}
		}
		num_columns = num_elements/num_rows;
		int H[num_rows][num_columns];
		fseek(fptr, 0, SEEK_SET);
		for (int i = 0; i < num_rows; i++) {
			for (int j = 0; j < num_columns; j++) {
				char ch = fgetc(fptr);
				H[i][j] = ch - 48;
				ch = fgetc(fptr);
			}
		}
		printf("Loaded Parity Matrix:\n");
		int information_vector[] = {0, 0, 1};
		int encoded_vector[num_columns];
		encode(H, information_vector, encoded_vector);
		printf("Information Vector: ");
		int num_info_bits = num_columns - num_rows;
		for (int i = 0; i < num_info_bits; i++) {
			printf("%d ", information_vector[i]);
		}
		printf("\n");
		printf("Encoded Vector: ");
		for (int i = 0; i < num_columns; i++) {
			printf("%d ", encoded_vector[i]);
		}
		printf("\n");
		float received_vector[] = {0.6, 0.7, 0.7, -0.6, -0.8, 0.9};
		float decoded_vector[num_columns];
		decode(H, received_vector, decoded_vector, 10);
	}
	return 0;
}
