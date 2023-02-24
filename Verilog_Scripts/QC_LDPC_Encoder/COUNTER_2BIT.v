//Modelling a 2 bit counter

`timescale 1ns/1ps

module COUNTER_2BIT(clk, clear, increment, count);
	input clear, clk, increment;
	output reg[1:0] count;

	always @(posedge clk or posedge clear) begin
		if (clear)
			count <= 2'b00;
		else if (increment)
			count <= count + 1;
	end
endmodule
