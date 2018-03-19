#include <types.h>
#include <spr0.h>

// Screen base adress	0x0000, 0x4000, 0x8000, 0xC000
//			0x2000, 0x6000, 0xA000, 0xE000
const WORD	spr0_scr_adr=0x4000;

void spr0_set_scr_adr(WORD adr)__naked{
__asm;
	pop	de
	pop	hl
	ld	(_spr0_scr_adr),hl
	push	hl
	push	de
	ret
__endasm;
}

void	spr0_out0(const Sprite0* adr, BYTE x, BYTE y)__naked{
__asm;
	push	ix
	ld	ix,#4
	add	ix,sp
	;// adr
	ld	e,0(ix)
	ld	d,1(ix)
	;// x
	ld	l,2(ix)
	;// y
	ld	h,3(ix)
	
	push	de
	pop	ix
	
	call	spr0_out0
	pop	ix
	ret
__endasm;
}

void	spr0_out0_attr(const Sprite0* adr, BYTE x, BYTE y)__naked{
__asm;
	push	ix
	ld	ix,#4
	add	ix,sp
	;// adr
	ld	e,0(ix)
	ld	d,1(ix)
	;// x
	ld	l,2(ix)
	;// y
	ld	h,3(ix)
	
	push	de
	pop	ix
	
	call	spr0_out0_attr
	pop	ix
	ret
__endasm;
}
