#include "window.h"
#include <string.h>

// Деструктор окна
void window_destructor(window* this){
	window** p=this->childs;
	if(p) while(*p){
		if((*p)->destructor) (*p)->destructor(*p);
		p++;
	}
}

// метод рисования окна
void window_draw(window* this){
	txt_screen_driver->ink = this->ink;
	txt_screen_driver->paper = this->paper;
	txt_screen_driver->clear_window(this->x,this->y,this->w,this->h);
	txt_screen_driver->border(this->border, this->x,this->y,this->w,this->h);
}

static void window_exec_send_to_childs(window* this, event* ev){
	window** p=this->childs;
	if(p) while(*p){
		if((*p)->hEvent) (*p)->hEvent(*p, ev);
		p++;
	}
}

static void window_exec_send_to_cur_child(window* this, event* ev){
	window** p=this->childs;
	int16_t cur=this->cur_child;
	//
	if( ( cur<0 ) || (!p) ) {
		return;
	}
	//
	p+=cur;
	
	if( (*p) -> hEvent ){
		(*p) -> hEvent ( *p, ev );
	}
}

// запуск цикла обработки событий
void window_exec(window* this){
	event ev;
	ev.ev = evEmpty;
	
	if(this->activate) this->activate(this);
	//
	while( ev.ev != evClose ){
		// Получить событие
		this->getEvent(this, &ev);
		
		// Ожидание рассылаем всем
		if( ev.ev == evIdle ){
			window_exec_send_to_childs(this, &ev);
		}
		else {
			window_exec_send_to_cur_child(this, &ev);
		}
		
		// Обрабатываем сами
		this->hEvent(this,&ev);
		
	}
	//
	if(this->deactivate) this->deactivate(this);
}

// вызывается когда окно становится активным
void window_activate(window* this){
	this->draw(this);
}

// получить событие
void window_getEvent(window* this, event* ev){
	ev->ev = evKbd;
	ev->key = 0;
	while( ev->key == 0 ){
		// ev->key = InKey();
	}
}
	
// обработать событие
void window_hEvent(window* this, event* ev){
	if(ev->ev == evKbd){
		// ESC - EXIT (default)
		if( ev->key == '\x1B' )	ev->ev = evClose;
	}
}


static const window window_init_data = {
/* Данные окна */

	/** @brief Положение и размер */
	//uint8_t  x;
	.x = 0,
	//uint8_t  y;
	.y = 0,
	//uint8_t  w;
	.w = 32,
	//uint8_t  h;
	.h = 24,
	
	/** @brief фон	 */
	//tColor		paper;
	.paper = 8,
	
	/** @brief тон	 */
	//tColor		ink;
	.ink = 6,
	
	/** @brief тип рамки */
	//borderTypes	border;
	.border = btNone,
	
	/** @brief окна-потомки (списко заканчивается NULL) */
	//struct window**		childs;
	.childs=(struct window**)0,
	
	/** @brief текущий потомок (-1 - нет такого) */
	//int16_t			cur_child;
	.cur_child=-1,
	
/* Методы окна */
	/** @brief деструктор */
	//void (*destructor)(struct window* this);
	.destructor = window_destructor,

	/** @brief метод рисования окна */
	//void (*draw)(struct window* this);
	.draw = window_draw,
	
	/** @brief запуск цикла обработки событий */
	//void (*exec)(struct window* this);
	.exec = window_exec,
	
	/** @brief вызывается когда окно становится активным */
	//void (*activate)(struct window* this);
	.activate = window_activate,
	
	/** @brief вызывается когда окно становится пассивным */
	//void (*deactivate)(struct window* this);
	.deactivate = (void*)0,
	
	/** @brief получить событие */
	//void (*getEvent)(struct window* this, event* ev);
	.getEvent = window_getEvent,
	
	/** @brief обработать событие */
	//void (*hEvent)(struct window* this, event* ev);
	.hEvent = window_hEvent
};

// Конструктор окна
void window_init(window* this){
	memcpy(this, &window_init_data, sizeof(struct window) );
}


