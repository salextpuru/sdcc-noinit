#include <wcplugin.h>
#include <wcpluginsp.h>

void*	wcGADRW(wcWindow* wnd, uint8_t x, uint8_t y)__naked{
	wnd;x;y;
__asm;
	iy_init
	;// whd
	get_ix
	;// x,y
	get_de
	;
	ld	a,#5
	wcentry
	;// HL= return adress
	procret
__endasm;
}
