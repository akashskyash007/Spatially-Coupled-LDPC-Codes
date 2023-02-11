//2 to 1 Bus Multiplexer for Mantissa

`timescale 1ns/1ps

module FLOATING_POINT_ADDER_MANTISSA_BUS_MUX_21(out, in1, in2, sel);
	input[22:0] in1, in2;
	output reg[22:0] out;
	input sel;

	always @(*) begin
		if (sel)
			out = in2;
		else
			out = in1;
	end
endmodule
