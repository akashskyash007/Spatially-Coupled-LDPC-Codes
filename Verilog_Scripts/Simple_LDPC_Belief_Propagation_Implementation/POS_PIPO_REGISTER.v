//2-bit parallel in parallel out register to store the minimum position

`timescale 1ns/1ps

module POS_PIPO_REGISTER(clk, load, out, in);
	input clk, load;
	input[1:0] in;
	output reg[1:0] out;

	always @(posedge clk) begin
		if (load)
			out <= in;
	end
endmodule
