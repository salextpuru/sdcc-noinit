#include <wcplugin.h>
#include <wcpluginsp.h>

uint8_t wcFINDNEXT(void* wcentry, uint8_t mode)__naked{
	mode;
__asm;
	iy_init
	;//
	get_de
	;//
	get_a
	;// Enable long names,
	;// time field[4],
	;// date field[3],
	;// size field[2]
	or	#0x1C
	ex	af,af';'
	ld	a,#58
	wcentry
	ld	l,#0x00
	procretnz
	ld	l,#0xFF
	ret
__endasm;
}
