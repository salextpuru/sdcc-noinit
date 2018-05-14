/**
 * @file winprocs.h - windows clear,set attr and other
 * 
 */
#ifndef __WINPROCS_H__
#define __WINPROCS_H__

#include <stdint.h>

/**
* @brief Clear window with effect (pixel only)
*/
void winClear(uint8_t x, uint8_t y, uint8_t w, uint8_t h );

void winClearRnd(uint8_t x, uint8_t y, uint8_t w, uint8_t h );

/**
* @brief Set attributes. Set attrs in window as (attr & mask) | (wattr & ~mask).
* 	wattr - attr of current char in window
*
* @param attr p_attr - attr 
* @param mask p_mask - mask.
*/
void winSetAtr(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t attr, uint8_t mask );

/**
* @brief Получить атрибут знакоместа с координатами (x,y)
*/
uint8_t attrGet(uint8_t x, uint8_t y);

/**
* @brief Установить атрибут знакоместа с координатами (x,y)
*/
void	attrSet(uint8_t x, uint8_t y, uint8_t attr);

#endif /* __WINPROCS_H__ */
