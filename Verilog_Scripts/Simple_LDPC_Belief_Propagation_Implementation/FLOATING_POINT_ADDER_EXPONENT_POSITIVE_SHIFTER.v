//Module to Generate Positive Shifted Exponent

`timescale 1ns/1ps

module FLOATING_POINT_ADDER_EXPONENT_POSITIVE_SHIFTER(out, in);
	input[7:0] in;
	output reg[7:0] out;

	always @(*)
		out = in + 1'b1;
endmodule
