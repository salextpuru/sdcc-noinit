#include <wcplugin.h>
#include <wcpluginsp.h>

uint8_t wcSTREAM(uint8_t mode, uint8_t part, uint8_t dev)__naked{
	mode;
__asm;
	iy_init
	; 
	get_a
	ld	d,a
	;
	get_bc
	;
	ld	a,#0xFE
	cp	b
	jr	c,wcstream_c1
	ld 	c,b
wcstream_c1:
	;
	ld	a,#57
	wcentry
	;
	ld	l,#0
	procretz
	ld	l,#0xFF
	ret
__endasm;
}
