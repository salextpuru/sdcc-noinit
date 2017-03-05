#include <wcplugin.h>
#include <wcpluginsp.h>


uint8_t wcTXTPR(wcWindow* win, const char* text, uint8_t x, uint8_t y)__naked{
	win;text;x;y; 
__asm;
	iy_init

	; win
	get_ix
	
	; text
	get_hl
	
	; x y
	get_de
	
	;
	ld	a,#11
	wcentry
	;// o: D - Y (след строка)
    ;//    E - X (без изменений)
    ld l,e 
	procret
__endasm;
}
