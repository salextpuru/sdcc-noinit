#include "conio.h"

void print(const char* s)__naked{
	s;
__asm;
	ld	hl,#2
	add	hl,sp
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	ex de,hl	;// hl = s

print_loop:
	ld	a,(hl)
	or	a
	ret	z
	call	_putchar_a
	inc	hl
	jr	print_loop
	
__endasm;
}

void nprint(const char* s, uint8_t strsize)__naked{
	s;strsize;
__asm;
	ld	hl,#2
	add	hl,sp
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	inc	hl	;// hl = s
	ld	b,(hl)	;// b = strsize
	ld	c,#0	;// char counter
	ex de,hl

nprint_loop:
	ld	a,(hl)
	or	a
	ret	z	;// exit \0
	push	bc
	call	_putchar_a
	pop	bc
	inc	hl
	inc	c
	djnz	nprint_loop
	ret		;// exit strsize
__endasm;
}

void nprintspc(const char* s, uint8_t strsize)__naked{
	s;strsize;
__asm;
	ld	hl,#2
	add	hl,sp
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	inc	hl	;// hl = s
	ld	b,(hl)	;// b = strsize
	ld	c,#0	;// char counter
	ex de,hl
	;
	push	bc
	call	nprint_loop
	ld	a,c
	pop	bc
	sub	b
	neg
	ld	b,a	;// b=strsize-strlen(s)
	;// print b spaces
nprintspc_loop:
	push	bc
	ld	a,#0x20
	call	_putchar_a
	pop	bc
	djnz	nprintspc_loop
	ret		;// exit strsize
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
