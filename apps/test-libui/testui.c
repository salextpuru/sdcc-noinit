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

menuv	m1;

const wRect	m1rect={{0,0},{32,24}};
const menu_item	m1items[]={
	{"Empty item",0},
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
