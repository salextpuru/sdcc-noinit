/**
 * @file scrarea13.c - разные процедурочки для работы с 1/3 экрана
 */

#include <im2.h>
#include <spr0.h>

#include "scrarea13.h"

static uint16_t rndnext=0x6AE7;
static void fadeRND3() __naked {
	__asm
	;// HL=adr of 1/3 screen
	
	ld 	bc,#0x0800 ;// 2K (1/3 scr)

	push	hl
fadeRND3L1:
	call	rndnext_g

	ld 	a,(_rndnext)
	and	(hl)
	ld 	(hl),a

	inc	hl
	dec 	bc
	ld	a,c
	or	b
	jr	nz,fadeRND3L1
	pop	hl

	ret

rndnext_g:
	push	hl
	ld	hl,(_rndnext)
	ld 	a,#0x5A
	add	a,l
	ld 	l,a
	ld 	a,#0xA5
	adc 	a,h
	ld	h,a
	adc 	a,l
	ld 	l,a
	ld 	(_rndnext),hl
	pop	hl
	ret
	__endasm;
}

static void clear13() __naked {
__asm
	;// HL=adr of 1/3 screen
	ld 	bc,#0x07FF ;// 2K (1/3 scr)
	push	hl
	pop	de
	push	hl
	inc	de
	ld	(hl),#0
	ldir
	pop	hl
	ld 	c,h
	ld	a,h
	and	#0xF8
	add	a,#0x18
	ld	h,a
	ld	a,c
	and	#0x18
	rr	a
	rr	a
	rr	a
	add	a,h
	ld 	h,a
	ld 	bc,#0x00FF
	push	hl
	pop	de
	inc	de
	ex 	af,af';'
	ld	(hl),a
	ldir
	ret
__endasm;
}

void clearTextArea(uint8_t area, uint8_t color) __naked{
__asm;
	;// get number (0..2) adr to hl
	ld 	hl,#0x0002
	add	hl,sp

	;// get number (0..2) to b
	ld 	b,(hl)
	;// color to A'
	inc  	hl
	ld 	a,(hl)
	ex 	af,af';'
	dec	hl
	;// counter of 0x800
	xor a
	inc 	b
	ld 	l,a ;// L=0

clearTextAreaL2:
	dec	b
	jr	z, clearTextAreaL1
	add 	a,#0x08 ; // 0x0800 is 1/3 screen offset
	jr	clearTextAreaL2
clearTextAreaL1:
	ld	h,a
	ld	bc,(_spr0_scr_adr)
	add	hl,bc
	;// HL = adress of 1/3 screen
	ld 	b,#0x0C
	;// Clear area 0x0C times
clearTextAreaL3:
	push	hl
	push	bc
	call	_fadeRND3
	pop	bc
	pop	hl
	djnz	clearTextAreaL3
	;// Full clear
	call	_clear13
	ret
__endasm;
}

uint16_t getScr13Rnd() __naked {
__asm;
	call	rndnext_g
	ld	hl,(_rndnext)
	ret
__endasm;
}
