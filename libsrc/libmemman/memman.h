/**
 * @file memman.c - базовые типы управления памятью
 */
#ifndef __MEMMAN_H__
#define __MEMMAN_H__

#include <stdint.h>

/**
* @brief Длинный указатель
*/
typedef	uint32_t mm_far_ptr;

/**
* @brief Максимальный размер выделяемой памяти
*/
#define MM_MAX_ALLOC_SIZE	0x4000

/**
 * @brief Получить номер страницы памяти
 * 
 * @param p - длинный адрес
 * @return uint16_t - номер страницы
 */
uint16_t getPage(mm_far_ptr p);

/**
 * @brief Получить короткий адрес (0x0000-0xFFFF)
 * 
 * @param p - длинный адрес
 * @return uint16_t - короткий адрес
 */
uint16_t getShortAdr(mm_far_ptr p);

/**
 * @brief Получить короткий адрес внутри страницы (0x0000 - 0x3FFF)
 * 
 * @param p - длинный адрес
 * @return uint16_t - короткий адрес внутри страницы
 */
uint16_t getPAdr(mm_far_ptr p);
 
/**
 * @brief Получить маску окна памяти (00 40 80 С0)
 * 
 * @param p - длинный адрес
 * @return uint8_t - маска окна памяти (00 40 80 С0)
 */
uint8_t getWinMask(mm_far_ptr p);

/**
 * @brief Получить номер окна памяти (00 01 02 03)
 * 
 * @param p - длинный адрес
 * @return uint8_t - номер окна памяти (00 01 02 03)
 */
uint8_t getWin(mm_far_ptr p);

/**
 * @brief Собирает динный адрес из страницы и короткого адреса
 * 
 * @param shortadr - короткий адрес
 * @param page - сраница
 * @return uint32_t - длинный адрес
 */
uint32_t getLongAdr(uint16_t shortadr, uint16_t page);

#endif /* __MEMMAN_H__ */
