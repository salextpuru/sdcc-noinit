/**
    @file win_class.c
    Класс-окно
*/
#include <win_class.h>


void tWindowDraw(tWindow* this){
	txt_screen_driver->curset(this->ccolor,ctnone);
	txt_screen_driver->clear_window(this->x, this->y, this->width,this->high);
	txt_screen_driver->curpos(this->cx + this->x, this->cy + this->y);
	txt_screen_driver->curset(this->ccolor,this->ctype);
}
