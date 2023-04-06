//Module to indicate the current layer of the parity check matrix

module BELIEF_PROPAGATION_DATA_PATH_LAYER_INDICATOR_COUNTER(clk, increment_count, reset_count, count);
	input clk, increment_count, reset_count;
	output reg[4:0] count;

	always @(posedge clk or posedge reset_count) begin
		if (reset_count)
			count <= 5'b0;
		else if (increment_count)
			count <= count + 1;
	end
endmodule
