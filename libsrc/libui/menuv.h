#ifndef __MENUV_H__
#define __MENUV_H__

#include "window.h"

/**
* @brief Коды выходя из меню
*/
enum {
	menuCodeEnter=0,
	menuCodeESC
};

/**
* @brief Элемент меню
*/
struct menuv;
typedef struct menu_item{
	/** Имя Элемента */
	char* name;
	/** Обработчик элемента */
	void (*handler)(struct menuv* m);
}menu_item;

/**
 * @brief Окно (этакий псевдокласс с заменяемыми методами)
 */
typedef struct menuv{
	/** Окно. Методы переопределены */
	window		win;
	/** Заголовок */
	char*		header;
	/** Цвет тона курсора */
	tColor		curInk;
	/** Цвет фона курсора */
	tColor		curPaper;
	/** Общее количество элементов меню */
	uint16_t	item_count;
	/** Номер первого (верхнего) элемента меню */
	uint16_t	item_first;
	/** Номер текущего элемента меню */
	uint16_t	item_current;
	/** Список элементов меню (последний элемент имеет name=NULL) */
	menu_item*	items;
	/** Код выхода меню */
	uint8_t		exit_code;
	/** Выход из меню по Enter */
	uint8_t		exitOnEnter;
}menuv;

void menuv_init(menuv* this, menu_item* items, wRect* w);

#endif /* __MENUV_H__ */
