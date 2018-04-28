#include <window.h>
#include <menuv.h>
#include <im2.h>

// =1 - PS2 клавиатура
// =0 - ZX  клавиатура
#define PS2_KEYS	0

#if PS2_KEYS
	#include <keybops2.h>
#else
	#include <keybozx.h>
	#include <zxkbd.h>
#endif

window	w1;
menuv	m1;

void handler1(struct menuv* m);
void handler2(struct menuv* m);

const wRect	m1rect={{4,4},{24,18}};
const menu_item	m1items[]={
	{"Item 1",0},
	{"Go menu 2",handler1},
	{"Item 3",0},
	{"Item 4 very long item name",0},
	{"Item 5",0},
	{"Go to menu 3",handler2},
	{"Item 7",0},
	{"Item 8",0},
	{"Item 9",0},
	{"Item 10",0},
	{"Item 11",0},
	{"Item 12",0},
	{"Item 13",0},
	{"Item 14",0},
	{"Item 15",0},
	{"Item 16 very long item name",0},
	{"Item 17",0},
	{"Item 18",0},
	{"Item 19",0},
	{"Item 20 very long item name ",0},
	//
	{0,0},
};

menuv	m2;
const wRect	m2rect={{6,6},{16,10}};
const menu_item	m2items[]={
	{"Item 1",0},
	{"Item 2",0},
	{"Item 3",0},
	//
	{0,0},
};

void handler1(struct menuv* m) {
	menuv_init(&m2,m2items, &(m2rect));
	m2.header = "[ Menu 2 ]";
	window_set_color(&m2.win, 001, 060);
	m2.win.exec(&m2.win);
}

menuv	m3;
const wRect	m3rect={{10,10},{16,10}};
const menu_item	m3items[]={
	{"Item 1",0},
	{"Item 2",0},
	{"Item 3",0},
	//
	{0,0},
};

void handler2(struct menuv* m) {
	menuv_init(&m3,m3items, &(m3rect));
	m3.header = "[ Menu 3 ]";
	window_set_color(&m3.win, 02, 040);
	m3.win.exec(&m3.win);
}

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
	//
	window_init(&w1);
	w1.border = btSingl;
	window_draw(&w1);
	
	menuv_init(&m1,m1items, &(m1rect));
	m1.header = "[ Menu 1 ]";
	m1.win.exec(&m1.win);
	
	return 0;
}
