#include <stdint.h>
#include <conio.h>
#include <cp866-8x8.h>

#include "keyidle.h"

extern uint8_t start_type;

int main(){
	// Enable interrupt
    EI();
    //
    conio_set_font(cp866_8x8);
	ccls(006);
	print("- ZX-Phoenix SROM (C) 2022 -\n");
	
    switch( start_type ) {
        case 0:
            print("Hard start from 0000");
        break;
        case 1:
            print("Hot start from 0000");
        break;
    }


	//
	while(1){
    uint16_t k=0;
		//
		k = iGetChar();
		if(k) {
			conio_at(0,3);
			putchar(k);
		}
	}
	//
	return 0;
}
