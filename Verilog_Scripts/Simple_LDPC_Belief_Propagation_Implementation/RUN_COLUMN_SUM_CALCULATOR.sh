iverilog -o COLUMN_SUM_CALCULATOR COLUMN_SUM_CALCULATOR_DATA_PATH.v COLUMN_SUM_CALCULATOR_CONTROL_PATH.v COLUMN_SUM_ADDER_TEST_BENCH.v BUS_MUX_31.v COLUMN_SUM_PIPO_REGISTER.v COLUMN_SUM_UP_COUNTER.v FLOATING_POINT_ADDER_DATA_PATH.v FLOATING_POINT_ADDER_SMALL_ALU.v FLOATING_POINT_ADDER_EXPONENT_BUS_MUX_21.v FLOATING_POINT_ADDER_MANTISSA_BS_MUX_21.v FLOATING_POINT_ADDER_BARREL_SHIFTER.v FLOATING_POINT_ADDER_BIG_ALU.v FLOATING_POINT_ADDER_MANTISSA_MUX_21.v FLOATING_POINT_ADDER_LEADING_ZEROS_COUNTER.v FLOATING_POINT_ADDER_PRIORITY_ENCODER.v FLOATING_POINT_ADDER_EXPONENT_POSITIVE_SHIFTER.v FLOATING_POINT_ADDER_EXPONENT_NEGATIVE_SHIFTER.v FLOATING_POINT_ADDER_MANTISSA_BARREL_LEFT_SHIFTER.v FLOATING_POINT_ADDER_MANTISSA_BARREL_RIGHT_SHIFTER.v FLOATING_POINT_ADDER_MANTISSA_BUS_MUX_21_24_BITS.v;
vvp COLUMN_SUM_CALCULATOR
gtkwave COLUMN_SUM_CALCULATOR.vcd