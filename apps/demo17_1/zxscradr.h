/**
 * Screen adress functions
 * 
 * --- More functions got FROM BOOK "let's code a zx demo"  ---
 * 
 */

#ifndef __ZXSCRADR_H__
#define __ZXSCRADR_H__

/**
* @brief Get screen address
* 
* Calling from assembler as call _asm_GetPixelAdr
* 
* in:	B = Y pixel position
* 	C = X pixel position
* 
* out:	Returns address in HL
*/
void  asm_GetPixelAdr();

/**
* @brief Вычислить адрес линии ниже текущей
* 
* вход: HL=адрес экранной линии
* выход: HL= адрес экранной линии ниже
*/
void asm_DownHL();

/**
* @brief Вычислить адрес линии выше текущей
* 
* вход: HL=адрес экранной линии
* выход: HL= адрес экранной линии выше
*/
void asm_UpHL();

#endif /* __ZXSCRADR_H__ */
