#include "conio.h"

void print(const char* s)__naked{
s;
__asm;
	ld	hl,#2
	add	hl,sp
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	inc	hl
	
	ex de,hl

print_loop:
	ld	a,(hl)
	or	a
	ret	z
	call	_putchar_a
	inc	hl
	jr	print_loop
	
__endasm;
}

void conio_at(uint8_t x, uint8_t y){

	extern uint8_t	cur_x;
	extern uint8_t	cur_y;

	cur_x=x;
	cur_y=y;
}

void conio_where(uint8_t* x, uint8_t* y){
	extern uint8_t	cur_x;
	extern uint8_t	cur_y;

	*x=cur_x;
	*y=cur_y;
}

// Putc must be emulate AT, INK, PAPER

// Buffer for params
//uint8_t _putc_ctl_buf[0x04];

// Counter of params
//uint8_t _putc_ctl_count;

// Command (SYM_AT, SYM_INK, SYM_PAPER)
//uint8_t _putc_ctl_code;
