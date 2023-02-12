//32 bit PIPO register to store column sum

`timescale 1ns/1ps

module COLUMN_SUM_PIPO_REGISTER(clk, clr, out, in);
	input clk, clr;
	input[31:0] in;
	output reg[31:0] out;

	always @(posedge clk or posedge clr) begin
		if (clr)
			out <= 32'b0;
		else
			out <= in;
	end
endmodule
