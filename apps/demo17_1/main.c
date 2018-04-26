#include <types.h>
#include <stdint.h>
#include <spr0.h>
#include <im2.h>

int main() {
	uint8_t pix=1;
	spr0_set_scr_adr(0x6000);
	scr0_fill_atr(7);

	while (1) {
		scr0_fill_pix(pix);
		scr0_flip4000();
		pix+=pix;
		if(!pix){
			pix=1;
		}
	}
	//
	return 0;
}
