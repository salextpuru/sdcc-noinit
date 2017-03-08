#include <wcplugin.h>
#include <wcpluginsp.h>

uint8_t wcMKDIR(const char* name)__naked{
	name;
__asm;
	iy_init
	get_hl
	ld	a,#73
	wcentry
	ld	l,#00
	procretz
	ld	l,a
__endasm;
}
