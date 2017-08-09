#ifndef SCRHELPER_H
#define SCRHELPER_H

#include <stdint.h>

/**
 * @brief Инициализация экрана с 0xC000
 */
void scrInit();
 
/**
 * @brief Перенос экрана с 0xC000 в 0x4000
 */
void scrFlip();

#endif // SCRHELPER_H
