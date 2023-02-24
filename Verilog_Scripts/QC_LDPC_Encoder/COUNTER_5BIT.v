//Modelling a 5-bit Counter

`timescale 1ns/1ps

module COUNTER_5BIT(clk, clear, count);
	input clear, clk;
	output reg[4:0] count;

	always @(posedge clk or posedge clear) begin
		if (clear)
			count <= 5'b0;
		else
			count <= count + 1;
	end
endmodule
