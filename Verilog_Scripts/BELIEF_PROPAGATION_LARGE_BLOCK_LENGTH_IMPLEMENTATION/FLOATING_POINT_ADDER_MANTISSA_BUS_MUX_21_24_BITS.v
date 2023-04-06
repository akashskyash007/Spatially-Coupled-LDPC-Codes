//24 Bit 2 to 1 MUX

`timescale 1ns/1ps

module FLOATING_POINT_ADDER_MANTISSA_BUS_MUX_21_24_BITS(out, in1, in2, sel);
	input[23:0] in1, in2;
	input sel;
	output reg[23:0] out;

	always @(*) begin
		if (sel)
			out = in2;
		else
			out = in1;
	end
endmodule
