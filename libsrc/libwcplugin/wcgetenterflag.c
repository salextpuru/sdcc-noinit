#include <wcplugin.h>
#include <wcpluginsp.h>

uint8_t wcGetEnterFlag()__naked{
__asm;
	ld	a,(wcheaderstart+05)
	ld	l,a
	ret
__endasm;
}
