//Test Bench for Cyclic Shift Register

`timescale 1ns/1ps

module cyclic_shift_register_test_bench;
	reg[15:0] in;
	reg clk, load;
	wire[15:0] out;
	
	CYCLIC_SHIFT_REGISTER_16BIT DUT(clk, load, in, out);

	initial clk = 1'b0;
	always #5 clk = ~clk;

	initial begin
		$dumpfile("CYCLIC_SHIFT_REGISTER_16BIT.vcd");
		$dumpvars(0, cyclic_shift_register_test_bench);
		$monitor($time, ": out = %16b", out);
		in = 16'b1011101110111011;
		#2 load = 1'b1;
		#5 load = 1'b0;
		#100 $finish;
	end
endmodule
