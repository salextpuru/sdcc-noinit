/**
 * Обработка загруженных модулей (перемещение и проч.)
 */
#include <stdio.h>
#include "so.h"

void* soReloc(void* load_adr){
	uint8_t* code = (uint8_t*)load_adr;
	soHeader* h = (soHeader*)load_adr;
	uint16_t* reloc = (uint16_t*) (code + h->reloctbl_offset);
	uint16_t len = *(reloc++);
	void (*init)() = (void*) (code +sizeof(soHeader));

	while( len-- ){
		uint8_t* w= code + *(reloc++);
		*w = *w + (((uint16_t)load_adr) >> 8);
	}
	
	init();
	
	// Заголовок тоже привязывается к абсолютным адресам
	return h->reloctbl_offset;
}
