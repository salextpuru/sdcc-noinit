#include <wcplugin.h>
#include <wcpluginsp.h>

uint8_t wcGetAbortFlag()__naked{
__asm;
	ld	a,(wcheaderstart+04)
	ld	l,a
	ret
__endasm;
}
