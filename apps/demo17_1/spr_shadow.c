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
	; // Copy attributes
	ld  bc,#0x1800
	ld  hl,(_scr_adr)
	add hl,bc
	ex de,hl
	ld hl,(_shascr_adr)
	add hl,bc
	ld bc,#0x300
	ldir
	
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

// assembler
// in:	C - x
// 	B - y
// out:
//	HL - attr adress on shadow screen
void shsc_atradr_asm()__naked{
__asm;
	ld	l,b
	ld 	b,#0x00
	ld 	h,b
	// y * 32
	add 	hl,hl
	add 	hl,hl
	add 	hl,hl
	add 	hl,hl
	add 	hl,hl
	// y*32 + x
	add 	hl,bc
	// y*32 + x + adr
	ld	bc,(_shascr_adr)
	add 	hl,bc
	ld	bc,#0x1800
	add 	hl,bc
	ret
__endasm;
}

// return adress on shadow screen
uint8_t* shsc_adr(uint8_t x, uint8_t y)__naked{
__asm;
	pop hl
	pop bc
	push bc
	push hl
	jr _shsc_adr_asm
__endasm;
}

// return adress on shadow screen
uint8_t* shsc_atradr(uint8_t x, uint8_t y)__naked{
__asm;
	pop hl
	pop bc
	push bc
	push hl
	jr _shsc_atradr_asm
__endasm;
}

// in:
// 	hl - source adr
// 	de - destination adr
//	c - width
//	b - heigh
void shsc_spr2scr_asm()__naked{
__asm;
	ld a,b
	add a,a
	add a,a
	add a,a
	ld b,a

shsc_spr2scr_asmh:
	push de
	push bc

shsc_spr2scr_asm0:
	ld a,(de)
	;//
shsc_spr2scr_asm_op:
	ld a,(hl)
	;//
	ld (de),a
	inc hl
	inc de
	dec c
	jr nz,shsc_spr2scr_asm0
	
	pop bc
	pop de
	
	ld a,e
	add #0x20
	ld e,a
	ld a,d
	adc #0
	ld d,a
	
	djnz shsc_spr2scr_asmh

	ret
__endasm;
}

/**
* @brief Вывод спрайта
* 
* @param sprdata - адрес спрайта
* @param scradr - адрес теневого экрана
* @param w - ширина (знакоместа)
* @param h - высота (знакоместа)
*/
void shsc_spr2scr(void* sprdata, void* scradr, uint8_t w, uint8_t h ) __naked {
__asm;
	push	ix
	ld	ix,#4
	add	ix,sp
	;
	exx
	ld	l,0x00(ix)
	ld	h,0x01(ix)
	ld	e,0x02(ix)
	ld	d,0x03(ix)
	ld	c,0x04(ix)
	ld	b,0x05(ix)
	call	_shsc_spr2scr_asm
	exx
	;
	pop	ix
	ret
__endasm;
}

// in:
// 	hl - attr adr in screen
// 	a  - color
//	c - width
//	b - heigh
void shsc_atr2scr_asm()__naked{
__asm;
	ld 	de,#0x0020
shsc_atr2scr_asm_h:
	push	hl
	push	bc
	;//
shsc_atr2scr_asm_w:
	ld	(hl),a
	inc 	hl
	dec	c
	jr 	nz,shsc_atr2scr_asm_w
	;//
	pop	bc
	pop	hl
	add 	hl,de
	djnz	shsc_atr2scr_asm_h
	ret
__endasm;
}

void shsc_atr2scr(uint8_t color, void* scradr, uint8_t w, uint8_t h)__naked {
__asm;
	push	ix
	ld	ix,#4
	add	ix,sp
	;
	exx
	ld	a,0x00(ix)
	ld	l,0x01(ix)
	ld	h,0x02(ix)
	ld	c,0x03(ix)
	ld	b,0x04(ix)
	call	_shsc_atr2scr_asm
	exx
	;
	pop	ix
	ret
	ret
__endasm;
}

void shsc_putmode()__naked{
__asm;
	ld a,#0x7E
	ld (shsc_spr2scr_asm_op),a
	ret
__endasm;
}

void shsc_xormode()__naked{
__asm;
	ld a,#0xAE
	ld (shsc_spr2scr_asm_op),a
	ret
__endasm;
}

void shsc_andmode()__naked{
__asm;
	ld a,#0xA6
	ld (shsc_spr2scr_asm_op),a
	ret
__endasm;
}

void shsc_ormode()__naked{
__asm;
	ld a,#0xB6
	ld (shsc_spr2scr_asm_op),a
	ret
__endasm;
}
