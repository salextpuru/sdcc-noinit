#include <types.h>
#include <conio.h>

#include "zxscradr.h"


int main(){
	// Init screen
	ccls(7);
	print("Test string size 32 byte length.");
	
__asm;
	// size
	ld b,#0x20
	// adr
	ld hl,#0x4000
	// shift
	ld c,#0x00 
	
	
	
	
__endasm;
	while(1){}
	//
	return 0;
}
