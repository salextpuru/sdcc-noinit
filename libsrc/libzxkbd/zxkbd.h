/*
 * Alex Shamin
 * INCOM Tomsk
 * 04:08:2017
 */

#ifndef ZXKBD_H
#define ZXKBD_H

#include <stdint.h>

/**
	Инициализация.
*/
void zxKbdInit();

/**
 * @brief Получить код нажатой клавиши
 * @return uint16_t
 */
uint16_t zxKbdInKey();

/**
 * @brief Получить язык
 */
uint8_t  zxKbdIsRus();

/**
 * @brief Установить язык (0 - English)
 */
uint8_t  zxKbdSetLang(uint8_t lang);

/**
 * @brief Получить регистр (0-lower)
 */
uint8_t  zxKbdIsCaps();

/**
 * @brief Установить регистр
 */
uint8_t  zxKbdSetCaps(uint8_t caps);

/**
	Проверка - нажат ли SHIFT (0-не нажат)
*/
uint8_t zxKbdIsSHIFT();

/**
	Проверка - нажат ли CTRL (0-не нажат)
	( CTRL =Symbol Shift)
*/
uint8_t zxKbdIsCTRL();

/**
	Проверка - нажат ли ALT (0-не нажат)
	Всегда 0 (ALT отсутствует)
*/
uint8_t zxKbdIsALT();

/**
 * @brief Сканирование клавиатурной матрицы (1/50 сек)
 */
void zxKbdScan();

#endif // ZXKBD_H
