#include "im2.h"

void im2SetHandler(void* handler)__naked{
handler;
__asm;
	ld	hl,#2
	add	hl,sp
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	inc	hl
	ex	de,hl
	ld	(im2_handler_u),hl
	;//-------------------------------------------------
	
	ld	hl,#vec_table
	ld	l,#0xff
	;// HL = (vec_table & 0xFF00) | 0xFF
	ld	a,h
	ld	i,a
	
	;// Set handler user
	ld	(hl), #<im2_handler
	inc	hl
	ld	(hl), #>im2_handler
	;//
	ret
vec_table:
	.ds 257

im2_handler_u:
	.dw 0x0000

im2_handler:
	di
	push	af
	push	bc
	push	de
	push	hl
	push	ix
	push	iy
	exx
	ex	af,af' ;'
	push	af
	push	bc
	push	de
	push	hl
	push	ix
	push	iy
	;// return adress
	ld	hl,#im2_handler_r
	push	hl
	;// and call im2_handler_u
	ld	hl,(im2_handler_u)
	jp	(hl)
im2_handler_r:
	;//call	#0x38
	;//
	pop	iy
	pop	ix
	pop	hl
	pop	de
	pop	bc
	pop	af
	exx
	ex	af,af' ;'
	pop	iy
	pop	ix
	pop	hl
	pop	de
	pop	bc
	pop	af
	ei
	reti
__endasm;
}

void im2Set()__naked{
	__asm;
	im 2
	ret
	__endasm;
}

void im1Set()__naked{
	__asm;
	im 1
	ret
	__endasm;
}

void im0Set()__naked{
	__asm;
	im 0
	ret
	__endasm;
}

void CLI()__naked{
	__asm;
	di
	ret
	__endasm;
}

void SEI()__naked{
	__asm;
	ei
	ret
	__endasm;
}

void waitINTS(uint8_t tick){
	while(tick){
		__asm;
			halt
		__endasm;
		tick--;
	}
}
