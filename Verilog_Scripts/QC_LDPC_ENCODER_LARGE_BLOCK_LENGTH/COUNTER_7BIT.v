//Modelling a 7-bit Counter

`timescale 1ns/1ps

module COUNTER_7BIT(clk, clear, count);
	input clear, clk;
	output reg[6:0] count;

	always @(posedge clk or posedge clear) begin
		if (clear)
			count <= 7'b0;
		else
			count <= count + 1;
	end
endmodule
