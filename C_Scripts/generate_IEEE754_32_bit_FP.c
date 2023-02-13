//Code to Generate the Single Precision IEEE 754 Standard for any Floating Point Number; Does not Consider Denormal Numbers

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Returns the absolute value of the number
float absolute(float x) {
	return x >= 0 ? x : -1 * x;
}

//Generates Binary Representation of Integer Part
int generate_integer_binary_representation(int x) {
	int temp = x;
	int count = 0;
	while (temp > 0) {
		count++;
		temp /= 2;
	}
	
	if (count == 0) {
		return 0;
	}
	
	int* binary_array = (int*)(malloc(count * sizeof(int)));
	int pos = 0;
	while (x > 0) {
		binary_array[pos++] = x % 2;
		x /= 2;
	}

	int result = 0;
	for (int i = count - 1; i >= 0; i--) {
		result = result * 10 + binary_array[i];
	}
	
	return result;
}

//Generate Binary Representation of Fractional Part
void generate_fraction_binary_representation(float x, int* fractional_binary_array) {
	int num_bits_fractional_part = 64;       //Hard Coded for Simplicity
	for (int i = 0; i < num_bits_fractional_part; i++) {
		x *= 2;
		fractional_binary_array[i] = floor(x);
		x -= floor(x);
	}
}

//Find the Integer Representation of the Exponent
int find_exponent(int mantissa, int* fractional_binary_array) {
	int exponent = 0;
	if (mantissa == 0) {
		while (fractional_binary_array[exponent * -1] == 0) {
			exponent--;
		}
		exponent--;
	}
	else {
		while (mantissa > 0) {
			exponent++;
			mantissa /= 10;
		}
		exponent--;
	}
	return exponent;
}

//Function to Fill the Exponent Part of the Final Result
void fill_exponent_part(int* result, int exponent) {
	int num_digits_in_exponent = 0;
	int temp = exponent;
	while (temp > 0) {
		num_digits_in_exponent++;
		temp /= 2;
	}
	int exponent_binary_array[num_digits_in_exponent];
	int count = 0;
	while (exponent > 0) {
		exponent_binary_array[count++] = exponent % 2;
		exponent /= 2;
	}
	int num_leading_zeros = 8 - num_digits_in_exponent;
	for (int i = 1; i <= num_leading_zeros; i++) {
		result[i] = 0;
	}
	int pos = num_leading_zeros + 1;
	for (int i = num_digits_in_exponent - 1; i >= 0; i--) {
		result[pos++] = exponent_binary_array[i];
	}
}

//Function to Fill the Mantissa part of Final Result
void fill_mantissa_part(int* result, int mantissa, int* fractional_binary_array) {
	if (mantissa == 0) {
		int pos = 0;
		while (fractional_binary_array[pos] == 0) {
			pos++;
		}
		pos++;
		int curr_pos = 9;
		for (int i = curr_pos; i < 32; i++) {
			result[curr_pos++] = fractional_binary_array[pos++];
		}
	}
	else {
		int num_digits_in_mantissa = 0;
		int temp = mantissa;
		while (temp > 0) {
			num_digits_in_mantissa++;
			temp /= 10;
		}
		int mantissa_binary_array[num_digits_in_mantissa];
		int count = 0;
		while (mantissa > 0) {
			mantissa_binary_array[count++] = mantissa % 10;
			mantissa /= 10;
		}
		int pos = 9;
		for (int i = num_digits_in_mantissa - 2; i >= 0; i--) {
			result[pos++] = mantissa_binary_array[i];
		}
		int temp_pos = pos;
		for (int i = pos; i < 32; i++) {
			result[temp_pos++] = fractional_binary_array[i - pos];
		}
	}
}

//Generates and prints the single precision floating point representation
void generate_spfp_representation(float input) {
	float input_magnitude = absolute(input);
	int integer_part = floor(input_magnitude);
	float fractional_part = input_magnitude - integer_part;
	int integer_part_binary_representation = generate_integer_binary_representation(integer_part);
	printf("%d\n", integer_part_binary_representation);
	int fractional_part_binary_array[64];
	generate_fraction_binary_representation(fractional_part, fractional_part_binary_array);
	for (int i = 0; i < 64; i++) {
		printf("%d ", fractional_part_binary_array[i]);
	}
	printf("\n");
	int exponent = find_exponent(integer_part_binary_representation, fractional_part_binary_array);
	printf("%d\n", exponent);
	int biased_exponent = exponent + 127;
	int result[32];
	result[0] = input < 0;
	fill_exponent_part(result, biased_exponent);
	fill_mantissa_part(result, integer_part_binary_representation, fractional_part_binary_array);
	for (int i = 0; i < 32; i++) {
		printf("%d", result[i]);
	}
	printf("\n");
}

int main(void) {
	float input = 0.9;
	generate_spfp_representation(input);
	return 0;
}
