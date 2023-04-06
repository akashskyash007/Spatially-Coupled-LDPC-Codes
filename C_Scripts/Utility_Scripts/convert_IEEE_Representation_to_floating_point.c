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

int main(void) {
	char floating_point_representation_str[] = "00111111011101110001111011010101";
	int floating_point_representation[32];
	for (int i = 0; i < 32; i++) {
		floating_point_representation[i] = floating_point_representation_str[i] - 48;
	}
	float result = convert_representation_to_number(floating_point_representation);
	printf("%f\n", result);
	return 0;
}
