//3 - to - 1 32 bit Bus Multiplexer

`timescale 1ns/1ps

module BUS_MUX_31(out, in1, in2, in3, sel);
	input[31:0] in1, in2, in3;
	output reg[31:0] out;
	input[1:0] sel;

	always @(*) begin
		case (sel)
			2'b00: out = in1;
			2'b01: out = in2;
			2'b10: out = in3;
			default: out = 32'b0;
		endcase
	end
endmodule
