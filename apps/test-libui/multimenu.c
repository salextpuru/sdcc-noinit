#include "multimenu.h"

// Фоновое окно
static window mm_win, info_win;
// 4 Меню
static menuv  m1,m2,m3;

// Потомки Фонового окна
static const window* mm_win_childs[] = {&(m1.win), &(m2.win), &(m3.win), &info_win , 0 };

// Элементы меню 1
static const wRect	m1rect= {{2,2},{12,8}};
static const menu_item	m1items[]= {
	{"Меню 1.1",0},
	{"Меню 1.2",0 },
	{"Меню 1.3",0},
	{"Меню 1.4",0},
	{"Меню 1.5",0 },
	{"Меню 1.6",0},
	//
	{0,0},
};

// Элементы меню 2
static const wRect	m2rect= {{18,2},{12,8}};
static const menu_item	m2items[]= {
	{"Меню 2.1",0},
	{"Меню 2.2",0 },
	{"Меню 2.3",0},
	{"Меню 2.4",0},
	{"Меню 2.5",0 },
	{"Меню 2.6",0},
	//
	{0,0},
};

// Элементы меню 3
static const wRect	m3rect= {{2,14},{12,8}};
static const menu_item	m3items[]= {
	{"Меню 3.1",0},
	{"Меню 3.2",0 },
	{"Меню 3.3",0},
	{"Меню 3.4",0},
	{"Меню 3.5",0 },
	{"Меню 3.6",0},
	//
	{0,0},
};
// Окно с информацией
static const wRect	info_win_rect= {{18,14},{12,8}};

static void info_win__draw(window* this) {
	window_draw(this);
	this->at(this, 3, 0 );
	this->puts(this, "Информ.");
	this->at(this, 2, 2 );
	this->puts(this, "Это окно");
	this->at(this, 4, 3 );
	this->puts(this, "не");
	this->at(this, 2, 4 );
	this->puts(this, "активно!");
}

void multiMenuExec(struct menuv* m) {
	//
	menuv_init(&m1,m1items,&m1rect);
	window_set_color(&m1.win,0130,000);
	m1.header = "[ Меню 1 ]";
	
	menuv_init(&m2,m2items,&m2rect);
	window_set_color(&m2.win,0160,001);
	m2.header = "[ Меню 2 ]";
	
	menuv_init(&m3,m3items,&m3rect);
	window_set_color(&m3.win,0120,0107);
	m3.header = "[ Меню 3 ]";
	//
	window_init(&info_win);
	window_setsize(&info_win,&info_win_rect);
	window_set_color(&info_win,040,000);
	info_win.border = btSingl;
	info_win.winFlags&=~wflagActivate; // Оно не может быть активным
	info_win.draw = info_win__draw;
	//
	window_init(&mm_win);
	window_set_color(&mm_win,000,050);
	// добавляем потомков и делаем активным первого из них
	mm_win.childs=mm_win_childs;
	mm_win.cur_child=0;
	//
	window_exec(&mm_win);
}
