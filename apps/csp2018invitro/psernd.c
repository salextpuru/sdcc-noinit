#include "psernd.h"

static const uint16_t rndnext=0x6AE7;

uint16_t rnd16() __naked {
__asm;
	ld    hl,(_rndnext)
	ld    a,h
	add   hl,hl
	xor   h
	add   hl,hl
	add   hl,hl
	add   hl,hl
	xor   h
	add   hl,hl
	add   hl,hl
	xor   h
	add   hl,hl
	add   hl,hl
	ld    l,a
	ld    (_rndnext),hl
	ret
__endasm;
}
