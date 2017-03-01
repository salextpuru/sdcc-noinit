#include <wcplugin.h>
#include <wcpluginsp.h>

void	wcMNG0PL(uint8_t page)__naked{
	page;
__asm;
	iy_init
	get_a
	ex	af,af' ; '
	ld	a,#78
	wcentry
	procret
__endasm;
}
