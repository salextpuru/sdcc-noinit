#include <window.h>
#include <im2.h>
#include <zxkbd.h>


window w1;


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
	SEI();
	while(1){
		uint16_t k;
		
		waitINTS(1);
		scanINT();
		
		k=zxInKey();
		if(k){
			txt_screen_driver->putc(k);
		}
	}
	
	
	return 0;
}
