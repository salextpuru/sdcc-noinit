/**
    @file win_class.c
    Класс-окно
*/
#include <win_class.h>

#define v2t(this)	((tWinClass*)this)
#define t2v(this)	((void*)this)

void tWinClass_Init(tWinClass* this){
	// Инициализация данных
	this->x=2;
	this->y=2;
	this->width=20;
	this->high=10;
	this->color=7;
	this->ccolor=56;
	this->cx=0;
	this->cy=0;
	this->ctype=ctnone;
	
	// Виртуальные методы
	this->Draw = t2v(tWinClass_Draw);
	
	// Предок
	tBaseClass_Init(&(this->parent));
	
	// tWinClass
	this->parent.classid = getClassId(tWinClass_Init);
}

void tWinClass_Draw(void* this){
	txt_screen_driver->curset(v2t(this)->ccolor,ctnone);
	txt_screen_driver->clear_window( v2t(this)->x,v2t(this)->y,
					v2t(this)->width,v2t(this)->high);
	txt_screen_driver->curpos(v2t(this)->cx + v2t(this)->x,
				  v2t(this)->cy + v2t(this)->y);
	txt_screen_driver->curset(v2t(this)->ccolor,v2t(this)->ctype);
}
