#include "keybops2.h"
#include "ps2.h"

static kbdDriver ps2kbd={

/**
 * @brief Необходимо, чтобы функция
 * 	возвращала обобщенный код клавиши
 *
 * 	Символьные клавиши - 0x01 - 0xFF.
 * 	0x1000 - 0x1FFF - управляющие
 */
.InKey=ps2InKey,

/**
 * @brief Получить язык (умолчание 0)
 */
.KbdIsRus = ps2IsRus,

/**
 * @brief Установить язык (0 - English)
 */
//uint8_t ( *KbdSetLang ) ( uint8_t lang );

/**
 * @brief Получить регистр (0-lower) (умолчание 0)
 */
.KbdIsCaps = ps2IsCaps,

/**
 * @brief Установить регистр (0-lower)
 */
//uint8_t ( *KbdSetCaps ) ( uint8_t caps );

/**
	Проверка - нажат ли SHIFT (0-не нажат)
*/
.KbdIsSHIFT = ps2IsSHIFT,

/**
	Проверка - нажат ли CTRL (0-не нажат) (умолчание 0)
	( CTRL =Symbol Shift)
*/
.KbdIsCTRL = ps2IsCTRL,

/**
	Проверка - нажат ли ALT (0-не нажат) (умолчание 0)
	Всегда 0 (ALT отсутствует)
*/
.KbdIsALT = ps2IsALT

};

void setKeyboardPS2(){
	ps2Init();
	keyboardDriver = &ps2kbd;
}
