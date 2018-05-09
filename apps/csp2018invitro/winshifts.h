/**
 * @file winshifts.h - Сдвиг окон во все стороны
 */
#ifndef __WINSHIFTS_H__
#define __WINSHIFTS_H__
#include <stdint.h>

/**
* @brief Описание окна (знакоместа)
*/
typedef struct {
	uint8_t x;
	uint8_t y;
	uint8_t w;
	uint8_t h;
}winShift;

/**
* @brief Сдвиг влево на пиксель
*/
void shiftLeftPix(const winShift* w);

#endif /* __WINSHIFTS_H__ */
