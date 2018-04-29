#include <menuv.h>
#include <im2.h>

#include "multimenu.h"

// =1 - PS2 клавиатура
// =0 - ZX  клавиатура
#define PS2_KEYS	0

#if PS2_KEYS
	#include <keybops2.h>
#else
	#include <keybozx.h>
	#include <zxkbd.h>
#endif

// Простое окно
static const wRect	simple_window_rect= {{4,4},{24,16}};
static window	simple_window;

static void simple_window_draw(window* this) {
	window_draw(this);
	this->at(this, 3, 2 );
	this->puts(this, "This");
	this->at(this, 3, 4 );
	this->puts(this, "is");
	this->at(this, 3, 6 );
	this->puts(this, "Simple");
	this->at(this, 3, 8 );
	this->puts(this, "Window");
}

void simple_windowExec(struct menuv* m) {
	window_init(&simple_window);
	window_setsize(&simple_window,&simple_window_rect);
	window_set_color(&simple_window,000,0106);
	simple_window.border = btSingl;
	simple_window.winFlags&=~wflagActivate; // Оно не может быть активным
	simple_window.draw = simple_window_draw;
	simple_window.exec(&simple_window);
}

// Основное меню
static menuv	m1;
static const wRect	m1rect={{0,0},{32,24}};
static const menu_item	m1items[]={
	{"Simple window", simple_windowExec},
	{"Go to Multi Menu", multiMenuExec },
	{"Exit",0},
	//
	{0,0},
};

int main(int argc, char* argv[]){
	// Драйвер экрана
	setScrDriverZX();
	// Драйвер клавиатуры
#if PS2_KEYS
	setKeyboardPS2();
#else
	setKeyboardZX();
	im2SetHandler(zxKbdScan);
	im2Set();
#endif
	SEI();
	
	menuv_init(&m1,m1items, &(m1rect));
	m1.header = "[ Menu 1 ]";
	m1.win.exec(&m1.win);
	
	return 0;
}
