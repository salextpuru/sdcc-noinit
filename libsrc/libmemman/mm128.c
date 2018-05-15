/**
 * mm128.с - менеджер памяти ZX128
 */
#include <string.h>
#include "memman.h"

#define RAMPAGES 8
#define ROMPAGES 2

// Описатели всех страниц
static uint8_t pages128[RAMPAGES]={
	3,3,
	3 | MPG_FIXED|MPG_BUSY, // Страница 2 (0x8000 - 0xBFFF)
	3,3,
	3 | MPG_FIXED|MPG_BUSY, // Страница 5 (0x4000 - 0x7FFF)
	3,3
};

// Копия порта конфигурации спека 128
static uint8_t copy_0x7FFD;
static void conf_apply() __naked {
	__asm;
	ld	bc,#0x7FFD
	ld	a, ( _copy_0x7FFD )
	out	( c ),a
	ret
	__endasm;
}

// RAM
uint16_t MMgetPagesCount() {
	return RAMPAGES;
}

uint8_t MMGetPageFlags ( uint16_t page ) {
	if ( page>=RAMPAGES ) {
		return MME_ABSENT;
	}
	return pages128[page];
}

uint8_t MMSetPageFlags(uint16_t page, uint8_t flags) {
	if ( page>=RAMPAGES ) {
		return MME_ABSENT;
	}
	pages128[page] = flags;
	return MME_OK;
}

uint8_t MMSetPageWin ( uint16_t page, uint8_t win ) {
	if ( win!=3 ) {
		return MME_WFIXED;
	}

	if ( page>=RAMPAGES ) {
		return MME_ABSENT;
	}

	__MMgetMemWinsD() [3].page = page;
	copy_0x7FFD = ( copy_0x7FFD & 0xF8 ) | ( page&0x07 );
	conf_apply();
	return MME_OK;
}

// ROM
uint16_t MMgetPagesCountROM() {
	return ROMPAGES;
}

uint8_t MMSetPageWinROM ( uint16_t page, uint8_t win ) {
	if ( win!=0 ) {
		return MME_WFIXED;
	}

	if ( page>=ROMPAGES ) {
		return MME_ABSENT;
	}

	__MMgetMemWinsD() [0].page = page;

	copy_0x7FFD = ( page==0 ) ? copy_0x7FFD&~0x10:copy_0x7FFD|0x10;

	conf_apply();
	return MME_OK;
}

uint8_t MMgetFreePage(uint16_t* page) {
	uint8_t i;
	if( !page ){
		return MME_ABSENT;
	}
	for(i=0; i<RAMPAGES;i++){
		if( pages128[i] & MPG_FIXED ){
			continue;
		}
		if(( pages128[i] & MPG_BUSY ) == 0){
			*page = i;
			return MME_OK;
		}
	}
	return MME_ABSENT;
}

uint8_t MMuseFreePage(uint16_t* page) {
	if( MMgetFreePage( page ) == MME_OK ){
		pages128[*page] |= MPG_BUSY;
		return MME_OK;
	}
	return MME_ABSENT;
}

uint8_t MMfreePage(uint16_t page) {
	if ( page>=RAMPAGES ) {
		return MME_ABSENT;
	}
	
	if( pages128[page] & MPG_FIXED ) {
		return MME_PFIXED;
	}
	
	if( pages128[page] & MPG_BUSY ) {
		pages128[page] &=~MPG_BUSY;
		return MME_OK;
	}
	return MME_FREE;
}

static const mm_win_d	memwins128[MEM_WINS] = {
	{1, MWF_ROM | MWF_EROM | MWF_WIN0, 0},	// ПЗУ, страница 1 (48) ROM может переключаться
	{5, MWF_FIXED | MWF_WIN1, 0},		// ОЗУ, страница 5, несменяема
	{2, MWF_FIXED | MWF_WIN2, 0},		// ОЗУ, страница 2, несменяема
	{0, MWF_ERAM  | MWF_WIN3, 0}		// ОЗУ, страница 0 (Переключаема)
};

void MMInit() {
	// Копируем начальную конфигурацию
	memcpy ( __MMgetMemWinsD(),&memwins128,sizeof ( memwins128 ) );
	MMSetPageWinROM ( __MMgetMemWinsD() [0].page,0 );
	MMSetPageWin ( __MMgetMemWinsD() [3].page,3 );
}
