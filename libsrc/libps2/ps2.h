#ifndef PS2_H_DEFINED
#define PS2_H_DEFINED

#include <types.h>
#include <stdint.h>
#include "ps2_const.h"

/**
	Инициализация.
*/
void ps2Init();

/**
	Получение нажатой клавиши.
	Старший байт, бит 0 (KEXTEND) определяет -
	обычная клавиша или дополнительная. Младший байт - код символа
	с учётом регистра и раскладки. KOI8-R
*/
uint16_t ps2InKey();

/**
	Проверка - нажат ли CTRL (0-не нажат)
*/
uint8_t ps2IsCTRL();

/**
	Проверка - нажат ли ALT (0-не нажат)
*/
uint8_t ps2IsALT();

/**
	Проверка - нажат ли SHIFT (0-не нажат)
*/
uint8_t ps2IsSHIFT();

/**
	Проверка - Регистра (0 - лат., иначе рус.)
*/
uint8_t ps2IsRus();

/**
	Проверка - Регистра (0 - строчные, иначе - заглавные)
*/
//BYTE IsUPPER();
uint8_t ps2IsCaps();

#endif /* PS2_H_DEFINED */
