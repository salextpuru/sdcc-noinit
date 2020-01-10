/**
 * @file memman.c - базовые типы управления памятью
 */
#include "memman.h"
 
/**
* @brief описатели окон памяти
*	0 - 0x0000 ... 0x3FFF 
* 	1 - 0x4000 ... 0x7FFF 
* 	2 - 0x8000 ... 0xBFFF 
* 	3 - 0xC000 ... 0xFFFF 
*/
static mm_win_d	memwins[MEM_WINS];

// Вспомогачка на асмочке
static void helper() __naked {
__asm;
;// Снять байт со стека (номер страницы)
;// Вызывается из С-функции
get_mm_win_d_adr:
	ld	hl,#4 ;// SP: retadr(2) retadr(2) w(1)
	add	hl,sp
	push	de
	;// de=w
	ld	e,(hl)
	ld	d,#0
	;// de=_memwins hl=w
	ld	hl,#_memwins
	ex	de,hl
	;// hl=w*4+_memwins
	add	hl,hl
	add	hl,hl
	add	hl,de
	pop	de
	ret
__endasm;
}

//
mm_win_d* __MMgetMemWinsD()__naked{
__asm;
	ld	hl,#_memwins
	ret
__endasm;
}

//
uint16_t MMgetWinPage(uint8_t w) __naked {
	w;
__asm;
	;// hl = _memwins+w*4
	call	get_mm_win_d_adr
	;// hl = memwins[w].page
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	ex	de,hl
	
	ret
__endasm;
}

uint8_t MMgetWinFlags(uint8_t w) __naked {
	w;
__asm;
	;// hl = _memwins+w*4
	call	get_mm_win_d_adr
	;// HL = memwins[w].flags
	ld	de,#2
	add	hl,de
	ld	l,(hl)
	ret
__endasm;
}

const mm_win_d* MMgetWinD(uint8_t w)__naked{
	w;
__asm;
	;// hl = _memwins+w*4
	call	get_mm_win_d_adr
	ret
__endasm;
}
