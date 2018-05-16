#include "so.h"

void* soReloc(void* load_adr){
	uint8_t* code = (uint8_t*)load_adr;
	soHeader* h = (soHeader*)load_adr;
	uint16_t* reloc = (uint16_t*) (code + h->reloctbl_offset);
	uint16_t len = *(reloc++);
	void (*init)() = (void*) (code +sizeof(soHeader));

	while( len-- ){
		uint16_t* w= (uint16_t*)(code + *(reloc++));
		*w = *w + (uint16_t)load_adr;
	}
	
	init();
	
	return code + ((soHeader*)(load_adr))->reloctbl_offset;
}
