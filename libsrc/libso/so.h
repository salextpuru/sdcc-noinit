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
	const char*	name;		// смещение от начала файла имени / адрес имени библиотеки
	uint16_t	reloctbl_offset;// смещение от начала файла таблцы перемещения / адрес таблцы перемещения
	uint16_t	link_counter;	// счетчик ссылок на библиотеку
	//
	uint16_t	nfunc;		// количество функций (без функции инициализации)
	uint16_t	reserv1;	// резерв
	uint16_t	reserv2;	// резерв
}soHeader;

/**
* @brief Описатель функции
*/
typedef struct {
	// переход на функцию (команда)
	uint8_t		jump;
	// переход на функцию (адрес)
	uint16_t	jumadr;
	// название функции
	const char* name;
} soFuncDsc;
 

/**
 * @brief Возвращает Описатель функции номер n=[0..N-1]
 * 	Если такой функции нет, то возвращает NULL
 */
soFuncDsc* getSoFuncDsc (soHeader* h, uint16_t n);

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

/**
 * @brief Ищет внутреннюю структуру загруженной библиотеки и настраивает её.
 */
void* tune_shared_obj(soHeader* lib);

#endif /* __SO_H__ */
