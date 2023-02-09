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
float generate_fraction_binary_representation(float x) {
	
}

//Generates and prints the single precision floating point representation
void generate_spfp_representation(float input) {
	float input_magnitude = absolute(input);
	int integer_part = floor(input_magnitude);
	float fractional_part = input_magnitude - integer_part;
	int integer_part_binary_representation = generate_integer_binary_representation(integer_part);
	printf("%d\n", integer_part_binary_representation);
}

int main(void) {
	float input = 5;
	generate_spfp_representation(input);
	return 0;
}
