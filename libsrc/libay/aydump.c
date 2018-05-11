/**
    @file aydump.c - Получить значение регистров муз. сопроцессора.
*/
#include "aydump.h"

// Порт AY8910/12
static uint16_t ayPort=0xFFFD;

const uint8_t ayDump[AY_READING_REGS];

void ayDumpGet() __naked {
	__asm;
	ld	e,#0x00 ; // Номер регистра
	ld	hl,#_ayDump ; // Адрес массива
	ld	bc,(_ayPort) ;// #FFFD - регистр адреса #BFFD - регистр данных
	ay_dump_loop1:
	;//
	ld	a,e
	out	(c),a
	in	a,(c)
	and	a,#0x0F
	ld	(hl),a
	;//
	inc	hl
	inc	e
	ld	a,#AY_READING_REGS
	cp	a,e
	jr	nz, ay_dump_loop1
	ret
	__endasm;
}
