/**
 * Обработка загруженных модулей (перемещение и проч.)
 */
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
	uint16_t	link_counter;	// счетчик ссылок на библиотеку
	//
	uint16_t	reserv0;	// резерв
	uint16_t	reserv1;	// резерв
	uint16_t	reserv2;	// резерв
}soHeader;

/**
 * Таблица перемещения.
 * 
 * Все файлы имеют начальный адрес 0 после компиляции
 * Загрузка перемещаемых файлов ТОЛЬКО с адреса кратного 0x100 (256) !
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

/**
* @brief Описатель секции _SHARED_LINKS,
* 	включающей описания подключенных библиотек.
*/
typedef struct {
	void*		next_link;
	void*		load_adr;
	uint16_t	page;
	uint16_t	flags;
	const char	name[];
} shared_link;

/**
* @brief Получить начало области описаний перемещаемых библиотек
*/
void* get_shared_links_area();

/**
* @brief Получить адрес окончания области описаний перемещаемых библиотек + 1
*/
void* get_shared_links_area_end();

#endif /* __SO_H__ */
