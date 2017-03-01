#include <wcplugin.h>
#include <wcpluginsp.h>

void	wcCURHIDE(wcWindow* wnd)__naked{
	wnd;
__asm;
	iy_init
	get_ix
	ld	a,#7
	wcentry
	procret
__endasm;
}
