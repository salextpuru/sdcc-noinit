#include <types.h>
#include <conio.h>
#include <spr0.h>

#include "spr_shadow.h"

#define baseadr _sprd_xbh

extern const unsigned char baseadr[];

int main(){
	uint8_t i;
	
	// Init screen
	shsc_cls();
while(1){
__asm;
	ld hl,#baseadr+0
	ld de,#0x6000
	ld bc,#0x0203
	call _shsc_spr2scr_asm
	call _shsc_flip
	
	ld hl,#baseadr+48
	ld de,#0x6000
	ld bc,#0x0203
	call _shsc_spr2scr_asm
	call _shsc_flip
	
	ld hl,#baseadr+48*2
	ld de,#0x6000
	ld bc,#0x0203
	call _shsc_spr2scr_asm
	call _shsc_flip
	
	ld hl,#baseadr+48*3
	ld de,#0x6000
	ld bc,#0x0203
	call _shsc_spr2scr_asm
	call _shsc_flip
__endasm;
}
	while(1){}
	//
	return 0;
}
