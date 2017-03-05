#include <wcplugin.h>
#include <wcpluginsp.h>

void	wcGEDPL()__naked{
__asm;
	iy_init
	ld a,#15
	wcentry
	procret
__endasm;
}
