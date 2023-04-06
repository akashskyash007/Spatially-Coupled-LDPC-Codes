//3520 - to - 1 32 bit Bus Multiplexer

`timescale 1ns/1ps

module BUS_MUX_3520_1(out, inputs, sel);
	input[32 * 40 - 1: 0] inputs;
	output reg[31:0] out;
	input[5:0] sel;
	integer i, j;

	always @(*) begin
		i = 31;	
		j = sel * 32 + 32 - 1;
		while (i >= 0) begin
			out[i] = inputs[j];
			i = i - 1;
			j = j - 1;
		end
	end
endmodule
