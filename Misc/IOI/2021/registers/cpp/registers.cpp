#include "registers.h"

void construct_instructions(int s, int n, int k, int q) {
	if(k==1){
		append_move(1,0);
		append_right(1,1,1);
		append_and(0,0,1);
	} else {
		append_move(1,0);
		append_right(1,1,2);
		append_and(2,0,1);
		// check if it's 01/10
		//append_print(2);
		append_xor(3,0,1);
		append_move(4,3);
		append_right(4,4,1);
		append_and(3,4,3);
		// clear first bit
		append_left(3,3,1999);
		append_right(3,3,1999);
		append_print(3);
		/*append_print(3);
		append_right(3,3,1);
		append_print(3);
		append_left(3,3,1);*/
		// and with the (xor) of first two
		append_move(6,0);
		append_left(6,6,1998);
		append_right(6,6,1998);
		
		append_right(6,6,1);
		append_xor(6,6,0);
		
		//append_print(3);
		append_and(3,6,3);
		append_or(0,2,3);
	}
}
