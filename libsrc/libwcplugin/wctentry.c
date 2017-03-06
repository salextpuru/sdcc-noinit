#include <wcplugin.h>
#include <wcpluginsp.h>

void wcTENTRY(void* tentry)__naked{
	tentry;
__asm;
	iy_init
	get_de
	ld	a,#51
	wcentry
	procret
__endasm;
}
