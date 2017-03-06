#include <wcplugin.h>
#include <wcpluginsp.h>

void wcADIR(uint8_t mode)__naked{
	mode;
__asm;
	iy_init
	get_a
	ex	af,af';'
	ld	a,#56
	wcentry
	procret
__endasm;
}
