module tb;  
    reg[16 * 88 - 1:0] test_memory[0:38];
    reg[16*88 - 1:0] curr_memory;  
    integer fptr;  
    integer i;
    integer scan_file;
    initial begin  
    	fptr = $fopen("G_MATRIX_ROWS.txt", "r");  
      	for (i = 0; i < 39; i++) begin
     	    scan_file = $fscanf(fptr, "%1408b\n", curr_memory);
	    test_memory[i] = curr_memory;
    	end
    	$fclose(fptr);
      $monitor("%1408b", test_memory[38]);	
    end  
endmodule 
