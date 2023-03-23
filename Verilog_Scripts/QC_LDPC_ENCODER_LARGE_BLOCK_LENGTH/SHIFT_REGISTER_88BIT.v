//Modelling an 88 bit shift register

`timescale 1ns/1ps

module SHIFT_REGISTER_88_BIT(clk, clear, load, in, out);
	input clk, clear, load;
	input[87:0] in;
	output reg[87:0] out;

	always @(posedge clk or posedge clear) begin
		if (clear)
			out <= 88'b0;
		else if (load) 
			out <= in;
	end
endmodule
