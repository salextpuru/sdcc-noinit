#include <types.h>

// Адрес экрана из	0x0000, 0x4000, 0x8000, 0xC000
//			0x2000, 0x6000, 0xA000, 0xE000
uint16_t	screen_adr=0x4000;

// Адрес шрифта (по умолчанию - стандартный спектрум)
uint8_t*	font=(uint8_t*)0x3C00;

// Координаты курсора
uint8_t	cur_x;
uint8_t	cur_y;

void conio_set_scr_adr(uint16_t adr){
	screen_adr=adr;
}

void conio_set_font(void* f) {
	font = f;
}