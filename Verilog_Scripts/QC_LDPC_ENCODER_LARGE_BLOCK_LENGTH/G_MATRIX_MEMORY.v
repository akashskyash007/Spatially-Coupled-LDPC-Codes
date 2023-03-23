//Module to Store the First Circulant Rows of Generator Matrix in Memory

`timescale 1ns/1ps

module G_MATRIX_MEMORY(clk, sel, out);
	input clk;
	input[5:0] sel;
	output reg[16 * 88 - 1: 0] out;

	reg[16 * 88 - 1: 0] G_MEMORY[0:38];
	reg[16 * 88 - 1: 0] curr_row;
	integer fptr;
	integer i;
	integer scan_file;

	initial begin
		fptr = $fopen("G_MATRIX_ROWS.txt", "r");
		for (i = 0; i < 39; i++) begin
			scan_file = $fscanf(fptr, "%1408b\n", curr_row);
			G_MEMORY[i] = curr_row;
		end
		$fclose(fptr);
	end

	always @(*) begin
		out = G_MEMORY[sel];
	end
endmodule
