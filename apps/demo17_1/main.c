#include <types.h>
#include <conio.h>
#include <spr0.h>

#include "spr_shadow.h"

extern const Sprite0 sdccnoinit;

int main(){
	uint8_t i;
	
	// Init screen
	//shsc_set_color(016);
	shsc_cls();

	shsc_flip();
	while(1){}
	
__asm;
	;// test screen
	ld hl,#_sdccnoinit+4
	ld de,#0x6000
	ld bc,#0x1800
	ldir
	;//
__endasm;
	
	shsc_flip();
	while(1){}
	//
	return 0;
}
