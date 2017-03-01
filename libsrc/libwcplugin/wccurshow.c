#include <wcplugin.h>
#include <wcpluginsp.h>

void	wcCURSHOW(wcWindow* wnd)__naked{
	wnd;
__asm;
	iy_init
	get_ix
	ld	a,#6
	wcentry
	procret
__endasm;
}
