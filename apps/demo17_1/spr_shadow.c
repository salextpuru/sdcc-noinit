/**
 * @file spr_shadow.c - Shadow screen functions
 */

#include <stdint.h>
#include "spr_shadow.h"

// 0bXXX0000000000000 - Only 3 high bits can be non-zero!
static uint8_t* scr_adr=(uint8_t*)0x4000;

// any addr
static uint8_t* shascr_adr=(uint8_t*)0x6000;

static uint8_t scr_color=016;

void shsc_flip()__naked{
__asm;
	; // Copy characters
	ld de,(_scr_adr)
	ld hl,(_shascr_adr)
	ld bc,#0x1800
	;// Copy loop
flip_loop0:
	ld a,(hl)
	ld (de),a
	; // Modify src
	inc hl
	; // Modify dst
	ld a,e
	and #0x1F
	inc a
	and #0x20
	jr z, flip_c1 ; // only increment
	;// Next line
	ld a,e
	and #0xE0
	ld e,a
	;//
	ld a,d
	and #0x07
	inc a
	and #0x08
	jr z, flip_c2 ; // only increment
	;// y3y4y5 ++
	ld a,d
	and #0xF8
	ld d,a
	ld a,e
	add #0x20
	ld e,a
	jr nc, flip_eol ; // only increment
	;// next 1/3 of screen
	ld a,d
	add #0x08
	ld d,a
	jr nc, flip_eol
flip_c2:
	inc d
	jr nc, flip_eol
	
flip_c1:
	inc e
	
flip_eol:
	; End of loop ?
	dec bc
	ld a,b 
	or c
	jr nz, flip_loop0
	; // Copy attributes
	ld bc,#0x300
	ldir
	ret
__endasm;
}

// set color
void shsc_set_color(uint8_t c){
	scr_color = c;
}

// clear
void shsc_cls(){
__asm;
	ld hl,(_shascr_adr)
	push hl
	pop de 
	inc de
	xor a
	ld (hl),a
	ld bc,#0x17FF
	ldir
	inc hl
	inc de
	ld a,(_scr_color)
	ld (hl),a
	ld bc,#0x2FF
	ldir
	ret
__endasm;
}

// assembler
// in:	C - x
// 	B - y
// out:
//	HL - adress on shadow screen
void shsc_adr_asm()__naked{
__asm;
	ld hl,(_shascr_adr)
	add hl,bc
	ret
__endasm;
}

// return adress on shadow screen
uint8_t* shsc_adr(uint8_t x, uint8_t y){
__asm;
	pop hl
	pop bc
	push bc
	push hl
	jr _shsc_adr_asm
__endasm;
}

