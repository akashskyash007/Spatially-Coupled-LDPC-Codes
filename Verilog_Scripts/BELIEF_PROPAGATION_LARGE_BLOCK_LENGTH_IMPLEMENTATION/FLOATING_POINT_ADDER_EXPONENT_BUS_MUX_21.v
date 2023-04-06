//Module to Select the Large of the Two Exponents using a Bus Multiplexer

`timescale 1ns/1ps

module FLOATING_POINT_ADDER_EXPONENT_BUS_MUX_21(out, in1, in2, sel);
	input[7:0] in1, in2;
	output reg[7:0] out;
	input sel;

	always @(*) begin
		if (sel)
			out = in2;
		else
			out = in1;
	end
endmodule
