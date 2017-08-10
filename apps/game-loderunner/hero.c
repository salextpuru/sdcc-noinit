#include "hero.h"
#include "scenes.h"
#include "sprites.h"

// Окружение героя (ф-ця getMedia)
uint8_t hero_on='b';
uint8_t hero_up='b';
uint8_t hero_dn='b';
uint8_t hero_rt='b';
uint8_t hero_lf='b';
uint8_t* hero_p;

// Координаты героя
uint8_t hero_x;
uint8_t hero_y;

// Направление движения героя
enum {
	hdirNone=0,
	hdirLeft=1,
	hdirRight=2,
	
	heroSprites=3
};
static	uint8_t direction=hdirNone;

// Номер спрайта анимации
static uint8_t spr_hero_num;

// Анимация движения влево
static Sprite0* spr_hero_left[heroSprites];
// Анимация движения вправо
static Sprite0* spr_hero_right[heroSprites];


// Получить окружение
void getMedia( uint8_t x, uint8_t y ){
	hero_p = &curScene[y][x];
	//
	hero_on = *hero_p;
	hero_lf = (x==0)?'b':*(hero_p-1);
	hero_rt = (x>=(sceneW-1))?'b':*(hero_p+1);
	hero_up = (y==0)?'b':*(hero_p-sceneW);
	hero_dn = (y>=(sceneH-1))?'b':*(hero_p+sceneW);
}

// Обработка перемещения героя по клавишам
static void check_key(){
	uint8_t key = zxKbdInKey();
	
	switch(key){
		case kLeft:{
			switch (hero_lf){
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
			switch (hero_rt){
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
			
			// Не упремся башкой?
			switch (hero_up){
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
			switch (hero_on){
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
			
			// Не упремся ногами?
			switch (hero_dn){
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
			
			switch (hero_on){
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
	getMedia( hero_x, hero_y );
	
	// Удаляем героя
	draw_scene_block(curScene, hero_x, hero_y);
	
	// Падаем? 
	if( ( hero_on == ' ' ) && ( hero_dn == ' ' ) ){
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
