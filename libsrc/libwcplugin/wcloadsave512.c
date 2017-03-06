#include <wcplugin.h>
#include <wcpluginsp.h>

void* wcLOAD512(void* buf, uint8_t sectors)__naked{
	buf;sectors;
__asm;
	ld	c,#48
sl512:
	iy_init
	;// buffer
	get_hl
	;// sectors
	get_a
	ld	b,a
	;
	ld	a,c
	wcentry
	;// if A=0F then EOF
	cp	#0x0F
	procretnz
	;// EOF
	ld hl,#0000
	ret
__endasm;
}

void* wcSAVE512(void* buf, uint8_t sectors)__naked{
	buf;sectors;
__asm;
	ld	c,#49
	jr	sl512
__endasm;
}
