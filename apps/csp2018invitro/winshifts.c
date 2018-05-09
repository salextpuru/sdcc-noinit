/**
 * @file winshifts.h - Сдвиг окон во все стороны
 */
#include <spr0.h>
#include "winshifts.h"

void shiftLeftPix(const winShift* w) __naked {
__asm;
	pop	hl
	pop	bc
	push	bc
	push	hl
	push	ix
	push	bc
	pop	ix
	;//
	;// Get screen adr
	ld	l,00(ix) ;// X
	ld	a,02(ix) ;// W
	add	l
	dec	a
	ld	l,a	 ;// X+W-1
	ld	h,01(ix) ;// Y
	call sprXYtoHL ;// hl = screen adress
	;//
	ld	c,02(ix) ;// W
	ld	a,03(ix) ;// H(chars)
	add	a
	add	a
	add	a
	ld	b,a	 ;// H(pix)
	;//
shiftLeftPixLline:
	push	hl
	push	bc
	xor	a
	ex	af,af';'
	;// shift one line
shiftLeftPixHoriz:
	ex	af,af';'
	ld	a,(hl)
	rla
	ld	(hl),a
	ex	af,af';'
	
	dec	hl
	dec	c
	jr	nz,shiftLeftPixHoriz
	;//
	pop	bc
	pop	hl
	;// down to one line
	call	down_hl
	;// lines loop
	djnz	shiftLeftPixLline
	;//
	pop	ix
	ret
	
	;вход: HL=адрес экранной линии
	;выход: HL= адрес экранной линии ниже
down_hl:
	inc	h
	ld	a,h
	and	#7
	ret	nz
	ld	a,l
	add	a,#0x20
	ld	l,a
	ret	c
	ld	a,h
	sub	#8
	ld	h,a
	ret
__endasm;
}
