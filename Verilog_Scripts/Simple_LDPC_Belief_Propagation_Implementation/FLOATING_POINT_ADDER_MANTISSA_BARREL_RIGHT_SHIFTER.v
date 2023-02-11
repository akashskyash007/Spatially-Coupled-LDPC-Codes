//Module to Generate Positive Shifted Mantissa

`timescale 1ns/1ps

module FLOATING_POINT_ADDER_MANTISSA_BARREL_RIGHT_SHIFTER(out, in);
	input[23:0] in;
	output[23:0] out;

	assign out = in >> 1;
endmodule
