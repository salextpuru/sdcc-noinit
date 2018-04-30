#include "keybozx.h"
#include <zxkbd.h>

static uint16_t zInKey(){
	uint16_t key = zxKbdInKey();
	
	// Для ZX надо перекодировать клавиши
	if( zxKbdIsSHIFT() ) switch(key){
		case '1':{
			key = kbdESC;
			break;
		}
		case '5':{
			key = kbdLEFT;
			break;
		}
		case '8':{
			key = kbdRIGHT;
			break;
		}
		case '7':{
			key = kbdUP;
			break;
		}
		case '6':{
			key = kbdDN;
			break;
		}
	}
	
	return key;
}

static const kbdDriver zxkbd={

/**
 * @brief Необходимо, чтобы функция
 * 	возвращала обобщенный код клавиши
 *
 * 	Символьные клавиши - 0x01 - 0xFF.
 * 	0x1000 - 0x1FFF - управляющие
 */
.InKey=zInKey,

/**
 * @brief Получить язык (умолчание 0)
 */
.KbdIsRus = zxKbdIsRus,

/**
 * @brief Установить язык (0 - English)
 */
.KbdSetLang = zxKbdSetLang,

/**
 * @brief Получить регистр (0-lower) (умолчание 0)
 */
.KbdIsCaps = zxKbdIsCaps,

/**
 * @brief Установить регистр (0-lower)
 */
.KbdSetCaps = zxKbdSetCaps,

/**
	Проверка - нажат ли SHIFT (0-не нажат)
*/
.KbdIsSHIFT = zxKbdIsSHIFT,

/**
	Проверка - нажат ли CTRL (0-не нажат) (умолчание 0)
	( CTRL =Symbol Shift)
*/
.KbdIsCTRL = zxKbdIsCTRL,

/**
	Проверка - нажат ли ALT (0-не нажат) (умолчание 0)
	Всегда 0 (ALT отсутствует)
*/
.KbdIsALT = zxKbdIsALT

};

void setKeyboardZX(){
	keyboardDriver = &zxkbd;
}
