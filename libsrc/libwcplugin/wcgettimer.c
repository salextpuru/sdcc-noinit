#include <wcplugin.h>
#include <wcpluginsp.h>

uint16_t wcGetTimer()__naked{
__asm;
	ld	hl,(wcheaderstart+9)
	ret
__endasm;
}
