#ifndef WINDOW_H
#define WINDOW_H

#include <scrfunc.h>
#include <event.h>

/**
 * @brief Окно (этакий псевдокласс с заменяемыми методами)
 */
typedef struct window{
/* Данные окна */

	/** @brief Положение и размер */
	uint8_t  x;
	uint8_t  y;
	uint8_t  w;
	uint8_t  h;
	
	/** @brief фон	 */
	tColor		paper;
	
	/** @brief тон	 */
	tColor		ink;
	
	/** @brief тип рамки */
	borderTypes	border;
	
	/** @brief окна-потомки (списко заканчивается NULL) */
	struct window**		childs;
	
	/** @brief текущий потомок (-1 - нет такого) */
	int16_t			cur_child;
	
/* Методы окна */
	/** @brief деструктор */
	void (*destructor)(struct window* this);

	/** @brief метод рисования окна */
	void (*draw)(struct window* this);
	
	/** @brief запуск цикла обработки событий */
	void (*exec)(struct window* this);
	
	/** @brief вызывается когда окно становится активным */
	void (*activate)(struct window* this);
	
	/** @brief вызывается когда окно становится пассивным */
	void (*deactivate)(struct window* this);
	
	/** @brief получить событие */
	void (*getEvent)(struct window* this, event* ev);
	
	/** @brief обработать событие */
	void (*hEvent)(struct window* this, event* ev);
	
}window;

// Методы по умолчанию
void window_destructor(window* this);
void window_draw(window* this);
void window_exec(window* this);
void window_activate(window* this);
void window_getEvent(window* this, event* ev);
void window_hEvent(window* this, event* ev);
void window_init(window* this);

#endif // WINDOW_H
