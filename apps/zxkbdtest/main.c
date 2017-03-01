#include <types.h>
#include <im2.h>
#include <conio.h>
#include <zxcolor.h>

void kbd_scan();

extern uint8_t scan_codes[];
extern uint8_t scan_timers[];

// Начало
void main(){
	CLI();
	ccls( ATTRN(YELLOW,BLACK) );
	im2SetHandler(kbd_scan);
	im2Set();
	SEI();
	while(1){
		uint8_t i;
		conio_at(5,5);
		printf("Scan:\n");
		for(i=0; i<=7; i++){
			printf("%.2X ",scan_codes[i]);
		}
	}
}
