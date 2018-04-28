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

const wRect	m1rect={{4,4},{20,18}};
const menu_item	m1items[]={
	{"Item 1",0},
	{"Item 2",0},
	{"Item 3",0},
	{"Item 4 very long item name",0},
	{"Item 5",0},
	{"Item 6",0},
	{"Item 7",0},
	{"Item 8",0},
	{"Item 9",0},
	{"Item 10",0},
	{"Item 11",0},
	{"Item 12",0},
	{"Item 13",0},
	{"Item 14",0},
	{"Item 15",0},
	{"Item 16",0},
	{"Item 17",0},
	{"Item 18",0},
	{"Item 19",0},
	{"Item 20",0},
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
	//
	window_init(&w1);
	w1.border = btSingl;
	window_draw(&w1);
	//window_exec(&w1);

	menuv_init(&m1,m1items, &(m1rect));
	m1.header = "[ Header ]";
	m1.win.exec(&m1.win);
	
	return 0;
}
