/**
 * @file printscale.c - vertical scaled print
 */
#include <spr0.h>
#include "koi8r-8x8.h"
#include "printscale.h"

// ПОТОМ СДЕЛАТЬ параметром!
//static const void* psFont=(void*)0x3C00;
static const void* psFont=koi8r_8x8;
//

void printScale(uint8_t x, uint8_t y, uint8_t scale, uint8_t ch) __naked {
__asm;
	push 	ix
	ld 	ix,#4
	add 	ix,sp
	;// get char adress
	ld   	l,03(ix)
	ld   	h,#0
	add  	hl,hl
	add  	hl,hl
	add  	hl,hl
	ld   	bc,(_psFont)
	add  	hl,bc
	ex  	de,hl ;// de = char Adress

	;// Get screen adr
	ld   l,00(ix)
	ld   h,01(ix)
	call sprXYtoHL ;// hl = screen adress

	;// output
	ld	c,#08	;// lines
	;//
printScaleLH:
	ld 	b,02(ix) ;// scale
	ld 	a,(de)
	inc 	de
	;// do scale times
printScaleLSCL:
	ld	(hl),a
	ex 	af,af';'
	call	down_hl
	ex 	af,af';'
	djnz	printScaleLSCL
	dec 	c 
	jr 	nz,printScaleLH
	;//
	pop  ix
	ret
	
	;вход: HL=адрес экранной линии
	;выход: HL= адрес экранной линии ниже
down_hl:
	INC H
	LD A,H
	AND #7
	RET NZ
	LD A,L
	ADD A,#0x20
	LD L,A
	RET C
	LD A,H
	SUB #8
	LD H,A
	RET
__endasm;
}

void printStrScale(uint8_t x, uint8_t y, uint8_t scale, uint8_t* s) {
	while( ( x<0x20 ) && (*s) ) {
		printScale(x++, y, scale, *(s++));
	}
}
