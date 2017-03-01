#ifndef PS2_H_DEFINED
#define PS2_H_DEFINED

#include <types.h>
#include "ps2_const.h"

/**
	Инициализация.
*/
void InitPS2()__naked;

/**
	Получить скан-код и флаги.
	Служебная и не очень нужная
*/
WORD GetPS2()__naked;

/**
	Получение нажатой клавиши.
	Старший байт, бит 0 (KEXTEND) определяет -
	обычная клавиша или дополнительная. Младший байт - код символа
	с учётом регистра и раскладки. KOI8-R
*/
WORD InKey()__naked;

/**
	Проверка - нажат ли CTRL (0-не нажат)
*/
BYTE IsCTRL()__naked;

/**
	Проверка - нажат ли ALT (0-не нажат)
*/
BYTE IsALT()__naked;

/**
	Проверка - нажат ли SHIFT (0-не нажат)
*/
BYTE IsSHIFT()__naked;

/**
	Проверка - Регистра (0 - лат., иначе рус.)
*/
BYTE IsRUS()__naked;

/**
	Проверка - Регистра (0 - строчные, иначе - заглавные)
*/
BYTE IsUPPER()__naked;

#endif /* PS2_H_DEFINED */
