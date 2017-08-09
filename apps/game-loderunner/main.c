#include <stdint.h>
#include <color.h>
#include <conio.h>
#include <zxkbd.h>
#include <im2.h>
//
#include "music.h"
#include "hero.h"
//
#include "scenes.h"
#include "scenesz.h"

// Отрисовка чертей
static void draw_devils(){
	
}

static void showStatus(){
	color(YELLOW);conio_at(0,22);print("TREASURES: ");
	color(YELLOW | 0x40);conio_at(11,22);putchar(howTreasures+'0');
	color(GREEN);conio_at(0,23);print("Demo Game of SDCC-NOINIT");
}

// Проверка - не поймал ли черт героя
static void check_collision(){
	// Собираем сундук
	if( hero_on == 'T' ){
		      howTreasures--;
		*hero_p = ' ';
		showStatus();
	}
	
	// Если все сундуки схвали - начинаем сначала
	// (потом переход на уровень дальше)
	if( howTreasures == 0 ){
		setScene(scn_scene_0);
		showStatus();
	}
}

static void im2Handler(){
	zxKbdScan();
	stc_music_check();
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
		check_hero();
		check_collision();
		//
		draw_scene(curScene);
		draw_hero();
		draw_devils();
		//
		scrFlip();
	}
}
