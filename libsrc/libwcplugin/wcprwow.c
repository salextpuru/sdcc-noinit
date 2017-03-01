#include <wcplugin.h>
#include <wcpluginsp.h>

void wcPRWOW(wcWindow* win)__naked{
	win;
__asm;
	iy_init
	get_ix
	ld	a,#1
	wcentry
	procret
__endasm;
}
