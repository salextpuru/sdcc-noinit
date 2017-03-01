#include <wcplugin.h>
#include <wcpluginsp.h>

uint8_t	wcYNMENU(uint8_t mode)__naked{
__asm;
	iy_init
	get_a
	ex	af,af' ; '
	ld	a,#8
	wcentry
	ld	l,#1
	;// if Z return 1 (OK)
	;// IY restore from stack here!
	procretz
	;// if NZ return 0 (CANCEL)
	ld	l,#0
	ret
__endasm;
}
