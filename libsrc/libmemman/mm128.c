/**
 * mm128.с - менеджер памяти ZX128
 */
#include <string.h>
#include "memman.h"

#define RAMPAGES 8
#define ROMPAGES 2

// Описатели всех страниц
static uint8_t pages128[RAMPAGES];

// Копия порта конфигурации спека 128
static uint8_t copy_0x7FFD;
static void conf_apply()__naked {
	__asm;
	ld	bc,#0x7FFD
	ld	a,(_copy_0x7FFD)
	out	(c),a
	ret
	__endasm;
}

// RAM
uint16_t MMgetPagesCount() {
	return 8;
}

uint8_t MMGetPageFlags(uint16_t page) {
	return pages128[page&7];
}

uint8_t MMSetPageWin(uint16_t page, uint8_t win) {
	if ( win!=3 ) {
		return MME_WFIXED;
	}

	if ( page>7 ) {
		return MME_ABSENT;
	}

	__MMgetMemWinsD()[3].page = page;
	copy_0x7FFD = (copy_0x7FFD & 0xF8) |  (page&0x07);
	conf_apply();
	return MME_OK;
}

// ROM
uint16_t MMgetPagesCountROM() {
	return 2;
}

uint8_t MMSetPageWinROM(uint16_t page, uint8_t win) {
	if ( win!=0 ) {
		return MME_WFIXED;
	}

	if ( page>1 ) {
		return MME_ABSENT;
	}

	__MMgetMemWinsD()[0].page = page;

	copy_0x7FFD = (page==0)? copy_0x7FFD&~0x10:copy_0x7FFD|0x10;

	conf_apply();
	return MME_OK;
}

static const mm_win_d	memwins[MEM_WINS] = {
	{1, MWF_ROM | MWF_EROM, 0},	// ПЗУ, страница 1 (48) ROM может переключаться
	{5, MWF_FIXED, 0},		// ОЗУ, страница 5, несменяема
	{2, MWF_FIXED, 0},		// ОЗУ, страница 2, несменяема
	{0, MWF_ERAM, 0}		// ОЗУ, страница 0 (Переключаема)
};

void MMInit() {
	// Копируем начальную конфигурацию
	memcpy(__MMgetMemWinsD(),&memwins,sizeof(memwins));
	MMSetPageWinROM(__MMgetMemWinsD()[0].page,0);
	MMSetPageWin(__MMgetMemWinsD()[3].page,3);
}
