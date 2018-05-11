/**
 * mm128.с - менеджер памяти ZX128
 */
#include <string.h>
#include "mm128.h"

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
static uint16_t MMgetPagesCount() {
	return 8;
}

static uint8_t MMGetPageFlags(uint16_t page) {
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
	copy_0x7FFD = (copy_0x7FFD & ~7) |  (page&7);
	conf_apply();
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
}

static const memman_f mm128_funct= {
	// RAM
	.MMgetPagesCount = MMgetPagesCount,
	.MMGetPageFlags = MMGetPageFlags,
	.MMSetPageWin = MMSetPageWin,
	// ROM
	.MMgetPagesCountROM = MMgetPagesCountROM,
	.MMSetPageWinROM = MMSetPageWinROM
};

static const mm_win_d	memwins[MEM_WINS] = {
	{0, MWF_ROM, 0},	// ПЗУ, страница 0 (128)
	{5, MWF_FIXED, 0},	// ОЗУ, страница 5, несменяема
	{2, MWF_FIXED, 0},	// ОЗУ, страница 2, несменяема
	{0, 0, 0}		// ОЗУ, страница 0 (Переключаема)
};

void mm128_Init() {
	mm_win_d* wins=__MMgetMemWinsD();
	memcpy(wins,&memwins,sizeof(memwins));
	mm_func = &mm128_funct;
	conf_apply();
}
