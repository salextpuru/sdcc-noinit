#include <types.h>
#include "koi8r-8x8.h"

// Адрес экрана из	0x0000, 0x4000, 0x8000, 0xC0000
//			0x2000, 0x6000, 0xA000, 0xE0000
uint16_t	screen_adr=0x4000;

// Адрес шрифта
uint8_t*	font=koi8r_8x8;

// Координаты курсора
uint8_t	cur_x;
uint8_t	cur_y;

void conio_set_scr_adr(uint16_t adr){
	screen_adr=adr;
}
