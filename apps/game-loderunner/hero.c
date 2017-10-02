#include "hero.h"
#include "scenes.h"
#include "sprites.h"

// Окружение героя (ф-ця getMedia)
uint8_t point_on='b';
uint8_t point_up='b';
uint8_t point_dn='b';
uint8_t point_rt='b';
uint8_t point_lf='b';
uint8_t* point_p;

// Координаты героя
uint8_t hero_x;
uint8_t hero_y;

// Направление движения героя
enum {
	// Направление движения
	hdirNone=0,
	hdirLeft=1,
	hdirRight=2,
	hdirUp=3,
	hdirDn=4,
	
	// Количество спрайтов
	heroSprites=3
};
static	uint8_t direction=hdirNone;

// Номер спрайта анимации
static uint8_t spr_hero_num;

// Анимация движения влево
static Sprite0* spr_hero_left[heroSprites];

// Анимация движения вправо
static Sprite0* spr_hero_right[heroSprites];

// Анимация движения вверх
static Sprite0* spr_hero_up[heroSprites];

// Анимация движения вниз
static Sprite0* spr_hero_down[heroSprites];

// Обработка перемещения героя по клавишам
static void check_key(){
	uint8_t key = zxKbdInKey();
	
	switch(key){
		case kLeft:{
			if(direction==hdirRight){
				direction=hdirNone;
			}
			else{
				direction=hdirLeft;
			}
			
			switch ( point_lf ){
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
			if(direction==hdirLeft){
				direction=hdirNone;
			}
			else{
				direction=hdirRight;
			}
			
			switch ( point_rt ){
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
			uint8_t r=1;
			
			if(direction==hdirDn){
				direction=hdirNone;
			}
			else{
				direction=hdirUp;
			}
			
			// Не упремся башкой?
			switch ( point_up ){
				case 'b':
				case 'B':{
					r=0;
					break;
				}
			}
			
			if(!r){
				break;
			}
			
			// Поднимаемся только по лесенкам
			switch ( point_on ){
				case 'L':
				case 'U':
					hero_y--;
			}
			
			break;
		}
		case kDown:{
			uint8_t r=1;
			// Опускаемся только по лесенкам
			// Лесенка под героем или герой на лесенке
			
			if(direction==hdirUp){
				direction=hdirNone;
			}
			else{
				direction=hdirDn;
			}
			
			// Не упремся ногами?
			switch ( point_dn ){
				case 'b':
				case 'B':{
					// Упремся
					r=0;
					break;
				}
				case 'L':
				case 'U':{
					// Неа
					hero_y++;
					r=0;
				}
			}
			
			if(!r){
				break;
			}
			
			switch ( point_on ){
				case 'L':
				case 'U':
					hero_y++;
			}
			
			break;
		}
	}
}

// Проверка движения (падение и проч)
void check_hero(){
	// Получаем окружение героя
	getPointArea ( hero_x, hero_y );
	
	// Удаляем героя
	draw_scene_block(curScene, hero_x, hero_y);
	
	// Падаем? 
	if( ( point_on == ' ' ) && ( point_dn == ' ' ) ){
		// да
		hero_y++;
	}
	else{
		// Не падаем. Проверка клавиатуры
		check_key();
	}
	//
	spr0_out0_attr(&spr_hero, hero_x, hero_y);
}
