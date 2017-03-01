#include <wcplugin.h>
#include <wcpluginsp.h>

void	wcMNGCPL(uint8_t page)__naked{
	page;
__asm;
	iy_init
	get_a
	ex	af,af' ; '
	xor	a
	wcentry
	procret
__endasm;
}
