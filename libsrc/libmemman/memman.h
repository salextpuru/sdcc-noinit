/**
 * @file memman.c - базовые типы управления памятью
 */
#ifndef __MEMMAN_H__
#define __MEMMAN_H__

#include <stdint.h>

/**
* @brief Длинный указатель
*/
typedef	uint32_t mm_far_ptr;

/**
* @brief Максимальный размер выделяемой памяти
*/
#define MM_MAX_ALLOC_SIZE	0x4000

// -----------------------------------------------------------------------------------------------

/**
 * Описатель страницы памяти 1 байт
 * Биты:
 * 	0,1 (MPG_WMASK)	- номер окна, в которое может быть
 * 				впечатана страница 16К (0..3)
 *
 * 	2 (MPG_BUSY)	- страница занята
 * 	3 (MPG_FIXED)	- страница не может быть освобождена (например, занята системой)
 * 
 * 	4 (MPG_RSRV0)	- резерв
 * 	5 (MPG_RSRV1)	- резерв
 * 	6 (MPG_RSRV2)	- резерв
 * 
 * 	7 (MPG_ABSENT)	- страница отсутствует (Страница с таким номером не существует)
 */
#define MPG_WMASK		0x03
#define MPG_GETWIN(p)		((p)&MPG_WMASK)

#define MPG_BUSY		0x04
#define MPG_FIXED		0x08

#define MPG_RSRV0		0x10
#define MPG_RSRV1		0x20
#define MPG_RSRV2		0x40

#define MPG_ABSENT		0x80

// -----------------------------------------------------------------------------------------------

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
* 
* 	2 (MWF_RSRV0)	- резерв
* 	3 (MWF_RSRV1)	- резерв
* 
* 	4 (MWF_FIXED)	- страница в окне памяти фиксирована (невозможно её сменить)
* 
* 	5 (MWF_ROM)	- в окне страница памяти ПЗУ (ROM) номер указан (0-в окне RAM)
* 
* 	6 (MFW_ERAM)	- в окно может быть впечатана страница ОЗУ (RAM) (только для сменяемых страниц)
* 	7 (MFW_EROM)	- в окно может быть впечатана страница ПЗУ (ROM) (только для сменяемых страниц)
*/
#define MWF_WMASK		0x03
#define MWF_GETWIN(p)		((p)&MWF_WMASK)
#define MWF_RSRV0	0x04
#define MWF_RSRV1	0x08
#define MWF_FIXED	0x10
#define MWF_ROM		0x20
#define MWF_ERAM	0x40
#define MWF_EROM	0x80
// MWF_WMASK
#define MWF_WIN0	0x00
#define MWF_WIN1	0x01
#define MWF_WIN2	0x02
#define MWF_WIN3	0x03
// -----------------------------------------------------------------------------------------------

// Количество окон памяти по 16К
#define MEM_WINS		0x04

// --- КОДЫ ОШИБОК ---
#define MME_OK		0x00	/* Нет ошибок */
#define MME_WFIXED	0x01	/* Страница не может быть впечатана в это окно */
#define MME_FREE	0x02	/* Страница уже свободна */
#define MME_PFIXED	0x04	/* страница фиксирована и не может быть освобождена или занята */
#define MME_ABSENT	0x80	/* Страница с таким номером не существует */

// -----------------------------------------------------------------------------------------------

/**
* @brief Функция инициализации. Индивидуальная для каждого драйвера
*/
void MMInit();

// ------------------------ Функции работы с окном памяти (общие для всех) ------------------------

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
* @brief получить флаги окна w
*/
uint8_t MMgetWinFlags(uint8_t w);

/**
* @brief Получить указатель на описатель окна w
*/
mm_win_d* MMgetWinD(uint8_t w);

// ------------------------ Функции работы со страницами ОЗУ (RAM) (индивидуальные) ------------------------
/**
* @brief Получить число страниц RAM
*/
uint16_t MMgetPagesCount();

/**
* @brief Получить описатель страницы page RAM
* Если страница отсутствует - возвращает MME_ABSENT
*/
uint8_t MMGetPageFlags(uint16_t page);

/**
* @brief Установить описатель страницы page RAM
* Если страница отсутствует - возвращает MME_ABSENT
*/
uint8_t MMSetPageFlags(uint16_t page, uint8_t flags);

/**
* @brief Впечатать страницу page в окно win RAM
* 	Возвращает код ошибки.
* 	MME_OK -всё получилось
* Если страница отсутствует - возвращает MME_ABSENT
*/
uint8_t MMSetPageWin(uint16_t page, uint8_t win);

// ------------------------ Функции работы со страницами ПЗУ (ROM) (индивидуальные) ------------------------

/**
* @brief Получить число страниц ROM
*/
uint16_t MMgetPagesCountROM();

/**
* @brief Впечатать страницу page в окно win ROM
* 	Возвращает код ошибки.
* 	MME_OK -всё получилось
* Если страница отсутствует - возвращает MME_ABSENT
*/
uint8_t MMSetPageWinROM(uint16_t page, uint8_t win);

// ------------------------ Выделение-освобождение страниц ОЗУ ------------------------
/**
* @brief Получить номер свободной страницы
* 
* @param page - (return) номер страницы
* @return uint8_t - MME_OK или MME_ABSENT
*/
uint8_t MMgetFreePage(uint16_t* page);

/**
* @brief Получить номер свободной страницы и 
* 	занять её
* 
* @param page - (return) номер страницы
* @return uint8_t - MME_OK или MME_ABSENT
*/
uint8_t MMuseFreePage(uint16_t* page);

/**
* @brief Освободить страницу page
* @return uint8_t
*/
uint8_t MMfreePage(uint16_t page);

#endif /* __MEMMAN_H__ */
