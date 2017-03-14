#include "ringbuf.h"

void ringBufferInit(tRingBuffer* buf, void* data, uint16_t size)__naked{
	buf;data;size;
__asm;
	ld 	hl,#0002
	add	hl,sp
	
	;// get buf
	ld 	e,(hl)
	inc hl
	ld 	d,(hl)
	inc hl
	
	;// Store buf
	push 	de
	
	;// data
	ld 	c,(hl)
	inc hl
	ld 	b,(hl)
	inc hl
	
	;// size
	ld 	e,(hl)
	inc hl
	ld 	d,(hl)
	
	;// HL= buf
	pop	hl
	
	;// buf.size = size
	ld 	(hl),e
	inc	hl
	ld 	(hl),d
	inc	hl
	
	;// buf.data = data
	ld 	(hl),c
	inc	hl
	ld 	(hl),b
	inc	hl
	
	;// buf.begin = data
	ld 	(hl),c
	inc	hl
	ld 	(hl),b
	inc	hl
	
	;// buf.end = data
	ld 	(hl),c
	inc	hl
	ld 	(hl),b
	inc	hl
	
	;// bc = bc + de = data + size
	ld 	a,c
	add	a,e
	ld 	c,a
	ld 	a,b
	adc	a,d
	ld 	b,a
	
	;// data_end.end = data+size
	ld 	(hl),c
	inc	hl
	ld 	(hl),b
	;// 
	ret
__endasm;
}

// 2(ix),3(ix) - data
// 4(ix),5(ix) - begin
// 6(ix),7(ix) - end
// 8(ix),9(ix) - data_end
uint16_t ringBufferWrite(tRingBuffer* buf, void* data, uint16_t size)__naked{
	buf;data;size;
__asm;
	push	ix
	
	;// Stack
	ld 	hl,#0004
	add	hl,sp
	
	;// get buf
	ld 	e,(hl)
	inc hl
	ld 	d,(hl)
	inc hl
	
	;// IX= buf
	push 	de
	pop 	ix
	
	;// BC=data
	ld 	c,(hl)
	inc hl
	ld 	b,(hl)
	inc hl
	
	;// DE=size
	ld 	e,(hl)
	inc hl
	ld 	d,(hl)
	
	;// Store size (DE)
	push	de
	
	;// Main loop
ringBufferWrite_loop:

	;// hl=end
	;// 6(ix),7(ix) - end
	ld	l,6(ix)
	ld	h,7(ix)
	
	push	hl
	
	;// Try increment..
	inc	hl
	
	;// compare data_end
	;// 8(ix),9(ix) - data_end
	ld 	a,l
	sub 	8(ix)
	ld 	a,h
	sbc 	9(ix)
	jr	c,ringBufferWrite_noreset
	
	;// hl=data
	;// 2(ix),3(ix) - data
	ld	l,2(ix)
	ld	h,3(ix)
	
ringBufferWrite_noreset:

	;// compare end==begin ?
	;// 4(ix),5(ix) - begin
	ld 	a,l
	cp 	4(ix)
	jr 	nz, ringBufferWrite_noz
	ld 	a,h
	cp 	5(ix)

	;// if hl == end then buffer is full
	jr	z,ringBufferWrite_full
	
ringBufferWrite_noz:

	;// end = hl
	ld	6(ix),l
	ld	7(ix),h
	
	;// Restore hl
	pop 	hl
	
	;// write one byte
	ld	a,(bc)
	ld	(hl),a
	inc	bc
	dec 	de
	ld 	a,e
	or	d
	jr	nz,ringBufferWrite_loop
	jr	ringBufferWrite_end
	
	;// FULL!! Exit
ringBufferWrite_full:
	
	;// Restore hl
	pop 	hl

ringBufferWrite_end:
	;// return old(de) - de
	or 	a ;// CY=0
	
	;// Restore size (HL)
	pop 	hl	;// hl = old(de)
	sbc	hl,de	;// hl = written bytes
	;//
	pop	ix
	ret
__endasm;
}

// 2(ix),3(ix) - data
// 4(ix),5(ix) - begin
// 6(ix),7(ix) - end
// 8(ix),9(ix) - data_end
uint16_t ringBufferRead(tRingBuffer* buf, void* data, uint16_t size)__naked{
	buf;data;size;
__asm;
	push	ix
	
	;// Stack
	ld 	hl,#0004
	add	hl,sp
	
	;// get buf
	ld 	e,(hl)
	inc hl
	ld 	d,(hl)
	inc hl
	
	;// IX= buf
	push 	de
	pop 	ix
	
	;// BC=data
	ld 	c,(hl)
	inc hl
	ld 	b,(hl)
	inc hl
	
	;// DE=size
	ld 	e,(hl)
	inc hl
	ld 	d,(hl)
	
	;// Store size (DE)
	push	de
	
	;// Main loop
ringBufferRead_loop:

	;// hl=end
	// 4(ix),5(ix) - begin
	ld	l,4(ix)
	ld	h,5(ix)

	;// compare end==begin ?
	// 6(ix),7(ix) - end
	ld 	a,l
	cp 	6(ix)
	jr	nz, ringBufferRead_noz
	ld 	a,h
	cp 	7(ix)
	;// if hl == end then buffer is empty
	jr	z,ringBufferRead_empty
ringBufferRead_noz:
	
	;// Read one byte
	ld	a,(hl)
	ld	(bc),a
	
	;// Try increment..
	inc	hl
	
	;// compare data_end
	;// 8(ix),9(ix) - data_end
	ld 	a,l
	sub 	8(ix)
	ld 	a,h
	sbc 	9(ix)
	jr	c,ringBufferRead_noreset
	
	;// hl=data
	;// 2(ix),3(ix) - data
	ld	l,2(ix)
	ld	h,3(ix)
	
ringBufferRead_noreset:

	;// begin = hl
	ld	4(ix),l
	ld	5(ix),h
	;//
	inc	bc
	dec 	de
	ld 	a,e
	or	d
	jr	nz,ringBufferRead_loop
	
	;// EMPTY!! Exit
ringBufferRead_empty:
	
	;// return old(de) - de
	or 	a ;// CY=0
	
	;// Restore size (HL)
	pop 	hl	;// hl = old(de)
	sbc	hl,de	;// hl = written bytes
	;//
	pop	ix
	ret
__endasm;
}
