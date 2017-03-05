#include <wcplugin.h>
#include <wcpluginsp.h>

void	wcISTRinit2(wcWindow* wnd, uint8_t x, uint8_t y, uint8_t curpos, uint8_t wlen, char* buf, uint16_t bufsize)__naked{
    wnd;x;y;curpos;wlen;buf;bufsize;
__asm;
	iy_init
	get_ix
	;
.globl wcISTRinit2common
wcISTRinit2common:
	;
	get_de ; // x,y
	get_bc ; // curpos, wlen
	get_hl ; // buffer
	;
	exx
	get_hl ; // bufsize
	exx
	;
	ld	a,#0xFD
	ex	af,af';'
	ld	a,#9
	wcentry
	;
	procret
__endasm;
}

void	wcISTREdit2(wcWindow* wnd)__naked{
    wnd;
__asm;
	iy_init
	get_ix
	;
	ld	a,#00
	ex	af,af';'
	ld	a,#9
	wcentry
	;
	ld	a,#02
	ex	af,af';'
	ld	a,#9
	wcentry
	;
	procret
__endasm;
}
