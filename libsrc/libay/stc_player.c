#include "stc_player.h"

void stcInit(void* mod_adress)__naked{
__asm;
	ld	hl,#2
	add	hl,sp
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	inc	hl
	
	ex de,hl

	jp stc_init_entry
__endasm;
}


void stcSetMode(char mode)__naked{
__asm;
	ld	hl,#2
	add	hl,sp
	ld	a,(hl)
	ld	(stc_flags),a
	ret
__endasm;
}

char stcGetMode()__naked{
__asm;
	ld a,(stc_flags)
	ld l,a
	ret
__endasm;
}