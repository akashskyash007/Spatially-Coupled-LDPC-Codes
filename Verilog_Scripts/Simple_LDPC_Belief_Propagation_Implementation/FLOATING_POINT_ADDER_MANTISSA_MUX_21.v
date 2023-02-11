//2 to 1 Multiplexer

`timescale 1ns/1ps

module FLOATING_POINT_ADDER_MANTISSA_MUX_21(out, in1, in2, sel);
	input in1, in2, sel;
	output reg out;
	always @(*) begin
		if (sel)
			out = in2;
		else
			out = in1;
	end
endmodule
