#include <stdint.h>
#include <wckeyfunc.h>
#include <wcpluginsp.h>

uint8_t	wcKeyFunc(uint8_t func_num)__naked{
	func_num;
__asm;
	iy_init
	;// get func number
	get_a
	wcentry
	ld	l,#1
	;// if Z return 1 (key pressed)
	procretnz ;// RESTORE iy
	;// if NZ return 0 (key unpressed)
	ld	l,#0
	ret
__endasm;
}

uint8_t wcKbScan(uint8_t table)__naked{
	table;
__asm;
	iy_init
	;// upd status
	push	iy
	ld	a,#0xFC
	ex	af,af';'
	ld	a,#9
	wcentry
	pop	iy
	;// get table mode
	get_a
	ex	af,af';'
	ld	a,#42
	wcentry
	ld	l,#0
	procretz ;// RESTORE iy. No key or error ret(0)
	ld	l,a
	ret		;// Key Code
__endasm;
}
