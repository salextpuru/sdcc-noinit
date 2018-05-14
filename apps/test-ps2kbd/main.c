#include <window.h>
#include <ps2.h>
#include <koi8r-8x8.h>

void at(uint8_t x, uint8_t y){
	txt_screen_driver->cur_x=x;
	txt_screen_driver->cur_y=y;
}

void cls(){
	txt_screen_driver->ink=006; // Octal system is very good for ZX colors:)
	txt_screen_driver->paper=010; // Octal system is very good for ZX colors:)
	txt_screen_driver->clear_window(0,0,txt_screen_driver->w,txt_screen_driver->h);
}

void putsat(uint8_t x, uint8_t y, const char* s){
	at(x,y);
	txt_screen_driver->puts(s, 0);
}

void putc(const char c){
	txt_screen_driver->putc(c);
}

void main(){
	setScrDriverZX();
	current_font = koi8r_8x8;
	//
	cls();
	putsat(0,0,"PS2 keyboard driver test.");
	//
	ps2Init();
	//
	while(1){
		uint8_t k = ps2InKey();
		
		putsat(0,2,"Symbol:");
		if(k){
			at(9,2);putc(k);
		}
		
		putsat(0,4,"Caps lock: ");putsat(11,4, ps2IsCaps()?"On ":"Off");
		putsat(0,5,"Language:  ");putsat(11,5, ps2IsRus()?"Rus":"Lat");
		
		putsat(0,6,"Caps shift:");putsat(11,6, ps2IsSHIFT()?"On ":"Off");
		putsat(0,7,"CTRL (SS): ");putsat(11,7, ps2IsCTRL()?"On ":"Off");
		putsat(0,8,"ALT      : ");putsat(11,8, ps2IsALT()?"On ":"Off");
	}
}
