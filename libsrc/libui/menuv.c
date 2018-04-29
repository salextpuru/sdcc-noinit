#include <keyboard.h>
#include <string.h>

#include "menuv.h"

static void menuv_draw_item(window* this, uint16_t n, uint8_t show) {
	menuv* parent = this->child_ifparent;
	uint8_t w = this->w-2;
	uint8_t l = strlen(parent->items[n].name);
	char s[0x21];
	memset(s,' ', 0x21);
	strncpy(s, parent->items[n].name, (w<=l)?w:l );
	s[w]=0;
	
	window_at(this,1,n-parent->item_first+1);
	
	if( show ) {
		txt_screen_driver->ink = parent->curInk;
		txt_screen_driver->paper = parent->curPaper;
	}
	else {
		txt_screen_driver->ink = this->ink;
		txt_screen_driver->paper = this->paper;
	}
	
	window_puts(this, s);
}

static uint8_t menuv_check(window* this) {
	menuv* parent = this->child_ifparent;
	uint16_t first = parent->item_first;
	uint16_t cur = parent->item_current;
	
	uint8_t rv=0;
	
	if( first>cur ){
		first=cur;
		rv=1;
	}
	
	if( (first + this->h-2) <= cur ){
		first = cur - this->h + 3;
		rv=1;
	}
	if( rv ) {
		parent->item_first = first;
		parent->item_current = cur;
	}
	
	return rv;
}

static void menuv_draw_items(window* this) {
	menuv* parent = this->child_ifparent;
	uint16_t first = parent->item_first;
	uint16_t cur = parent->item_current;
	
	uint16_t	i;
	
	for(i=first; i<(first+(this->h)-2); i++){
		if( i >= (parent->item_count) ){
			break;
		}
		window_at(this,1,i-first+1);
		if( i != cur ){
			menuv_draw_item(this, i, 0);
		}
	}
	
	if( this->winFlags & wflagActive ){
		menuv_draw_item(this, cur, 1);
	}
	else {
		menuv_draw_item(this, cur, 0);
	}
}

// Методы окна (переопределены)
static void menuv_draw(window* this) {
	menuv* parent = this->child_ifparent;
	uint16_t first = parent->item_first;
	uint16_t cur = parent->item_current;
	
	window_draw(this);
	
	if( parent->header ) {
		window_at(this,2,0);
		window_puts(this, parent->header );
	}
	
	if( ! parent->item_count ) {
		return;
	}
	
	menuv_draw_items(this);
}

static void menuv_exec(window* this) {
	menuv_check(this);
	window_exec(this);
}

static void menuv_hEvent(window* this, event* ev) {
	menuv* parent = this->child_ifparent;
	
	if(ev->ev == evKbd) switch(ev->key) {
		case kbdESC:{
			parent->exit_code=menuCodeESC;
			break;
		}
		
		case 0x0D:{
			if( parent->items[ parent->item_current ].handler ){
				parent->items[ parent->item_current ].handler( parent );
				menuv_draw(this);
			}
			else if(parent->exitOnEnter) {
				parent->exit_code=menuCodeEnter;
				ev->key=kbdESC;
			}
			break;
		}
		
		case kbdUP:{
			if(!parent->item_current) break;
			menuv_draw_item(this, parent->item_current, 0);
			parent->item_current--;
			if( menuv_check(this) ){
				menuv_draw_items(this);
			}else{
				menuv_draw_item(this, parent->item_current, 1);
			}
			break;
		}
		
		case kbdDN:{
			if( parent->item_current >= (parent->item_count-1) )break;
			menuv_draw_item(this, parent->item_current, 0);
			parent->item_current++;
			if( menuv_check(this) ){
				menuv_draw_items(this);
			} else {
				menuv_draw_item(this, parent->item_current, 1);
			}
			
			break;
		}
	}
	
	window_hEvent(this,ev);
}

static void menuv_activate(window* this) {
	window_activate(this);
	menuv_draw_item(this, ((menuv*)(this->child_ifparent))->item_current, 1);
}

static void menuv_deactivate(window* this) {
	menuv_draw_item(this, ((menuv*)(this->child_ifparent))->item_current, 0);
	window_deactivate(this);
}

// Методы меню
/** пересчитывает количество элементов меню */ 
static void menuv_items_calc(menuv* this) {
	uint16_t item_count=0;
	menu_item* cit=this->items;
	
	if( cit )  while (cit->name) {
		item_count++;
		cit++;
	}
	
	this->item_count = item_count;
	
	if( this->item_first >= item_count ) {
		this->item_first = item_count?item_count-1:0;
	}
}

void menuv_init(menuv* this, menu_item* items, wRect* w) {
	memset(this, 0, sizeof(menuv) );
	window_init(&this->win);
	this->win.child_ifparent = this;
	
	window_setsize(&this->win,w);
	this->win.border = btDoubl;
	this->win.ink = 0106;
	
	// Виртуальные методы (private!:)
	this->win.draw = menuv_draw;
	this->win.activate = menuv_activate;
	this->win.deactivate = menuv_deactivate;
	this->win.exec = menuv_exec;
	this->win.hEvent = menuv_hEvent;
	//
	this->items = items;
	menuv_items_calc(this);
	//
	this->curInk = 0;
	this->curPaper = 6;
}
