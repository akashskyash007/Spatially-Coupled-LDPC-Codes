//Up Counter for Column Sum Index Calculation

`timescale 1ns/1ps

module COLUMN_SUM_UP_COUNTER(clk, clr, count);
	input clk, clr;
	output reg[1:0] count;

	always @(posedge clk or posedge clr) begin
		if (clr)
			count <= 2'b0;
		else
			count <= count + 1;
	end
endmodule
