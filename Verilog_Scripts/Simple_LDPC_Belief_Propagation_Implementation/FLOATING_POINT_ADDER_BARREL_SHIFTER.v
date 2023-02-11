//Module to Implement a Barrel Shifter in Behavioral Fashion

`timescale 1ns/1ps

module FLOATING_POINT_ADDER_BARREL_SHIFTER(out, in, shift_factor);
	input[22:0] in;
	input[7:0] shift_factor;
	output[23:0] out;

	wire[23:0] before_shift;

	assign before_shift = {1'b1, in[22:0]};
	assign out = before_shift >> shift_factor;
endmodule
