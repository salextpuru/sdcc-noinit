#ifndef WINDOW_H
#define WINDOW_H

#include <scrfunc.h>
#include <event.h>

/** Флаги отображения */
enum {
	// Окно активно
	wflagActive	= 1,
	// Окно может быть активировано (обрабатывать события)
	wflagActivate	= 2,
};

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
	
	/** @brief Позиция курсора внутри окна */
	uint8_t  cur_x;
	uint8_t  cur_y;
	
	/** @brief фон	 */
	tColor		paper;
	
	/** @brief тон	 */
	tColor		ink;
	
	/** @brief тип рамки */
	uint8_t		border;
	
	/** @brief окна-потомки (списко заканчивается NULL) */
	struct window**	childs;
	
	/** @brief текущий потомок (-1 - нет такого) */
	int16_t		cur_child;
	
	/** Указатель на потомка, если окно чей-то предок */
	void*		child_ifparent;
	
	/** Флаги отображения */
	uint16_t	winFlags;
	
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
	
	/** @brief Печать строки в окне (за пределы не выходим) */
	uint8_t (*puts)(struct window* this, const char* s);
	
	/** @brief Установка позиции курсора в окне (за пределы не выходим) */
	void (*at)(struct window* this, uint8_t x, uint8_t y);
}window;

// Методы по умолчанию (виртуальные)
void window_destructor(window* this);
void window_draw(window* this);
void window_exec(window* this);
void window_activate(window* this);
void window_deactivate(window* this);
void window_getEvent(window* this, event* ev);
void window_hEvent(window* this, event* ev);
uint8_t window_puts(struct window* this, const char* s);
void window_at(struct window* this, uint8_t x, uint8_t y);
void window_init(window* this);

// Невиртуальные методы
/** Установка размеров */
void window_setsize(window* this, wRect* w);
/** Установить цвета */
void window_store_color(window* this, tColor* ink, tColor* paper);
/** Получить цвета */
void window_set_color(window* this, tColor ink, tColor paper);
/** Получить текущего потомка (null - нет) */
window* window_get_cur_child(window* this);
/** Перейти к следующему потомку (возвращает 1 - все ОК, 0 - потомков нет, 2 - возврат на начало) */
uint8_t window_next_child(window* this);
/** Перейти к предыдущему потомку (возвращает 1 - все ОК, 0 - потомков нет, 2 - возврат на начало) */
uint8_t window_prev_child(window* this);
#endif // WINDOW_H
