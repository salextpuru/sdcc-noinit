#include "pt3xplayer.h"

void pt3Init(void* mod_adress)__naked{
__asm;
	ld	hl,#2
	add	hl,sp
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	inc	hl
	
	ex de,hl
	
	push	ix
	call pt3xplayer_init+3
	pop	ix
	ret
__endasm;
}

void pt3Play()__naked{
__asm;
	push	ix
	call 	pt3xplayer_init+5
	pop	ix
	ret
__endasm;
}

void pt3Mute()__naked{
__asm;
	push	ix
	call pt3xplayer_init+8
	pop	ix
	ret
__endasm;
}

void pt3SetMode(char mode)__naked{
__asm;
	ld	hl,#2
	add	hl,sp
	ld	a,(hl)
	ld (pt3xplayer_init+10),a
	ret
__endasm;
}

char pt3GetMode()__naked{
__asm;
	ld a,(pt3xplayer_init+10)
	ld l,a
	ret
__endasm;
}
