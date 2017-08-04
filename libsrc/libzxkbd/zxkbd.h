/*
 * Alex Shamin
 * INCOM Tomsk
 * 04:08:2017
 */

#ifndef ZXKBD_H
#define ZXKBD_H

#include <stdint.h>

/**
 * @brief Получить код нажатой клавиши
 * @return uint16_t
 */
uint16_t zxInKey();

/**
 * @brief Сканирование клавиатурной матрицы (1/50 сек)
 */
void scanINT();

#endif // ZXKBD_H
