#include <wcplugin.h>
#include <wcpluginsp.h>

void wcPRSRW(wcWindow* win, const char* text, uint8_t x, uint8_t y, uint16_t len, uint8_t color)__naked{
	win;text;x;y;len;color;
__asm;
	iy_init

	; win
	get_ix
	
	; text
	get_hl
	
	; x y
	get_de
	
	; len
	get_bc
	
	; color
	get_a
	;
	push	af
	;// call PRSRW
	ld	a,#3
	wcentry
	pop	af
	ex	af,af' ; '
	;// call PRIAT
	ld	a,#4
	wcentry
	procret
__endasm;
}
