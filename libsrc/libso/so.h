
#ifndef __SO_H__
#define __SO_H__

#include <stdint.h>

#define SO_SIGN 0x424С

/**
* @brief Заголовок перемещаемой библиотеки
*/
typedef struct {
	uint16_t	signature;	// Сигнатура 0x424С (LB)
	uint16_t	version;	// Версия
	uint16_t	name_offset;	// смещение от начала файла имени
	uint16_t	reloctbl_offset;// смещение от начала файла таблцы перемещения
}soHeader;

/**
 * Таблица перемещения.
 * 
 * Все файлы имеют начальный адрес 0 после компиляции
 * 
 * .dw размер (в словах по 16 бит)
 * .dw <адр.> <адр.> <адр.>
 */

/**
* @brief Настраивает библиотеку
* 
* @param load_adr p_load_adr - адрес загрузки
* @return void* - первый саободный адрес за библиотекой (NULL - ошибка)
*/
void* soReloc(void* load_adr);


#endif /* __SO_H__ */
