#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define c 8
#define t 20
#define b 88
#define n t * b
#define k 1063
#define num_iterations 10
#define num_systematic_info_bits 1056

//Function to Perform Left Cyclic Shift By a Certain Factor
void perform_left_cyclic_shift(float* arr, int shift_factor) {
	for (int i = 1; i <= shift_factor - 1; i++) {
		float temp = arr[0];
		for (int j = 0; j < b - 1; j++) {
			arr[j] = arr[j + 1];
		}
		arr[b - 1] = temp;
	}
}

//Function to Perform Right Cyclic Shift by a Certain Factor
void perform_right_cyclic_shift(float* arr, int shift_factor) {
	for (int i = 1; i <= shift_factor - 1; i++) {
		float temp = arr[b - 1];
		for (int j = b - 1; j > 0; j--) {
			arr[j] = arr[j - 1];
		}
		arr[0] = temp;
	}
}

//Function to Return Absolute Value
float return_absolute_value(float x) {
	return x >= 0 ? x : x * -1;
}

//Function to Return Sign of a Number
int return_sign(float x) {
	return x >= 0 ? 1 : -1;
}

//Function to Perform Row Updation
void perform_row_update(float* curr_row) {
	float absolute_min_1 = INT_MAX;
	float absolute_min_2 = INT_MAX;
	int min_pos = -1;
	for (int i = 0; i < t; i++) {
		if (return_absolute_value(curr_row[i]) < return_absolute_value(absolute_min_1)) {
			absolute_min_1 = return_absolute_value(curr_row[i]);
			min_pos = i;
		}
		//printf("%f\n", absolute_min_1);
	}
	for (int i = 0; i < t; i++) {
		if (i == min_pos)
			continue;
		if (return_absolute_value(curr_row[i]) < return_absolute_value(absolute_min_2)) {
			absolute_min_2 = return_absolute_value(curr_row[i]);
		}
	}
	int overall_sign = -1;
	for (int i = 0; i < t; i++) {
		overall_sign *= return_sign(curr_row[i]);
	}
	for (int i = 0; i < t; i++) {
		if (i == min_pos) {
			float curr_magnitude = absolute_min_2;
			int curr_sign = overall_sign * return_sign(curr_row[i]);
			curr_row[i] = curr_magnitude * curr_sign;
		}
		else {
			float curr_magnitude = absolute_min_1;
			int curr_sign = overall_sign * return_sign(curr_row[i]);
			curr_row[i] = curr_magnitude * curr_sign;
		}
	}
}

