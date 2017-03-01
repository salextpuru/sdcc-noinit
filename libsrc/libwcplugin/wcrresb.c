#include <wcplugin.h>
#include <wcpluginsp.h>

void	wcRRESB(wcWindow* win)__naked{
	win;
__asm;
	iy_init
	get_ix
	ld	a,#2
	wcentry
	procret
__endasm;
}
