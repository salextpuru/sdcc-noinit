#include <scrfunc.h>

int main(int argc, char* argv[]){
	txt_screen_driver=&scrDriver_ZX;
	// clear all screen
	txt_screen_driver->setcolor(7,0);
	txt_screen_driver->clear_window(0,0,32,24);
	//
	 
	txt_screen_driver->setcolor(6,8);
	txt_screen_driver->clear_window(0,0,16,12);
	txt_screen_driver->curpos(0,0);
	txt_screen_driver->puts("The blue paper",16);
	
	txt_screen_driver->setcolor(4,16);
	txt_screen_driver->clear_window(16,0,16,12);
	txt_screen_driver->curpos(16,0);
	txt_screen_driver->puts("The red paper",16);
	
	txt_screen_driver->setcolor(2,32);
	txt_screen_driver->clear_window(0,12,16,12);
	txt_screen_driver->curpos(0,12);
	txt_screen_driver->puts("The green paper",16);
	
	txt_screen_driver->setcolor(0,56);
	txt_screen_driver->clear_window(16,12,16,12);
	txt_screen_driver->curpos(16,12);
	txt_screen_driver->puts("The white paper",16);
	
	while(1);
	return 0;
}
