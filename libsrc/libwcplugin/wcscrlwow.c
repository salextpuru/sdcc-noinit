#include <wcplugin.h>
#include <wcpluginsp.h>

void wcSCRLWOW(wcWindow* win, uint8_t scroll_mode,  uint8_t x, uint8_t y, uint8_t w, uint8_t h)__naked{
	win; scroll_mode; x; y; w; h;
__asm;
	iy_init
	
	; win
	get_ix
	
	; scroll mode
	get_a
	
	; x y
	get_de
	
	; w h
	get_bc
	
	;
	ex	af,af' ; '
	;
	ld	a,#84
	wcentry
	procret
__endasm;	 
}
