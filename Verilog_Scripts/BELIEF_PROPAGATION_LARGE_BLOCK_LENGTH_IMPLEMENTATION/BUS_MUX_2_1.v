//2 to 1 32-bit Bus Multiplexer

`timescale 1ns/1ps

module BUS_MUX_2_1(out, in1, in2, sel);
	input[31:0] in1, in2;
	output reg[31:0] out;
	input sel;

	always @(*) begin
		case (sel)
			1'b0: out = in1;
			1'b1: out = in2;
		endcase
	end
endmodule
