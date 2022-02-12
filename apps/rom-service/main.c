#include <stdint.h>
#include <conio.h>
#include <koi8r-8x8.h>
#include <zxkbd.h>

// Interrupt handler
void irq38() {
	zxKbdScan();
}

void main(){
	conio_set_font(koi8r_8x8);
	ccls(006);
	
	print("ZX-Phoenix");
	
	// Enable interrupt
	__asm;
	im 0
	ei
	__endasm;
	//
	while(1){
		uint16_t k=0;
		//
		__asm;
		di
		__endasm;
		k = zxKbdInKey() & 0xFF;
		__asm;
		ei
		__endasm;
		
		if(k) {
			//conio_at(0,3);
			putchar(k);
		}
	}
}