void perform_belief_propagation(float* belief_vector) {
	
	//Load Base Matrix
	FILE* fptr;
	fptr = fopen("BASE_MATRIX.txt", "r");
	static int H_protograph[c][t];
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

	//Initialize Storage Matrix to Zeros
	static float storage_matrix[c][n];
	for (int i = 0; i < c; i++) {
		for (int j = 0; j < n; j++) {
			storage_matrix[i][j] = 0;
		}
	}

	//Main Loop to keep track of the number of completed iterations
	for (int curr_iteration = 1; curr_iteration <= num_iterations; curr_iteration++) {

		//Loop to process each layer of the parity check matrix
		for (int curr_layer = 0; curr_layer < c; curr_layer++) {
			
			//Update the Current Layer with Difference
			for (int i = 0; i < n; i++) {
				storage_matrix[curr_layer][i] = storage_matrix[curr_layer][i] - belief_vector[i];
			}

			//Store the current block row as a layer
			static float curr_block_row_temporary_storage[t][b];
			for (int i = 0; i < t; i++) {
				for (int j = 0; j < b; j++) {
					curr_block_row_temporary_storage[i][j] = storage_matrix[curr_layer][i * b + j];
				}
			}

			//Perform Row Processing
			for (int i = 0; i < t; i++) {
				perform_left_cyclic_shift(curr_block_row_temporary_storage[i], H_protograph[curr_layer][i]);
			}
			for (int i = 0; i < b; i++) {
				static float curr_row_temporary_storage[t];
				for (int j = 0; j < t; j++) {
					curr_row_temporary_storage[j] = curr_block_row_temporary_storage[j][i];
				}
				perform_row_update(curr_row_temporary_storage);
				for (int j = 0; j < t; j++) {
					curr_block_row_temporary_storage[j][i] = curr_row_temporary_storage[j];
				}
			}
			for (int i = 0; i < t; i++) {
				perform_right_cyclic_shift(curr_block_row_temporary_storage[i], H_protograph[curr_layer][i]);
			}
			for (int i = 0; i < t; i++) {
				for (int j = 0; j < b; j++) {
					storage_matrix[curr_layer][i * b + j] = curr_block_row_temporary_storage[i][j];
				}
			}

			//Updation of the Belief Vector (Column Processing)
			for (int i = 0; i < n; i++) {
				belief_vector[i] = belief_vector[i] + storage_matrix[curr_layer][i];
			}
		}

		if (curr_iteration > 1)
			fptr = fopen("BELIEF_PROPAGATION_RESULTS.txt", "a");
		else
			fptr = fopen("BELIEF_PROPAGATION_RESULTS.txt", "w");
		fprintf(fptr, "Iteration %d\n", curr_iteration);
		fprintf(fptr, "####################################################################################################\n");
		fprintf(fptr, "\nStorage Matrix\n");
		for (int i = 0; i < c; i++) {
			for (int j = 0; j < n; j++) {
				fprintf(fptr, "%f ", storage_matrix[i][j]);
			}
			fprintf(fptr, "\n");
		}
		fprintf(fptr, "\nBelief Vector\n");
		for (int i = 0; i < n; i++) {
			fprintf(fptr, "%f ", belief_vector[i]);
		}
		fprintf(fptr, "\n");
		fprintf(fptr, "####################################################################################################\n\n");
		fclose(fptr);
		//printf("Done Iteration %d/%d\n", curr_iteration, num_iterations);
	}
}

void generate_random_information_vector(int* information_vector) {
	srand(time(0));
	for (int i = 0; i < k; i++) {
		information_vector[i] = (int)(rand()) % 2;
	}
}

void generate_encoded_vector(int* information_vector, int* encoded_vector) {
	for (int i = 0; i < n; i++) {
		encoded_vector[i] = 0;
	}
	FILE* fptr;
	fptr = fopen("G_MATRIX.txt", "r");
	static int G[k][n];
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < n; j++) {
			char ch = fgetc(fptr);
			G[i][j] = ch - 48;
			ch = fgetc(fptr);
		}
		char ch = fgetc(fptr);
	}
	fclose(fptr);
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < n; j++) {
			encoded_vector[j] = (encoded_vector[j] + G[i][j] * information_vector[i]) % 2;
		}
	}
}

void add_channel_noise(float* received_vector, int* modulated_vector, float EbNodB) {
	float R = (int)(k) * 1.0/(int)(n);
	float EbNo = pow(10, EbNodB * 1.0/10);
	float sigma = 1.0/sqrt(2 * R * EbNo);
	
	char sigma_val[20];
	sprintf(sigma_val, "%f", sigma);
	char noise_vector_size[50];
	sprintf(noise_vector_size, "%d", n);
	char python_prompt[2000];
       	strcpy(python_prompt, "python3 /home/akash/MyFiles/SpatiallyCoupledLDPC/Python_Scripts/generate_noise.py ");
	strcat(python_prompt, noise_vector_size);
	strcat(python_prompt, " ");
	strcat(python_prompt, sigma_val);
	system(python_prompt);

	FILE* fptr;
	fptr = fopen("noise_vector.txt", "r");
	static float noise_vector[n];
	for (int i = 0; i < n; i++) {
		float curr_value;
		fscanf(fptr, "%f", &curr_value);
		noise_vector[i] = curr_value;
	}
	fclose(fptr);

	for (int i = 0; i < n; i++) {
		received_vector[i] = modulated_vector[i] + noise_vector[i];
	} 
}

