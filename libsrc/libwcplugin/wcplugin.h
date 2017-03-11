#ifndef WCPLUGIN_INCLUDE
#define WCPLUGIN_INCLUDE

#include <stdint.h>
#include <wckeyfunc.h>
#include <wcfatfunc.h>

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

// Get page in win0
uint16_t wcGetW0Page();

// Get page in win1
uint16_t wcGetW1Page();

// Get page in win2
uint16_t wcGetW2Page();

// Get page in win3
uint16_t wcGetW3Page();

// Get ABT flag
uint8_t wcGetAbortFlag();

// Get Enter flag
uint8_t wcGetEnterFlag();

// Get timer (+1 every 20ms)
uint16_t wcGetTimer();

// Colors
enum wcColors{
	wcBlue		= 1,
	wcRed		= 2,
	wcMagenta	= 3,
	wcGreen		= 4,
	wcCyan		= 5,
	wcYellow	= 6,
	wcGray		= 7,
	wcBlack 	= 8,
	wcLightBlue	= 1,
	wcLightRed	= 2,
	wcLightMagenta	= 3,
	wcLightGreen	= 4,
	wcLightCyan	= 5,
	wcLightYellow	= 6,
	wcWhite		= 7,
};

#define wcColorCode( ink, paper ) ((( paper & 0xFF ) << 4) |  (ink & 0xFF))

#define wcWinTypeSimple		0
#define wcWinTypeHText		1
#define wcWinTypeHTextCur	2

// Data window type 0
typedef struct {
	uint8_t curx;	//12	позиция курсора в окне (от 1)
	uint8_t cury;	//13	нижний ограничитель
	uint8_t cur_color;//14	цвет курсора (накладывается по маске из +1(1))
	uint8_t cur_wcolor;//15 цвет окна под курсором
} wcwintype0data;

// Data window type 1
typedef struct {
	const char* topHeader;//12	адрес строки для верхнего заголовка окна
	const char* botHeader;//14	адрес строки для нижнего заголовка окна
	const char* text;//16		адрес строки/абзаца для вывода в окно
} wcwintype1data;

// Data window type 2
typedef struct {
	uint8_t curx;//12	позиция курсора в окне (от 1)
	uint8_t cury;//13	нижний ограничитель
	uint8_t cur_color;//14	цвет курсора (накладывается по маске из +1(1))
	uint8_t cur_wcolor;//15 цвет окна под курсором
	const char* topHeader;//16	адрес строки для верхнего заголовка окна
	const char* botHeader;//18	адрес строки для нижнего заголовка окна
	const char* text;//20		адрес строки/абзаца для вывода в окно
} wcwintype2data;

// Data window all types
typedef union{
	wcwintype0data type0;
	wcwintype1data type1;
	wcwintype2data type2;
} wcwindata;

// Window descriptor
typedef struct {
	uint8_t		winType;	//+0	0 - стандартное окно
					//	1 - окно с заголовками и текстом (но без курсора)
					//	2 - окно с заголовками, текстом с курсором
	//
	uint8_t		curColorMask;	//+1	маска цвета курсора
	uint8_t		winX;		//+2	позиция окна X
	uint8_t		winY;		//+3	позиция окна Y
	uint8_t		winWidth;	//+4	ширина окна (Width)  0 = во весь экран
	uint8_t		winHeigh;	//+5	высота окна (Height) 0 = во весь экран
	uint8_t		winColor;	//+6	цвет окна (Paper+Ink)
	uint8_t		winReserv0;	//+7	reserved (always=0!)
	//
	void*		winStoreBuf;	//+8	адрес буфера, где лежит информация из под окна
					//	#0000=окно не выведено, система меняет эту переменную на актуальное значение!
					//	#FFFF=при выводе окна буфер не используется!
	//
	uint8_t		winLine1;	//+10	линия разделитель 1 
	uint8_t		winLine2;	//+11	линия разделитель 2
					//	если !=0 то выводим оную.
					//	Значение задает смещение по вертикали с низу!
					
	wcwindata	data;		//+12... (depend from winType, see wcwintype0data, wcwintype1data, wcwintype2data)
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

// 9 Input string (without indicators)
// Init string edit type 2
// x,y		- position into the window
// curpos	- cursor's position in the string
// wlen		- size of visible string part
// buf		- adress of buffer for the string
// bufsize 	- size of string
void	wcISTRinit2(wcWindow* wnd, uint8_t x, uint8_t y, uint8_t curpos, uint8_t wlen, char* buf, uint16_t bufsize);

// Call eyery frame after wcISTRinit2 (edit process, without indicators)
void	wcISTREdit2(wcWindow* wnd);

// 9 Input string (with indicators)
// Init string edit type 2
// x,y		- position into the window
// curpos	- cursor's position in the string
// wlen		- size of visible string part
// buf		- adress of buffer for the string
// bufsize 	- size of string
void	wcISTRinit2IndTop(wcWindow* wnd, uint8_t x, uint8_t y, uint8_t curpos, uint8_t wlen, char* buf, uint16_t bufsize);
void	wcISTRinit2IndBottom(wcWindow* wnd, uint8_t x, uint8_t y, uint8_t curpos, uint8_t wlen, char* buf, uint16_t bufsize);

// Call eyery frame after wcISTRinit2Ind* (edit process, with indicators)
void	wcISTREdit2Ind(wcWindow* wnd);

// 11 TXTPR     вывод текста в окне
uint8_t wcTXTPR(wcWindow* win, const char* text, uint8_t x, uint8_t y);

// 12 MEZZ	вывод сообщения в окне
uint8_t wcMEZZ(wcWindow* win, uint8_t nmsg, const char* msgtable, uint8_t x, uint8_t y);

// 15 GEDPL	восстановление паллитры, всех оффсетов и txt режима
//		обязательно вызывать при запуске плагина!
//		(включает основной txt экран)
void	wcGEDPL();

// 84 SCRLWOW	сдвинуть содержимое области в окне
// mode - режим сдвига

// Направление
#define wcSCRL_UP		0x01
#define wcSCRL_DOWN		0x00
#define wcSCRL_LEFT		0x03
#define wcSCRL_RIGHT		0x02

// Очистка прокрученной строки
#define wcSCRL_CLEAR		0x40

// Сдвигать атрибуты
#define wcSCRL_ATTRS		0x80

// Шаг сдвига (1-16)
#define wcSCRL_STEP(step)	((step-1)<<2)

// Example (scroll up, 2 lines with attrs, clear):
// mode = wcSCRL_UP | wcSCRL_STEP(2) | wcSCRL_ATTRS | wcSCRL_CLEAR;

void wcSCRLWOW(wcWindow* win, uint8_t scroll_mode,  uint8_t x, uint8_t y, uint8_t w, uint8_t h);

#endif
