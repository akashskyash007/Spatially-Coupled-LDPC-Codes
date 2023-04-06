//Up Counter to count number of message passing iterations that have been
//completed

`timescale 1ns/1ps

module BELIEF_PROPAGATION_DATA_PATH_UP_COUNTER(clk, increment_count, reset_count, count);
	input clk, increment_count, reset_count;
	output reg[3:0] count;

	always @(posedge clk or posedge reset_count) begin
		if (reset_count)
			count <= 4'b0;
		else if (increment_count)
			count <= count + 1;
	end
endmodule
