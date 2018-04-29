#include "window.h"
#include <string.h>
#include <keyboard.h>

#define getu8(v) ((uint8_t)(v))

// Деструктор окна
void window_destructor(window* this) {
	window** p=this->childs;
	if (p) while (*p) {
			if ((*p)->destructor) (*p)->destructor(*p);
			p++;
		}
}

void window_clear(window* this) {
	txt_screen_driver->clear_window(
	        this->x,this->y,
	        this->w,this->h);
}

// метод рисования окна
void window_draw(window* this) {
	window** p=this->childs;

	txt_screen_driver->ink = this->ink;
	txt_screen_driver->paper = this->paper;
	txt_screen_driver->clear_window(
	        this->x,this->y,
	        this->w,this->h);
	txt_screen_driver->border(this->border,
	                          this->x,this->y,
	                          this->w,this->h);

	if ( ( (this->cur_child)<0 ) || (!p) || (!*p) ) {
		return;
	}

	while ( *p ) {
		if ( ( *p ) && ( (*p)->draw ) ) {
			(*p)->draw(*p);
		}
		p++;
	}
}

static void window_exec_send_to_childs(window* this, event* ev) {
	window** p=this->childs;
	if (p) while (*p) {
			if ((*p)->hEvent) (*p)->hEvent(*p, ev);
			p++;
		}
}

static void window_exec_send_to_cur_child(window* this, event* ev) {
	window* p=window_get_cur_child(this);

	if ( ( p ) && ( p->hEvent ) && (p->winFlags & wflagActivate ) ) {
		p->hEvent ( p, ev );
	}
}

// запуск цикла обработки событий
void window_exec(window* this) {
	event ev;
	ev.ev = evEmpty;

	if (this->activate) this->activate(this);
	//
	while ( ev.ev != evClose ) {
		// Получить событие
		this->getEvent(this, &ev);

		// Ожидание рассылаем всем
		if ( ev.ev == evIdle ) {
			window_exec_send_to_childs(this, &ev);
		} else {
			window_exec_send_to_cur_child(this, &ev);
		}

		// Обрабатываем сами
		this->hEvent(this,&ev);

	}
	//
	if (this->deactivate) this->deactivate(this);
}

// вызывается когда окно становится активным
void window_activate(window* this) {
	window* p=window_get_cur_child(this);

	this->winFlags |= wflagActive;

	this->draw(this);
	if ( p && (p->activate) ) {
		p->activate(p);
	}
}

void window_deactivate(window* this) {
	window* p=window_get_cur_child(this);
	if ( p && (p->deactivate) ) {
		p->deactivate(p);
	}
	this->winFlags &= ~wflagActive;
}

// получить событие
void window_getEvent(window* this, event* ev) {
	ev->ev = evKbd;
	ev->key = 0;
	// получаем событие от клавиатуры
	if ( keyboardDriver ) while ( ev->key == 0 ) {
			ev->key = keyboardDriver->InKey();
		}
}

// обработать событие
void window_hEvent(window* this, event* ev) {
	if (ev->ev == evKbd) {
		// Если вдруг, то закрываем
		switch ( ev->key ) {
		case kbdESC: {
			ev->ev = evClose;
			break;
		}
		case kbdLEFT: {
			window_prev_child(this);
			break;
		}
		case kbdRIGHT: {
			window_next_child(this);
			break;
		}
		}
	}
}

// Печать строки в окне (за пределы не выходим)
uint8_t window_puts(struct window* this, const char* s) {
	uint8_t x=this->cur_x;
	uint8_t y=this->cur_y;
	uint8_t w=this->w;
	uint8_t h=this->h;
	uint8_t x0=x;
	//
	if ( y>=h ) {
		return 0;
	}
	txt_screen_driver->cur_x=x+this->x;
	txt_screen_driver->cur_y=y+this->y;

	while ( s && (*s) && (x<w) ) {
		txt_screen_driver->putc(*s);
		s++;
		x++;
		txt_screen_driver->cur_x++;
	}

	// Возвращаем количество символов
	this->cur_x=x;
	return x-x0;
}

// Установка позиции курсора в окне (за пределы не выходим)
void window_at(struct window* this, uint8_t x, uint8_t y) {
	this->cur_x = x;
	this->cur_y = y;
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

	/** @brief Позиция курсора внутри окна */
	.cur_x=0,
	.cur_y=0,

	/** @brief фон	 */
	//tColor		paper;
	.paper = 010,

	/** @brief тон	 */
	//tColor		ink;
	.ink = 006,

	/** @brief тип рамки */
	//borderTypes	border;
	.border = btNone,

	/** @brief окна-потомки (списко заканчивается NULL) */
	//struct window**		childs;
	.childs=(struct window**)0,

	/** @brief текущий потомок (-1 - нет такого) */
	//int16_t			cur_child;
	.cur_child=-1,

	/** Указатель на потомка, если окно чей-то предок */
	.child_ifparent=NULL,

	/** Флаги отображения */
	.winFlags=wflagActivate,

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
	.deactivate = window_deactivate,

	/** @brief получить событие */
	//void (*getEvent)(struct window* this, event* ev);
	.getEvent = window_getEvent,

	/** @brief обработать событие */
	//void (*hEvent)(struct window* this, event* ev);
	.hEvent = window_hEvent,

	/** @brief Печать строки в окне (за пределы не выходим) */
	.puts=window_puts,

	/** @brief Установка позиции курсора в окне (за пределы не выходим) */
	.at=window_at
};

void window_setsize(window* this, wRect* w) {
	if ( (!this) || (!w) ) {
		return;
	}
	this->x = w->point.x;
	this->y = w->point.y;
	this->w = w->size.w;
	this->h = w->size.h;
}

void window_store_color(window* this, tColor* ink, tColor* paper) {
	*ink = this->ink;
	*paper = this->paper;
}

void window_set_color(window* this, tColor ink, tColor paper) {
	this->ink=ink;
	this->paper=paper;
}

window * window_get_cur_child(window* this) {
	window** p=this->childs;
	int16_t cur=this->cur_child;
	//
	if ( ( cur<0 ) || (!p) || (!*p) ) {
		return NULL;
	}
	//
	return ( *(p + cur) );
}

uint8_t window_next_child(window* this) {
	window*  w;
	uint8_t rv=0;
	window** p=this->childs;
	int16_t cur=this->cur_child;

	if ( ( cur<0 ) || (!p) || (!*p) ) {
		return 0;
	}

	w=*(p+cur);
	if( ( w->deactivate ) && (w->winFlags & wflagActivate ) ) w->deactivate(w);

	while ( !((*(p + (++cur) ))->winFlags & wflagActivate )) {
		if ( !*(p+cur) ) {
			break;
		}
	}

	w=*(p+cur);


	if ( w  ) {
		rv=1;
	} else {
		cur=0;
		w=*(p+cur);
		rv=2;
	}

	this->cur_child = cur;

	if( ( w->activate ) && (w->winFlags & wflagActivate ) ) w->activate(w);

	return rv;
}

uint8_t window_prev_child(window* this) {
	
}

// Конструктор окна
void window_init(window* this) {
	memcpy(this, &window_init_data, sizeof(window) );
}
