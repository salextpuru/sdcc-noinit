void atrType(uint8_t x, uint8_t y, uint8_t atr, const char* s)__naked{
__asm;
	;// Entry
	push	ix
	ld	ix,#4
	add	ix,sp
	;//
	ld	l,00(ix)	;// X
	ld	h,01(ix)	;// Y
	call	sprXYtoHLattr	;// HL = adr of attr
	;//
	ld	e,03(ix)	;// Adr of str
	ld	d,04(ix)	;
	;//
	ld	c,02(ix)	;// ATR

atrTypePutsLoop:
	ld	a,(de)
	inc	de
	or	a
	push	af
	call	nz,atrTypePutc
	pop	af
	jr	nz, atrTypePutsLoop
	pop	ix
	;// exit
	ret

	;// Put one char (a=char code)
atrTypePutc:

	exx
	;// FONT! NEED to change!
	ld	de,(0x5C36)
	ld	l,a
	ld	h,#0
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,de
	ex	de,hl
	exx	;// de' = adr of char
	;//
	ld	b,#8
	push	hl
	
atrTypePutcLoopH:
	exx
	ld	a,(de)	;// get line of char
	inc	de	;// Next line of char
	exx
	;//
	push	bc
	push	hl
	;//
	ld	b,#8
atrTypePutcLoopV:
	bit	7,a
	jr	z,atrTypePutcLoopHC1
	ld	(hl),c
atrTypePutcLoopHC1:
	inc	hl
	rlca
	djnz	atrTypePutcLoopV
	;//
	pop	hl
	ld	bc,#0x20
	add	hl,bc
	pop	bc
	djnz	atrTypePutcLoopH
	;//
	pop	hl
	push	bc
	ld	bc,#0x08
	add	hl,bc
	pop	bc
	ret
__endasm;
}
