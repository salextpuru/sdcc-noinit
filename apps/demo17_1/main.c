#include <types.h>
#include <conio.h>
#include <spr0.h>

extern Sprite0 sdccnoinit;

static void flash_atr() __naked {
	__asm;
	ld a,#0x00
	ld bc,#100
flash_atr_loop:
	push af
	push bc

	ld hl, #0x5800
	ld de, #0x5801
	ld bc, #0x2FF
	ld (hl),a
	ldir
	
	inc a 
	and #0x7F
	halt
	
	pop bc
	pop af
	dec bc
	ld a,b
	or c
	
	jr nz,flash_atr_loop
	ret
	__endasm;
}

int main(){
	// Init screen
	ccls(7);
	
	spr0_out0(&sdccnoinit,0,0);
	
	flash_atr();
	
	while(1){}
	//
	return 0;
}
