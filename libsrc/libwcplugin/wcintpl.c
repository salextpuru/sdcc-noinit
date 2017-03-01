#include <wcplugin.h>
#include <wcpluginsp.h>

void wcINTPL(uint8_t mode, void* int_handler)__naked{
	mode;int_handler;
__asm;
	iy_init
	get_a
	get_hl
	ex	af,af' ; '
	ld	a,#86
	wcentry
	procret
__endasm;
}
