#include <wcplugin.h>
#include <wcpluginsp.h>

uint8_t wcMKFILE(void* wcmkfileentry)__naked{
	wcmkfileentry;
__asm;
	iy_init
	get_hl
	ld	a,#72
	wcentry
	;
	ld	l,a
	procretnz
	;
	ld	l,#00
	;
	ret
__endasm;
}
