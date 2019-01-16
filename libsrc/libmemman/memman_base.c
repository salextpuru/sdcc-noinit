/**
 * @file memman.c - базовые типы управления памятью
 */
#include "memman.h"

#ifndef NAKED
#define NAKED
#endif

// Это объединение только для преобразования адресов
typedef union {
	// Длинный адрес
	mm_far_ptr	far_ptr;
	// Короткий адрес и страница
	struct {
		uint16_t	memadr;
		uint16_t	page;
	}adr;
} ufar_ptr;

uint16_t getPage(mm_far_ptr p)  {
	return ((ufar_ptr*)&p)->adr.page;
}

uint16_t getShortAdr(mm_far_ptr p) {
	return ((ufar_ptr*)&p)->adr.memadr;
}

uint16_t getPAdr(mm_far_ptr p) {
	return (((ufar_ptr*)&p)->adr.memadr) & 0x3FFF;
}

uint8_t getWinMask(mm_far_ptr p) NAKED {
	p;
__asm;
	ld	hl,#0x0003 ;// SP+3 = PAGE hi byte
	add	hl,sp
	ld	a,#0xC0	   ;// MASK (bits 7,6)
	and	a, (hl)
	ld	l,a
	ret
__endasm;
}

uint8_t getWin(mm_far_ptr p) NAKED {
	p;
__asm;
	ld	hl,#0x0003 ;// SP+3 = PAGE hi byte
	add	hl,sp
	ld	a,#0xC0	   ;// MASK (bits 7,6)
	and	a, (hl)
	rlca		;// 7,6 -> 1,0
	rlca
	ld	l,a
	ret
__endasm;
}

uint32_t getLongAdr(uint16_t shortadr, uint16_t page) NAKED {
	page;shortadr;
__asm;
	pop bc ;// ret
	pop hl ;// shortadr
	pop de ;// page
	push de
	push hl
	push de
	ret
__endasm;
}
