#include <stdint.h>
#include <conio.h>
#include <cp866-8x8.h>
#include <zxkbd.h>

// Interrupt handler
void irq38() {
	zxKbdScan();
}

void main(){
	conio_set_font(cp866_8x8);
	ccls(006);
	print("- ZX-Phoenix SROM (C) 2022 -");
	
	// Enable interrupt
	__asm;
	im 0
	ei
	__endasm;
	//
	while(1){
		uint16_t k=0;
		//
		k = zxKbdInKey() & 0xFF;
		if(k) {
			conio_at(0,3);
			putchar(k);
		}
	}
}
