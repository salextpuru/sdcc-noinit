/**
 * @file spr_shadow.h - Shadow screen functions
 */
#ifndef __SPR_SHADOW_H__
#define __SPR_SHADOW_H__

#include <stdint.h>

// Copy shadow to screen
void shsc_flip();

// set color
void shsc_set_color(uint8_t c);

// clear
void shsc_cls();

// return adress on shadow screen
uint8_t* shsc_adr(uint8_t x, uint8_t y);

// assembler
// in:	C - x
// 	B - y
// out:
//	HL - adress on shadow screen
void shsc_adr_asm();

// in:
// 	hl - source adr
// 	de - destination adr
//	c - width
//	b - heigh
void shsc_spr2scr_asm();

// assembler
// in:	C - x
// 	B - y
// out:
//	HL - attr adress on shadow screen
void shsc_atradr_asm();

// return adress on shadow screen
uint8_t* shsc_atradr(uint8_t x, uint8_t y);

// in:
// 	hl - attr adr in screen
// 	a  - color
//	c - width
//	b - heigh
void shsc_atr2scr_asm();

/**
* @brief Вывод спрайта
* 
* @param sprdata - адрес спрайта
* @param scradr - адрес теневого экрана
* @param w - ширина (знакоместа)
* @param h - высота (знакоместа)
*/
void shsc_spr2scr(void* sprdata, void* scradr, uint8_t w, uint8_t h );

/**
* @brief Закрасить атрибуты
* 
* @param color - цвет
* @param scradr - адрес на теневом экране
* @param w - ширина (знакоместа)
* @param h - высота (знакоместа)
*/
void shsc_atr2scr(uint8_t color, void* scradr, uint8_t w, uint8_t h);

void shsc_putmode();
void shsc_xormode();
void shsc_andmode();
void shsc_ormode();

#endif /* __SPR_SHADOW_H__ */
