#include <window.h>
#include <im2.h>
#include <zxkbd.h>
#include <stdio.h>
#include <koi8r-8x8.h>

void at(uint8_t x, uint8_t y){
	txt_screen_driver->cur_x=x;
	txt_screen_driver->cur_y=y;
}

void ncls(){
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

char s[0x10];
void main(){
	CLI();
	setScrDriverZX();
	current_font = koi8r_8x8;
	//
	ncls();
	putsat(0,0,"ZX keyboard driver test.");
	//
	im2SetHandler(zxKbdScan);
	im2Set();
	SEI();
	while(1){
		uint8_t k = zxKbdInKey();
		
		putsat(0,2,"Symbol:");
		if(k){
			at(9,2);putc(k);
			sprintf(s,"0x%.2X",k);
			putsat(12,2,s);
		}
		
		putsat(0,4,"Caps lock: ");putsat(11,4, zxKbdIsCaps()?"On ":"Off");
		putsat(0,5,"Language:  ");putsat(11,5, zxKbdIsRus()?"Rus":"Lat");
		
		putsat(0,6,"Caps shift:");putsat(11,6, zxKbdIsSHIFT()?"On ":"Off");
		putsat(0,7,"CTRL (SS): ");putsat(11,7, zxKbdIsCTRL()?"On ":"Off");
		putsat(0,8,"ALT      : ");putsat(11,8, zxKbdIsALT()?"On ":"Off");
		
		waitINTS(1);
	}
}
