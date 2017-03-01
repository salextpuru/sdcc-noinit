#ifndef WCPLUGIN_INCLUDE
#define WCPLUGIN_INCLUDE

#include <stdint.h>
#include <wckeyfunc.h>

// Entry code
#define	wcpEntryExt	0x00
#define	wcpEntryLoad	0x01
#define	wcpEntryTimer	0x02
#define	wcpEntryMenu	0x03
#define	wcpEntryF4	0x14

// Exit code
#define	wcpExitOk	0x00
#define	wcpExitErFile	0x01
#define	wcpExitNextFile	0x02
#define	wcpExitPrevFile	0x04
#define	wcpExitReadCat	0x03

/*
 * --- Entry-Exit interface ---
 */
// Entry code (read)
extern uint8_t	entry_code;
// Exit code (must be set on exit)
extern uint8_t	exit_code;
// Extention number (read)
extern uint8_t	ext_number;
// Pointer to file name on entry (read)
extern char*	file_name_adr;
// Size of file on entry (read)
extern uint32_t	file_len;
// Active panel window (read)
extern void*	active_panel_adr;


#define wcWinTypeSimple		0
#define wcWinTypeHText		1
#define wcWinTypeHTextCur	2

// Data window type 0
typedef struct {
	uint8_t curx;	//12
	uint8_t cury;	//13
	uint8_t cur_color;//14
	uint8_t cur_wcolor;//15
} wcwintype0data;

// Data window type 1
typedef struct {
	char* topHeader;//12
	char* botHeader;//14
	char* text;//16
} wcwintype1data;

// Data window type 2
typedef struct {
	uint8_t curx;//12
	uint8_t cury;//13
	uint8_t cur_color;//14
	uint8_t cur_wcolor;//15
	char* topHeader;//16
	char* botHeader;//18
	char* text;//20
} wcwintype2data;

// Data window all types
typedef union{
	wcwintype0data type0;
	wcwintype1data type1;
	wcwintype2data type2;
} wcwindata;

// Window descriptor
typedef struct {
	uint8_t		winType;	//+0
	uint8_t		curColorMask;	//+1
	uint8_t		winX;		//+2
	uint8_t		winY;		//+3
	uint8_t		winWidth;	//+4
	uint8_t		winHeigh;	//+5
	uint8_t		winColor;	//+6
	uint8_t		winReserv0;	//+7
	void*		winStoreBuf;	//+8
	uint8_t		winLine1;	//+10
	uint8_t		winLine2;	//+11
	wcwindata	data;		//+12... (depend from winType)
} wcWindow;

// wait for farme (function enabled Interrupts!)
void	wcWaitForFrame();

// 86
#define wcINT_DISABLE	0
#define wcTIME_DISABLE	1
#define wcPS2_DISABLE	2
#define wcSET_INTHDL	0xFF
void wcINTPL(uint8_t mode, void* int_handler);

// 1	вывод окна на экран
void	wcPRWOW(wcWindow* wnd);

// 3	печать строки в окне (включает основной ТХТ экран в #C000)
void	wcPRSRW(wcWindow* win, const char* text, uint8_t x, uint8_t y, uint16_t len, uint8_t color);

// Печать строки, длина вычисляется автоматом
void	wcPrint(wcWindow* win, const char* text, uint8_t x, uint8_t y, uint8_t color);

// 0	включение страницы на #C000 (из выделенного блока)
//	нумерация совпадает с использующейся в +36
#define	wcFONT_PAGE	0xFF
#define	wcTXTSCR_PAGE	0xFE
void	wcMNGCPL(uint8_t page);

// 78	включение страницы на #0000 (из выделенного блока)
//	не влияет на работу FAT драйвера, НО все структуры
//	которые будут подаваться файловым функциям, должны
//	лежать в адресах #8000-#FFFF!
void	wcMNG0PL(uint8_t page);

// 79	включение страницы на #8000 (из выделенного блока)
void	wcMNG8PL(uint8_t page);

// 2	стирание окна (восстановление информации) (включает основной ТХТ экран в #C000)
void	wcRRESB(wcWindow* wnd);

// 5	получение адреса в окне (включает основной ТХТ экран в #C000)
void*	wcGADRW(wcWindow* wnd, uint8_t x, uint8_t y);

// 6	печать курсора
void	wcCURSHOW(wcWindow* wnd);

// 7	стирание курсора (восстановление цвета)
void	wcCURHIDE(wcWindow* wnd);

// 8	меню ok/cancel
#define	wcYNINIT	0x01	/* инициализация (вычисляет координаты) */
#define	wcYNIDLE	0x00	/* обработка нажатий (вызывать раз в фрейм) */
#define	wcYNEXIT	0xFF	/* выход */
// return
#define	wcYN_CANCEL	0x00
#define	wcYN_OK		0x01
uint8_t	wcYNMENU(uint8_t mode);

// 9

#endif
