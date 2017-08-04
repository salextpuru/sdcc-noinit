#include <window.h>
#include <im2.h>
#include <zxkbd.h>


window w1;

extern uint8_t		modes;

int main(int argc, char* argv[]){
	setScrDriverZX();
	
	/*
	txt_screen_driver->puts("Init ", 0);
	window_init(&w1);
	txt_screen_driver->puts("Win init ", 0);
	window_exec(&w1);
	txt_screen_driver->puts("Executed ", 0);
	window_destructor(&w1);
	txt_screen_driver->puts("Exit ", 0);
	*/

	txt_screen_driver->puts("Init ", 0);
	txt_screen_driver->cur_x=0;
	txt_screen_driver->cur_y=3;
	txt_screen_driver->puts("Symbol:",0);
	txt_screen_driver->cur_x=0;
	txt_screen_driver->cur_y=4;
	txt_screen_driver->puts("Caps:",0);
	txt_screen_driver->cur_x=0;
	txt_screen_driver->cur_y=5;
	txt_screen_driver->puts("Lang:",0);
	
	txt_screen_driver->cur_x=8;
	SEI();
	while(1){
		uint16_t k;
		
		waitINTS(1);
		scanINT();
		
		k=zxInKey();
		if(k){
			
			txt_screen_driver->cur_y=3;
			txt_screen_driver->putc(k);
		}
		txt_screen_driver->cur_y=4;
		txt_screen_driver->putc(zxIsCaps()+'0');
		txt_screen_driver->cur_y=5;
		txt_screen_driver->putc(zxIsRus()+'0');
	}
	
	
	return 0;
}
