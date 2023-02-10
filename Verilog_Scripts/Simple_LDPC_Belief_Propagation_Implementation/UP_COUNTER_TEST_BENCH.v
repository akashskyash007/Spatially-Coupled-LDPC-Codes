//Test Bench for Up Counter

module UP_COUNTER_TEST_BENCH;
	reg clk, reset, condition_check;
	reg[1:0] min_index;
	wire[1:0] count;

	UP_COUNTER DUT(clk, reset, condition_check, min_index, count);

	initial clk = 1'b0;

	always #5 clk = ~clk;

	initial begin
		$dumpfile("UP_COUNTER.vcd");
		$dumpvars(0, UP_COUNTER_TEST_BENCH);
		$monitor($time, ": count = %2b", count);
		#2 reset = 1'b1; condition_check = 1'b1; min_index = 2'b11;
		#5 reset = 1'b0;
		#100 $finish;
	end
endmodule
