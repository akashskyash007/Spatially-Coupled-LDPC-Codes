//2 bit up counter with modification to skip the minimum position when
//calculating second minimum

`timescale 1ns/1ps

module UP_COUNTER(clk, reset, condition_check, min_index, count);
	input clk, reset, condition_check;
	input[1:0] min_index;
	output reg[1:0] count;
	
	reg[1:0] counter_input;
	wire reset_check;
	
	assign reset_check = (min_index == 2'b00) && condition_check;

	always @(*) begin
		counter_input = count + 1;
		if (counter_input == min_index && condition_check)
			counter_input = counter_input + 1;
	end

	always @(posedge clk or posedge reset) begin
		if (reset) begin
			if (reset_check)
				count <= 2'b01;
			else
				count <= 2'b00;
		end
		else begin
			count <= counter_input;
		end
	end
endmodule
