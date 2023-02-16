//Module to Compute the Mantissa Sum and Resultant Sign

`timescale 1ns/1ps

module FLOATING_POINT_ADDER_BIG_ALU(carry_out, result_magnitude_without_carry, result_sign, input1_magnitude, input1_sign, input2_magnitude, input2_sign);
	input[23:0] input1_magnitude, input2_magnitude;
	input input1_sign, input2_sign;
	output reg result_sign;
	output[23:0] result_magnitude_without_carry;
	output carry_out;

	reg[24:0] result_magnitude;
	wire is_subtraction;

	assign is_subtraction = input1_sign ^ input2_sign;
	assign carry_out = result_magnitude[24];
	assign result_magnitude_without_carry = result_magnitude[23:0];

	always @(*) begin
		if (is_subtraction) begin
			if (input1_magnitude >= input2_magnitude)
				result_magnitude = input1_magnitude - input2_magnitude;
			else
				result_magnitude = input2_magnitude - input1_magnitude;
		end
		else
			result_magnitude = input1_magnitude + input2_magnitude;
		if (input1_sign == 0 && input2_sign == 0)
			result_sign = 0;
		else if (input1_sign == 0 && input2_sign == 1)
			if (input1_magnitude >= input2_magnitude)
				result_sign = 0;
			else
				result_sign = 1;
		else if (input1_sign == 1 && input2_sign == 0)
			if (input2_magnitude >= input1_magnitude)
				result_sign = 0;
			else
				result_sign = 1;
		else
			result_sign = 1;
	end
endmodule
