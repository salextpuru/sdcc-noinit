#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

/**
 * Указатели на функции
 * Если функция отсутствует (NULL),
 * то режим считается по умолчанию.
 */

typedef struct kbdDriver {

/**
 * @brief Необходимо, чтобы функция
 * 	возвращала обобщенный код клавиши
 *
 * 	Символьные клавиши - 0x01 - 0xFF.
 * 	0x1000 - 0x1FFF - управляющие
 */
uint16_t ( *InKey ) ();

/**
 * @brief Получить язык (умолчание 0)
 */
uint8_t ( *KbdIsRus ) ();

/**
 * @brief Установить язык (0 - English)
 */
uint8_t ( *KbdSetLang ) ( uint8_t lang );

/**
 * @brief Получить регистр (0-lower) (умолчание 0)
 */
uint8_t ( *KbdIsCaps ) ();

/**
 * @brief Установить регистр (0-lower)
 */
uint8_t ( *KbdSetCaps ) ( uint8_t caps );

/**
	Проверка - нажат ли SHIFT (0-не нажат)
*/
uint8_t ( *KbdIsSHIFT ) ();

/**
	Проверка - нажат ли CTRL (0-не нажат) (умолчание 0)
	( CTRL =Symbol Shift)
*/
uint8_t ( *KbdIsCTRL ) ();

/**
	Проверка - нажат ли ALT (0-не нажат) (умолчание 0)
	Всегда 0 (ALT отсутствует)
*/
uint8_t ( *KbdIsALT ) ();

} kbdDriver;


/**
 * @brief Указатель на структуру - драйвер клавиатуры
 */
extern kbdDriver*	keyboardDriver;

/**
 * @brief Обобщенный код клавиши.
 * 	Для PS2 равен коду, возвращаемому драйвером,
 * 	а для ZX - как нравится перекодируйте
 */
enum keyboard_codes {
	kbdESC = 0x001B,
	
	kbdINSERT	=0x0109,
	kbdHOME	=0x010A,

	kbdPGUP	=0x010B,
	kbdPGDN	=0x010C,

	kbdKDELETE	=0x010D,
	kbdKEND	=0x010E,

	kbdUP	=0x010F,
	kbdDN	=0x0110,
	kbdLEFT	=0x0111,
	kbdRIGHT	=0x0112,

	kbdF1	=0x0113,
	kbdF2	=0x0114,
	kbdF3	=0x0115,
	kbdF4	=0x0116,
	kbdF5	=0x0117,
	kbdF6	=0x0118,
	kbdF7	=0x0119,
	kbdF8	=0x011A,
	kbdF9	=0x011B,
	kbdF10	=0x011C,
	kbdF11	=0x011D,
	kbdF12	=0x011E,

	kbdNUMLOCK	=0x0120,
	kbdKPMUL	=0x0121,
	kbdKPMIMUS	=0x0122,
	kbdKPPLUS	=0x0123,
	kbdKPENTER	=0x0124,
	kbdKPPOINT	=0x0125,

	kbdKP0	=0x0126,
	kbdKP1	=0x0127,
	kbdKP2	=0x0128,
	kbdKP3	=0x0129,
	kbdKP4	=0x0130,
	kbdKP5	=0x0131,
	kbdKP6	=0x0132,
	kbdKP7	=0x0133,
	kbdKP8	=0x0134,
	kbdKP9	=0x0135
};

#endif // KEYBOARD_H

