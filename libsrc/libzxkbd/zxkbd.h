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
 * @brief Получить язык
 */
uint8_t  zxIsRus();

/**
 * @brief Установить язык (0 - English)
 */
uint8_t  zxSetLang(uint8_t lang);

/**
 * @brief Получить регистр (0-lower)
 */
uint8_t  zxIsCaps();

/**
 * @brief Установить регистр
 */
uint8_t  zxSetCaps(uint8_t caps);

/**
 * @brief Сканирование клавиатурной матрицы (1/50 сек)
 */
void scanINT();

#endif // ZXKBD_H
