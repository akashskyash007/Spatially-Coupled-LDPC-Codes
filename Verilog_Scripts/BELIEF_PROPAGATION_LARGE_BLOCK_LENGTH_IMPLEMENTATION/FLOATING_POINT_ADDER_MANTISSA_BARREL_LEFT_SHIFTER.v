//Module to Generate Negative Shifted Exponent

`timescale 1ns/1ps

module FLOATING_POINT_ADDER_MANTISSA_BARREL_LEFT_SHIFTER(out, in, shift_factor);
	input[23:0] in;
	input[4:0] shift_factor;
	output reg[23:0] out;

	always @(*)
		out = in << shift_factor;
endmodule
