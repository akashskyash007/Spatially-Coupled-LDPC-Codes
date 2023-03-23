//Modelling a 6 bit counter

`timescale 1ns/1ps

module COUNTER_6BIT(clk, clear, increment, count);
	input clear, clk, increment;
	output reg[5:0] count;

	always @(posedge clk or posedge clear) begin
		if (clear)
			count <= 6'b0;
		else if (increment)
			count <= count + 1;
	end
endmodule
