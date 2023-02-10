//32 bit Parallel In Parallel Out Register to Store the Minimum and Second
//Minimum

`timescale 1ns/1ps

module MIN_PIPO_REGISTER(clk, load, initialize, out, in);
	input clk, load, initialize;
	input[31:0] in;
	output reg[31:0] out;

	always @(posedge clk or posedge initialize) begin
		if (initialize)
			out <= 32'hFFFFFFFF;
		else if (load)
			out <= in;
	end
endmodule
