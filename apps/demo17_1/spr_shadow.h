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

#endif /* __SPR_SHADOW_H__ */
