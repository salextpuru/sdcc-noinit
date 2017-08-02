#include <scrfunc.h>
#include <im2.h>

uint8_t buf_blob_0[16*12*9 + sizeof(scrDriverStored)];
uint8_t buf_blob_1[16*12*9 + sizeof(scrDriverStored)];
uint8_t buf_blob_2[16*12*9 + sizeof(scrDriverStored)];
uint8_t buf_blob_3[16*12*9 + sizeof(scrDriverStored)];

int main(int argc, char* argv[]){
	#define buf0 ((scrDriverStored*)buf_blob_0)
	#define buf1 ((scrDriverStored*)buf_blob_1)
	#define buf2 ((scrDriverStored*)buf_blob_2)
	#define buf3 ((scrDriverStored*)buf_blob_3)

	setScrDriverZX();
	
	// clear all screen
	txt_screen_driver->setcolor(7,0);
	txt_screen_driver->clear_window(0,0,32,24);
	//
	txt_screen_driver->setcolor(6,8);
	txt_screen_driver->clear_window(0,0,16,12);
	txt_screen_driver->curpos(2,2);
	txt_screen_driver->puts("Синий фон",16);
	txt_screen_driver->border(btSingl, 0,0,16,12);
	txt_screen_driver->store_window(buf0, 0,0,16,12);
	
	txt_screen_driver->setcolor(4,16);
	txt_screen_driver->clear_window(16,0,16,12);
	txt_screen_driver->curpos(18,2);
	txt_screen_driver->puts("Красный фон",16);
	txt_screen_driver->border(btDoubl, 16,0,16,12);
	txt_screen_driver->store_window(buf1, 16,0,16,12);
	
	txt_screen_driver->setcolor(2,32);
	txt_screen_driver->clear_window(0,12,16,12);
	txt_screen_driver->curpos(2,14);
	txt_screen_driver->puts("Зеленый фон",16);
	txt_screen_driver->border(btSingl, 0,12,16,12);
	txt_screen_driver->store_window(buf2, 0,12,16,12);

	txt_screen_driver->setcolor(0,56);
	txt_screen_driver->clear_window(16,12,16,12);
	txt_screen_driver->curpos(18,14);
	txt_screen_driver->puts("Белый фон",16);
	txt_screen_driver->border(btDoubl, 16,12,16,12);
	txt_screen_driver->store_window(buf3, 16,12,16,12);
	
	SEI();
	while(1){
		uint8_t x;
		uint8_t y;
		// Swap loop
		x=buf0->x;
		y=buf0->y;
		//
		buf0->x=buf1->x;
		buf0->y=buf1->y;
		//
		buf1->x=buf2->x;
		buf1->y=buf2->y;
		//
		buf2->x=buf3->x;
		buf2->y=buf3->y;
		//
		buf3->x = x;
		buf3->y = y;
		//
		waitINTS(12);
		txt_screen_driver->restore_window(buf0);
		waitINTS(12);
		txt_screen_driver->restore_window(buf1);
		waitINTS(12);
		txt_screen_driver->restore_window(buf2);
		waitINTS(12);
		txt_screen_driver->restore_window(buf3);
		//
	}
	return 0;
}
