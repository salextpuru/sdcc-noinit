#include <stdint.h>
#include <color.h>
#include <conio.h>
#include <zxkbd.h>
#include <im2.h>
//
#include "music.h"
#include "hero.h"
#include "devils.h"
//
#include "scenes.h"
#include "scenesz.h"

static void showStatus(){
	color(YELLOW);conio_at(0,22);print("TREASURES: ");
	color(YELLOW | 0x40);conio_at(11,22);putchar(howTreasures+'0');
	color(GREEN);conio_at(0,23);print("Demo Game of SDCC-NOINIT");
}

// Проверка - не поймал ли черт героя
static void check_collision(){
	// Собираем сундук
	if( point_on == 'T' ){
		      howTreasures--;
		*point_p = ' ';
		//
		showStatus();
	}
	
	// Если все сундуки схвали - начинаем сначала
	// (потом переход на уровень дальше)
	if( howTreasures == 0 ){
		setScene(scn_scene_0);
		showStatus();
	}
}

// Случайное число (доделать)
uint16_t pseudoRand;

static void im2Handler(){
	zxKbdScan();
	stc_music_check();
	//
	pseudoRand ^= 0xA55A;
	pseudoRand += 0x3C67;
}

void main(){
	// Init screen
	scrInit();
	
	// Init keyboard on IM2
	im2SetHandler(im2Handler);
	im2Set();
	SEI();

	// Set Level
	setScene(scn_scene_0);
	showStatus();
	
	// Loop
	while(1){
		// Ждем кадра
		HALT();
		//
		check_devils();
		check_hero();
		check_collision();
		scrFlip();
	}
}
