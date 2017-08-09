#include <stdint.h>
#include <color.h>
#include <spr0.h>
#include <zxkbd.h>
#include <im2.h>
#include <string.h>
#include <conio.h>

#include "music.h"
#include "scrHelper.h"
#include "scenes.h"
#include "scenesz.h"
#include "sprites.h"

// Клавиши управления
enum {
	kUp='7',
	kDown='6',
	kLeft='5',
	kRight='8'
};


Sprite0 spr = {
	.sz=9+sizeof(Sprite0),
	.w=1,
	.h=1,
	.datap={0,1,2}
};

// Текущий экран
static scrPlan plane;

// Координаты героя
static uint8_t hero_x;
static uint8_t hero_y;

// Отрисовка героя
static void draw_hero(){
	spr0_out0_attr(&spr_hero, hero_x, hero_y);
}

// Отрисовка чертей
static void draw_devils(){
	
}

// Обработка клавиш
static void check_key(){
	uint8_t key = zxKbdInKey();
	
	switch(key){
		case kLeft:{
			uint8_t blk;
			if(hero_x<=0){
				break;
			}
			
			blk = plane[hero_y][hero_x-1];
			
			switch (blk){
				// Низзя!
				case 'b':
				case 'B':
					break;
				//
				default:
					hero_x--;
			}
			break;
		}
		case kRight:{
			uint8_t blk;
			if(hero_x>=(sceneW-1)){
				break;
			}
			
			blk = plane[hero_y][hero_x+1];
			
			switch (blk){
				// Низзя!
				case 'b':
				case 'B':
					break;
				//
				default:
					hero_x++;
			}
			
			break;
		}
		case kUp:{
			uint8_t blk;
			uint8_t blk1;
			
			if(hero_y<=0){
				break;
			}
			
			blk = plane[hero_y][hero_x];
			blk1 = plane[hero_y-1][hero_x];
			
			// Поднимаемся только по лесенкам
			if( blk=='L' ) switch (blk1){
				case 'b':
				case 'B':
					break;
				default:
					hero_y--;
			}
			
			break;
		}
		case kDown:{
			uint8_t blk1;
			if(hero_y>=(sceneH-1)){
				break;
			}
			blk1 = plane[hero_y+1][hero_x];
			// Опускаемся только по лесенкам
			switch (blk1){
				case 'b':
				case 'B':
					break;
				case 'L':
					hero_y++;
					break;
				default:;
			}
			
			break;
		}
	}
}

// Сколько сундуков надо собрать?
static uint8_t treasures;

static void showStatus(){
	color(YELLOW);conio_at(0,22);print("TREASURES: ");
	color(YELLOW | 0x40);conio_at(11,22);putchar(treasures+'0');
	color(GREEN);conio_at(0,23);print("Demo Game of SDCC-NOINIT");
}

// Проверка движения (падение и проч)
static void check_hero(){
	uint8_t blk;
	uint8_t blk1;
	
	blk = plane[hero_y][hero_x];
	blk1 = plane[hero_y+1][hero_x];
	
	// Собираем сундук
	if( blk == 'T' ){
		treasures--;
		plane[hero_y][hero_x] = ' ';
		showStatus();
	}
	
	// Падаем? 
	if( ( blk == ' ' ) && ( blk1 == ' ' ) ){
		// да
		hero_y++;
	}
	else{
		// Не падаем. Проверка клавиатуры
		check_key();
	}
	
}

// Тут пока только один уровень
static void setScene(){
	uint8_t x;
	uint8_t y;
	
	hero_x=16;
	hero_y=16;
	
	// memcpy(&plane, &scene_0, sizeof(scrPlan));
	scn_decomp(scn_scene_0, plane);
	
	// Анализ карты
	treasures=0;
	for(y=0; y<sceneH; y++){
		for(x=0; x<sceneW; x++){
			switch(plane[y][x]){
				// Сундук
				case 'T':{
					treasures++;
					break;
				}
				// Черт
				case 'D':{
					break;
				}
				// Герой
				case 'M':{
					hero_x=x;
					hero_y=y;
					plane[y][x]=' ';
					break;
				}
			}
		}
	}
	
	
}

// Проверка - не поймал ли черт героя
static void check_collision(){
	// Если все сундуки схвали - начинаем сначала
	// (потом переход на уровень дальше)
	if( treasures == 0 ){
		setScene();
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
	setScene();
	showStatus();
	
	// Loop
	while(1){
		check_hero();
		
		draw_scene(plane);
		
		draw_hero();
		
		draw_devils();
		
		check_collision();
		
		scrFlip();
	}
}
