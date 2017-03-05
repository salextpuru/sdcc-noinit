#include <wcplugin.h>
#include <wcpluginsp.h>

void	wcISTRinit2IndTop(wcWindow* wnd, uint8_t x, uint8_t y, uint8_t curpos, uint8_t wlen, char* buf, uint16_t bufsize)__naked{
    wnd;x;y;curpos;wlen;buf;bufsize;
__asm;
.globl wcISTRinit2common
	iy_init
	get_ix
	;
	push 	ix
	push	iy
	ld	hl,#0x00FF
	ld	a,#0xFE
	ex	af,af';'
	ld	a,#9
	wcentry
	pop	iy
	pop	ix
	;
	jp	wcISTRinit2common
__endasm;
}

void	wcISTRinit2IndBottom(wcWindow* wnd, uint8_t x, uint8_t y, uint8_t curpos, uint8_t wlen, char* buf, uint16_t bufsize)__naked{
    wnd;x;y;curpos;wlen;buf;bufsize;
__asm;
.globl wcISTRinit2common
	iy_init
	get_ix
	;
	push 	ix
	push	iy
	ld	hl,#0x01FF
	ld	a,#0xFE
	ex	af,af';'
	ld	a,#9
	wcentry
	pop	iy
	pop	ix
	;
	jp	wcISTRinit2common
__endasm;
}

void	wcISTREdit2Ind(wcWindow* wnd)__naked{
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
	ld	a,#03
	ex	af,af';'
	ld	a,#9
	wcentry
	;
	procret
__endasm;
}
