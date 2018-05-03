/**
 * @file printscale.h - vertical scaled print
 */
#ifndef __PRINTSCALE_H__
#define __PRINTSCALE_H__

#include <stdint.h>

/**
* @brief print scaled char
* 
* @param x - X
* @param y - Y
* @param scale - scale (1..24)
* @param ch - char
*/
void printScale(uint8_t x, uint8_t y, uint8_t scale, uint8_t ch);

/**
* @brief print scaled char
* 
* @param x - X
* @param y - Y
* @param scale - scale (1..24)
* @param s - string
*/
void printStrScale(uint8_t x, uint8_t y, uint8_t scale, uint8_t* s);

#endif /* __PRINTSCALE_H__ */
