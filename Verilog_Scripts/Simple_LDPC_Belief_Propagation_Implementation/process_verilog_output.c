#include <stdio.h>
#include <stdlib.h>

//Convert Exponent From Binary to Decimal Form
int find_exponent(int* exponent_binary_array) {
	int current_multiplier = 1;
	int result = 0;
	for (int i = 7; i >= 0; i--) {
		result = result + current_multiplier * exponent_binary_array[i];
		current_multiplier *= 2;
	}
	return result;
}

//Convert Fractional Binary Array to Float
float find_fractional_part(int* fractional_binary_array, int len) {
	float current_multiplier = 0.5;
	float result = 0;
	for (int i = 0; i < len; i++) {
		result = result + current_multiplier * fractional_binary_array[i];
		current_multiplier /= 2;
	}
	return result;
}

//Convert Decimal Array to Float
float find_decimal_part(int* decimal_array, int len) {
	int current_multiplier = 1;
	float result = 0;
	for (int i = len - 1; i >= 0; i--) {
		result = result + current_multiplier * decimal_array[i];
	        current_multiplier *= 2;
	}
	return result;
}

//Convert IEEE 754 representation to floating point number and print it
float convert_representation_to_number(int* floating_point_representation) {
	//Sign Bit Processing
	int sign = floating_point_representation[0] ? -1 : 1;
	int exponent_binary_array[8];
	for (int i = 1; i < 9; i++) {
		exponent_binary_array[i - 1] = floating_point_representation[i];
	}
	int exponent_with_bias = find_exponent(exponent_binary_array);
	int exponent = exponent_with_bias - 127;
	if (exponent < 0) {
		int temp = exponent * -1;
		int fractional_binary_array[23 + temp];
		for (int i = 0; i < temp - 1; i++) {
			fractional_binary_array[i] = 0;
		}
		fractional_binary_array[temp - 1] = 1;
		for (int i = temp; i < 23 + temp; i++) {
			fractional_binary_array[i] = floating_point_representation[i - temp + 9];
		}
		float result;
		result = find_fractional_part(fractional_binary_array, 23 + temp);
		return result * sign;
	}
	else {
		int mantissa_length = exponent + 1;
		int fractional_length = 23 - mantissa_length;
		int decimal_array[mantissa_length];
		decimal_array[0] = 1;
		for (int i = 1; i < mantissa_length; i++) {
			decimal_array[i] = floating_point_representation[i - 1 + 9];
		}
		float decimal_part = find_decimal_part(decimal_array, mantissa_length);
		int fractional_array[fractional_length];
		for (int i = 9 + mantissa_length - 1; i < 32; i++) {
			fractional_array[i - (9 + mantissa_length - 1)] = floating_point_representation[i];
		}
		float fractional_part = find_fractional_part(fractional_array, fractional_length);
		return sign * (decimal_part + fractional_part);
	}
}

//Process Verilog Output File and Write Actual Floating Point Numbers to Another File
void process_verilog_output_file(int num_rows, int num_columns, int num_iterations) {
	FILE* fptr_in;
	FILE* fptr_out;
	fptr_in = fopen("parity_check_matrix_results.txt", "r");
	fptr_out = fopen("final_parity_check_matrix.txt", "w");
	char current_line[1000];
	int curr_row = 0;
	fprintf(fptr_out, "Initialized Storage Matrix:\n");
	int current_iteration = 1;
	while (fgets(current_line, sizeof(current_line), fptr_in) != NULL) {
		if (current_line[0] < 48 || current_line[0] > 49) {
			continue;
		}
		else {
			int curr_pos = 0;
			for (int i = 0; i < num_columns; i++) {
				int curr_floating_point_representation[32];
				for (int j = 0; j < 32; j++) {
					curr_floating_point_representation[j] = current_line[curr_pos++] - 48;
				}
				float current_floating_point_number = convert_representation_to_number(curr_floating_point_representation);
				fprintf(fptr_out, "%f ", current_floating_point_number);
				curr_pos++;
			}
			fprintf(fptr_out, "\n");
			curr_row++;
			if (curr_row % num_rows == 0) {
				fprintf(fptr_out, "\n");
				if (curr_row % 2 != 0) {
					if (current_iteration <= num_iterations) {
						fprintf(fptr_out, "Iteration %d\n", current_iteration);
						current_iteration++;
						fprintf(fptr_out, "Storage Matrix after Check Node Update:\n");
					}
				}
				else {
					fprintf(fptr_out, "Storage Matrix after Bit Node Update:\n");
				}
			}
		}
	}
	fclose(fptr_in);
	fclose(fptr_out);
}

int main(void) {
	int num_rows = 3;
	int num_columns = 6;
	int num_iterations = 10;
	process_verilog_output_file(num_rows, num_columns, num_iterations);
	system("vim final_parity_check_matrix.txt");
	return 0;
}