int test_belief_propagation(float EbNodB) {
	static float received_vector[n];
	static int decoded_vector[n];
	static int information_vector[k];
	static int encoded_vector[n];
	static int modulated_vector[n];
	generate_random_information_vector(information_vector);
	generate_encoded_vector(information_vector, encoded_vector);
	for (int i = 0; i < n; i++) {
		if (encoded_vector[i] == 0) {
			modulated_vector[i] = -1;
		}
		else {
			modulated_vector[i] = 1;
		}
	}
	add_channel_noise(received_vector, modulated_vector, EbNodB);
	int num_errors = 0;
	for (int i = 0; i < num_systematic_info_bits; i++) {
		if (received_vector[i] >= 0) {
			decoded_vector[i] = 1;
		}
		else {
			decoded_vector[i] = 0;
		}
		if (decoded_vector[i] != encoded_vector[i]) {
			num_errors++;
		}
	}
	//printf("Number of Errors before Belief Propagation = %d\n", num_errors);
	perform_belief_propagation(received_vector);
	num_errors = 0;
	for (int i = 0; i < num_systematic_info_bits; i++) {
                if (received_vector[i] >= 0) {
                        decoded_vector[i] = 1;
                }
                else {
                        decoded_vector[i] = 0;
                }
                if (decoded_vector[i] != encoded_vector[i]) {
                        num_errors++;
                }
        }
	//printf("Number of Errors after Belief Propagation = %d\n", num_errors);
	return num_errors;
}

void generate_BER_curve() {
	float EbNodB_arr[100];
	float EbNodB_val = 0.0;
	for (int i = 0; i < 100; i++) {
		EbNodB_arr[i] = EbNodB_val;
		EbNodB_val += 0.1;	
	}
	int num_blocks = 100;
	float BER_arr[100];
	for (int i = 0; i < 100; i++) {
		long long int num_errors = 0;
		long long int total_bits_transmitted = num_blocks * num_systematic_info_bits;
		EbNodB_val = EbNodB_arr[i];

		float progress = 0.0;
  		int curr_c = 0, x = 0, last_c = 0;
		printf("Iteration %d/%d\n", (i + 1), 100);
  		fprintf(stderr, "%3d%% [", (int)progress);
  		for (x = 0; x < curr_c; x++){
    			fprintf(stderr, "=");
  		}
  		for (x = curr_c; x < 100; x++){
    			fprintf(stderr, " ");
  		}
  		fprintf(stderr, "]");

		for (int j = 1; j <= num_blocks; j++) {
			progress = j * 100.0/num_blocks;
    			curr_c = (int) progress;
    			fprintf(stderr, "\n\033[F");
    			fprintf(stderr, "%3d%%", (int)progress);
    			fprintf(stderr, "\033[1C");
    			fprintf(stderr, "\033[%dC=", last_c);
    			for (x = last_c; x < curr_c; x++){
      				fprintf(stderr, "=");
    			}
    			if(x < 100){
      				fprintf(stderr, ">");
    			}
    			last_c = curr_c;

			num_errors += test_belief_propagation(EbNodB_val);
		}
		float BER_val = (1.0 * num_errors)/total_bits_transmitted;
		BER_arr[i] = BER_val;
		printf("\n");
	}
	FILE* fptr;
	fptr = fopen("BER_RESULTS.txt", "w");
	for (int i = 0; i < 100; i++) {
		fprintf(fptr, "%f ", BER_arr[i]);
	}
	fclose(fptr);
}

int main(void) {
	generate_BER_curve();
	system("python3 /home/akash/MyFiles/SpatiallyCoupledLDPC/Python_Scripts/plot_BER_curve.py");
	//test_belief_propagation();
	//system("vim BELIEF_PROPAGATION_RESULTS.txt");
	return 0;
}
