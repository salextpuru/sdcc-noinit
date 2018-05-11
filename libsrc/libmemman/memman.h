/**
 * @file memman.c - базовые типы управления памятью
 */
#ifndef __MEMMAN_H__
#define __MEMMAN_H__

#include <stdint.h>

/**
 * Описатель страницы памяти 1 байт
 * Биты:
 * 	0,1 (MPG_WMASK)	- номер окна, в которое может быть
 * 				впечатана страница 16К (0..3)
 *
 * 	2 (MPG_BUSY)	- страница занята
 * 	3 (MPG_FIXED)	- страница не может быть освобождена (например, занята системой)
 * 	4..6		- резерв
 * 	7 (MPG_ABSENT)	- страница отсутствует (Страница с таким номером не существует)
 */
#define MPG_WMASK		0x03
#define MPG_GETWIN(p)		((p)&MPG_WMASK)

#define MPG_BUSY		0x04
#define MPG_FIXED		0x08
#define MPG_ABSENT		0x80

/**
 * Описатель окна памяти 4 байта
 */
typedef struct {
	uint16_t	page;	// +00 Номер страница (0..65535)
	uint8_t		flags;	// +02 Флаги
	uint8_t		res0;	// +03 Резерв
} mm_win_d;

/**
* Флаги окна памяти (mm_win_d.flags)
* Биты:
* 	0..1 (MWF_WMASK)	- номер окна (0..3)
* 	2,3		- резерв
* 	4 (MWF_FIXED)	- страница в окне памяти фиксирована (невозможно её сменить)
* 	5 (MWF_ROM)	- в окне страница памяти ПЗУ (ROM) номер указан
* 	6,7		- резерв
*/
#define MWF_WMASK		0x03
#define MWF_GETWIN(p)		((p)&MWF_WMASK)

#define MWF_FIXED	0x10
#define MWF_ROM		0x11

// Количество окон памяти по 16К
#define MEM_WINS		0x04

// --- КОДЫ ОШИБОК ---
#define MME_OK		0x00	/* Нет ошибок */
#define MME_WFIXED	0x01	/* Страница не может быть впечатана в это окно */
#define MME_ABSENT	0x80	/* Страница с таким номером не существует */

// ------------------------ Функции работы с окном памяти ------------------------

/**
* @brief Получить массив описателей окон
* 	Только для других менеджеров памяти!
* 	Не использовать в программах Пользовтеля!
*/
mm_win_d* __MMgetMemWinsD();

/**
* @brief получить номер страницы в окне w
*/
uint16_t MMgetWinPage(uint8_t w);

/**
* @brief получить флаги страницы в окне w
*/
uint8_t MMgetWinFlags(uint8_t w);

/**
* @brief Получить указатель на описатель окна w
*/
mm_win_d* MMgetWinD(uint8_t w);

/**
* @brief Структура, описывающая функции работы с менеджером памяти
*/
typedef struct {
	// ------------------------ Функции работы со страницами ОЗУ (RAM) ------------------------
	/**
	* @brief Получить число страниц RAM
	*/
	uint16_t (*MMgetPagesCount)();

	/**
	* @brief Получить описатель страницы page RAM
	*/
	uint8_t (*MMGetPageFlags)(uint16_t page);

	/**
	* @brief Впечатать страницу page в окно win RAM
	* 	Возвращает код ошибки.
	* 	0-всё получилось
	*/
	uint8_t (*MMSetPageWin)(uint16_t page, uint8_t win);

	// ------------------------ Функции работы со страницами ПЗУ (ROM) ------------------------

	/**
	* @brief Получить число страниц ROM
	*/
	uint16_t (*MMgetPagesCountROM)();

	/**
	* @brief Впечатать страницу page в окно win ROM
	* 	Возвращает код ошибки.
	* 	0-всё получилось
	*/
	uint8_t (*MMSetPageWinROM)(uint16_t page, uint8_t win);
} memman_f;

/**
* @brief После инициализации только через mm_func
* 	идёт обращение к переопределяемым функциям
*/
extern memman_f* mm_func;

#endif /* __MEMMAN_H__ */
