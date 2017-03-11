#include <wcplugin.h>
#include <wcpluginsp.h>

uint8_t wcRENAME(void* wcentry, const char* new_name)__naked{
	wcentry;
__asm;
	iy_init
	;// get adress of buffer
	;// pointer to &(wcENTRY.flag)
	get_hl
	ld	de,#0x0008
	add	hl,de
	;// get DE - new_name
	get_de
	;//
	ld	a,#74
	wcentry
	;// error if Z, return error code
	ld	a,l
	procretz
	;// no errors, return 0
	xor	a 
	ld	l,a
	ret
__endasm;
}
