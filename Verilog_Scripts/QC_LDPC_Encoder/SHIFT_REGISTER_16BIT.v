//Modelling a 16 bit shift register

`timescale 1ns/1ps

module SHIFT_REGISTER_16_BIT(clk, clear, load, in, out);
	input clk, clear, load;
	input[15:0] in;
	output reg[15:0] out;

	always @(posedge clk or posedge clear) begin
		if (clear)
			out <= 16'b0;
		else if (load) 
			out <= in;
	end
endmodule
