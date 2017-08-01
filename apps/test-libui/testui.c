#include <scrfunc.h>

int main(int argc, char* argv[]){
	txt_screen_driver=&scrDriver_ZX;
	
	txt_screen_driver->setcolor(0,8);
	txt_screen_driver->clear_window(0,0,16,12);
	
	txt_screen_driver->setcolor(0,16);
	txt_screen_driver->clear_window(16,0,16,12);
	
	txt_screen_driver->setcolor(0,32);
	txt_screen_driver->clear_window(0,12,16,12);
	
	txt_screen_driver->setcolor(0,56);
	txt_screen_driver->clear_window(16,12,16,12);
	
	
	while(1);
	return 0;
}
