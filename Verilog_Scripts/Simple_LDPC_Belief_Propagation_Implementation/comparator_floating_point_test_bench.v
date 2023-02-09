`timescale 1ns/1ps

module comparator_floating_point_tb;
	reg[31:0] in1, in2;
	wire l;

	comparator_floating_point DUT(l, in1, in2);

	initial begin
		$dumpfile("comparator_floating_point.vcd");
		$dumpvars(0, comparator_floating_point_tb);
		$monitor("in1 = %32b, in2 = %32b, l = %b", in1, in2, l);
		in1 = 32'b00111110100110011001100110011001; in2 = 32'b00111111100110011001100110011010;          //in1 = 0.3, in2 = 1.2
		#5 in1 = 32'b00111111100110011001100110011010; in2 = 32'b00111110100110011001100110011001;	 //in1 = 1.2, in2 = 0.3
		#5 in1 = 32'b00111111100110011001100110011010; in2 = 32'b01000010110010000000000000000000;       //in1 = 1.2, in2 = 100
		#5 in1 = 32'b01000010110010000000000000000000; in2 = 32'b00111111100110011001100110011010;       //in1 = 100, in2 = 1.2
		#5 in1 = 32'b01000010110010000000000000000000; in2 = 32'b01000010110010000000000000000000;       //in1 = 100, in2 = 100
	end
endmodule
