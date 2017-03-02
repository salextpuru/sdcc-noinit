/**
    @file scrfunc.h
    Функции для вывода на экран
*/
#ifndef scrfunc_h_E
#define scrfunc_h_E
#include <stdint.h>

/**
 * @brief Типы курсора
 */
typedef enum curTypes{
	ctnone=0,	// Невидимый
	insert,		// Вставка
	replace		// Замена
} curTypes;

/**
 * @brief Типы рамки
 */
typedef enum borderTypes{
	btnone=0,		// нет
	singl,		// одинарная
	doubl		// двойная
} borderTypes;


/**
 * @brief Функции вывода на экран
 * 	Все функции привязаны к знакоместам 8x8 пикселей
 */
typedef struct {
	/**
	 * @brief размеры экрана
	 */
	uint8_t x;
	uint8_t y;
	uint8_t w;
	uint8_t h;
	
	/**
	 * @brief Текущий цвет 
	 */
	uint32_t	wcolor;
	
	/**
	 * @brief Установка цвета
	 */
	void (*setcolor)(uint32_t color);
	
	/**
	 * @brief Очистка экрана
	 */
	void (*clrscr)();
	
	/**
	 * @brief Очистка окна (цвет установлен)
	 */
	void (*clear_window)(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
	
	/**
	 * @brief Вычисление размера памяти, потребного для сохранения окна,
	 * 	заданного размера
	 */
	uint32_t (*get_win_size)(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
	
	/**
	 * @brief Сохранить окно заданного размера в буфере
	 */
	void	(*store_window)(void* buf, uint8_t x, uint8_t y, uint8_t w, uint8_t h);
	
	/**
	 * @brief Вывести окно из буфера на экран
	 */
	void	(*restore_window)(void* buf, uint8_t x, uint8_t y, uint8_t w, uint8_t h);
	
	/**
	 * @brief Вывести символ в позицию курсора
	 */
	void	(*putc)(char c);
	
	/**
	 * @brief Вывести строку в позицию курсора
	 * 	Выводится не более maxsize символов,
	 * 	остальное добивается пробелами,
	 * 	если строка короче maxsize
	 */
	void	(*puts)(const char* s, uint8_t maxsize);
	
	/**
	 * @brief Установить позицию позицию курсора
	 */
	void	(*curpos)(uint8_t x, uint8_t y);
	
	/**
	 * @brief Установить тип курсора
	 */
	void	(*curset)(uint32_t color, curTypes t);
	
	/**
	 * @brief Вывести рамку заданного типа
	 */
	void	(*border)(borderTypes btype, uint8_t x, uint8_t y, uint8_t w, uint8_t h);
	
} scrDriverFunc;

/**
 * @brief Драйвер экрана
 */
extern scrDriverFunc*	txt_screen_driver;

#endif /* scrfunc_h_E */
