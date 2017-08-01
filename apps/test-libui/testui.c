#include <scrfunc.h>

int main(int argc, char* argv[]){
	txt_screen_driver=&scrDriver_ZX;
	 
	txt_screen_driver->setcolor(6,8);
	txt_screen_driver->clear_window(0,0,16,12);
	txt_screen_driver->curpos(0,0);
	txt_screen_driver->putc('A');
	
	txt_screen_driver->setcolor(4,16);
	txt_screen_driver->clear_window(16,0,16,12);
	txt_screen_driver->curpos(16,0);
	txt_screen_driver->putc('B');
	
	txt_screen_driver->setcolor(2,32);
	txt_screen_driver->clear_window(0,12,16,12);
	txt_screen_driver->curpos(0,12);
	txt_screen_driver->putc('C');
	
	txt_screen_driver->setcolor(0,56);
	txt_screen_driver->clear_window(16,12,16,12);
	txt_screen_driver->curpos(16,12);
	txt_screen_driver->putc('D');
	
	while(1);
	return 0;
}
