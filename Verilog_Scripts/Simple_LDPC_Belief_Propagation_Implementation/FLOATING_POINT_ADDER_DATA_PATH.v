//Module to Implement the Data Path of the Floating Point Adder

`timescale 1ns/1ps

module FLOATING_POINT_ADDER_DATA_PATH(in1, in2, out);
	input[31:0] in1, in2;
	output[31:0] out;

	wire[7:0] exponent1, exponent2;
	wire l;
	wire[7:0] diff;
	wire[7:0] larger_exponent;
	wire[22:0] mantissa1, mantissa2;
	wire[22:0] mantissa_with_smaller_exponent, mantissa_with_larger_exponent;
	wire[23:0] input_mantissa_1, input_mantissa_2;
	wire sign_of_amaller_exponent, sign_of_larger_exponent;
	wire carry_out;
	wire[23:0] mantissa_sum;
	wire is_result_zero;
	wire[4:0] negative_exponent_shift;
	wire[7:0] positive_shifted_exponent, negative_shifted_exponent;
	wire[7:0] final_exponent;
	wire[23:0] positive_shifted_mantissa, negative_shifted_mantissa;
	wire[23:0] final_mantissa;

	assign exponent1 = in1[30:23];
	assign exponent2 = in2[30:23];
	assign mantissa1 = in1[22:0];
	assign mantissa2 = in2[22:0];
	assign input_mantissa_2 = {1'b1, mantissa_with_larger_exponent};
	assign out[30:23] = final_exponent;
	assign out[22:0] = final_mantissa[22:0];

	FLOATING_POINT_ADDER_SMALL_ALU generate_exponent_difference(l, diff, exponent1, exponent2);
	FLOATING_POINT_ADDER_EXPONENT_BUS_MUX_21 select_larger_exponent(larger_exponent, exponent1, exponent2, l);
	FLOATING_POINT_ADDER_MANTISSA_BUS_MUX_21 select_mantissa_with_smaller_exponent(mantissa_with_smaller_exponent, mantissa2, mantissa1, l);
	FLOATING_POINT_ADDER_MANTISSA_MUX_21 select_sign_of_smaller_exponent(sign_of_smaller_exponent, in2[31], in1[31], l);
	FLOATING_POINT_ADDER_MANTISSA_BUS_MUX_21 select_mantissa_with_larger_exponent(mantissa_with_larger_exponent, mantissa1, mantissa2, l);
	FLOATING_POINT_ADDER_MANTISSA_MUX_21 select_sign_of_larger_exponent(sign_of_larger_exponent, in1[31], in2[31], l);
	FLOATING_POINT_ADDER_BARREL_SHIFTER generate_input_mantissa_1(input_mantissa_1, mantissa_with_smaller_exponent, diff);
	FLOATING_POINT_ADDER_BIG_ALU generate_added_mantissa_and_sign(carry_out, mantissa_sum, out[31], input_mantissa_1, sign_of_smaller_exponent, input_mantissa_2, sign_of_larger_exponent);
	FLOATING_POINT_ADDER_LEADING_ZEROS_COUNTER find_number_of_leading_zeros_in_mantissa_sum(negative_exponent_shift, is_result_zero, mantissa_sum);
	FLOATING_POINT_ADDER_EXPONENT_POSITIVE_SHIFTER generate_positive_shifted_exponent(positive_shifted_exponent, larger_exponent);
	FLOATING_POINT_ADDER_EXPONENT_NEGATIVE_SHIFTER generate_negative_shifted_exponent(negative_shifted_exponent, larger_exponent, negative_exponent_shift);
	FLOATING_POINT_ADDER_EXPONENT_BUS_MUX_21 generate_final_exponent(final_exponent, negative_shifted_exponent, positive_shifted_exponent, carry_out);
	FLOATING_POINT_ADDER_MANTISSA_BARREL_LEFT_SHIFTER generate_negative_shifted_mantissa(negative_shifted_mantissa, mantissa_sum, negative_exponent_shift);
	FLOATING_POINT_ADDER_MANTISSA_BARREL_RIGHT_SHIFTER generate_positive_shifted_mantissa(positive_shifted_mantissa, mantissa_sum);
	FLOATING_POINT_ADDER_MANTISSA_BUS_MUX_21_24_BITS generate_final_mantissa(final_mantissa, negative_shifted_mantissa, positive_shifted_mantissa, carry_out);
endmodule
