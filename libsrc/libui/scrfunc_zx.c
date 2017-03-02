#include <scrfunc.h>
#include <zxcolor.h>
#include "conio.h"

static void setcolor(uint32_t c){
	color(c&0xFF);
}

scrDriverFunc	zx_screen_driver = {
	/**
	 * @brief размеры экрана
	 */
	.x=0,
	.y=0,
	.w=32,
	.h=24,
	
	/**
	 * @brief Текущий цвет 
	 */
	.wcolor=ATTRN(YELLOW,BLACK),
	
	/**
	 * @brief Установка цвета
	 */
	.setcolor=setcolor,
	
	/**
	 * @brief Очистка экрана
	 */
	.clrscr=cls
	
	/**
	 * @brief Очистка окна (цвет установлен)
	 */
	//void (*clear_window)(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
	
	/**
	 * @brief Вычисление размера памяти, потребного для сохранения окна,
	 * 	заданного размера
	 */
	//uint32_t (*get_win_size)(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
	
	/**
	 * @brief Сохранить окно заданного размера в буфере
	 */
	//void	(*store_window)(void* buf, uint8_t x, uint8_t y, uint8_t w, uint8_t h);
	
	/**
	 * @brief Вывести окно из буфера на экран
	 */
	//void	(*restore_window)(void* buf, uint8_t x, uint8_t y, uint8_t w, uint8_t h);
	
	/**
	 * @brief Вывести символ в позицию курсора
	 */
	//void	(*putc)(char c);
	
	/**
	 * @brief Вывести строку в позицию курсора
	 * 	Выводится не более maxsize символов,
	 * 	остальное добивается пробелами,
	 * 	если строка короче maxsize
	 */
	//void	(*puts)(const char* s, uint8_t maxsize);
	
	/**
	 * @brief Установить позицию позицию курсора
	 */
	//void	(*curpos)(uint8_t x, uint8_t y);
	
	/**
	 * @brief Установить тип курсора
	 */
	//void	(*curset)(uint32_t color, curTypes t);
	
	/**
	 * @brief Вывести рамку заданного типа
	 */
	//void	(*border)(borderTypes btype, uint8_t x, uint8_t y, uint8_t w, uint8_t h);
	
};