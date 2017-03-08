#include <wcplugin.h>
#include <wcpluginsp.h>

uint8_t wcFENTRY(void* wcentry)__naked{
	wcentry;
__asm;
	iy_init
	;// get adress of buffer
	get_hl
	;// hl=&(wcENTRY.size) store it
	push 	hl
	;// pointer to &(wcENTRY.flag)
	ld	de,#0x0008
	add	hl,de
	;// 
	ld	a,#59
	wcentry
	;// ix=&(wcENTRY.size)
	pop	ix
	jr	z,wcentry_notfound
	;// store size
	ld	0(ix),l
	ld	1(ix),h
	ld	2(ix),e
	ld	3(ix),d
	ld	l,#0x00
	jr	wcentry_found
	;// Not found
wcentry_notfound:
	ld	l,#0xFF
wcentry_found:
	procret
__endasm;
}
