//Module to Generate Negative Shifted Exponent

`timescale 1ns/1ps

module FLOATING_POINT_ADDER_EXPONENT_NEGATIVE_SHIFTER(out, in, decr_value);
	input[7:0] in;
	input[4:0] decr_value;
	output reg[7:0] out;

	always @(*)
		out = in - decr_value;
endmodule
