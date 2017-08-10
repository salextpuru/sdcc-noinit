#include "scenes.h"
#include "sprites.h"
#include "hero.h"

// Текущий экран
scrPlan curScene;

/**
 *	Карта кодируется символами:
 *
 *	D - черт (devil) Не более 10 шт
 * 	M - человек (MAN)
 * 	T - сундук (treasure)
 * 	L - лестница
 *
 * 	b - Кирпич неуничтожимый [count8]
 * 	B - Кирпич уничтожимый [count8]
 *	U - верхний поручень [count8]
 * 	' ' (пробел) - пустое место [count8]
 *
 * 	count8 - после символа идет один байт-счетчик
 *
 * 	Программа кодирует карту на основе текстового файла
 *
 * 	остальные символы - не кодируются
*/

void scn_decomp ( uint8_t* scnz, scrPlan scn ) {
	uint8_t c;
	uint16_t i;
	uint8_t counter;
	uint8_t* ptr;

	ptr= ( uint8_t* ) scn;

	i=0;
	while ( i<sizeof ( scrPlan ) ) {
		c=* ( scnz++ );
		switch ( c ) {
		// Неподсчитываемые символы
		case 'D':
		case 'M':
		case 'T':
		case 'L': {
			* ( ptr++ ) =c;
			i++;
			break;
		}

		// Подсчитываемые символы
		case 'b':
		case 'B':
		case 'U':
		case ' ': {
			counter=* ( scnz++ );
			while ( ( i<sizeof ( scrPlan ) ) && ( counter!=0 ) ) {
				* ( ptr++ ) =c;
				i++;
				counter--;
			}

			break;
		}
		default:
			;
		}
	}
	//
}

void draw_scene_block ( const scrPlan scn, uint8_t x, uint8_t y ) {
	switch ( scn[y][x] ) {
	case 'B':
	case 'b': {
		spr0_out0_attr ( &spr_brick, x, y );
		break;
	}
	case 'L': {
		spr0_out0_attr ( &spr_ladder, x, y );
		break;
	}
	case 'T': {
		spr0_out0_attr ( &spr_treasure, x, y );
		break;
	}
	case 'U': {
		spr0_out0_attr ( &spr_upholder, x, y );
		break;
	}
	default:
		// Ничто
		spr0_out0_attr ( &spr_empty, x, y );
		;
	}
}

void draw_scene ( const scrPlan scn ) {
	uint8_t x;
	uint8_t y;

	scrCLS();

	for ( y=0; y<sceneH; y++ ) {
		for ( x=0; x<sceneW; x++ ) {
			draw_scene_block(scn, x,y);
		}
	}
}

// Сколько сундуков надо собрать?
uint8_t howTreasures;

void setScene ( uint8_t* scnz ) {
	uint8_t x;
	uint8_t y;

	hero_x=16;
	hero_y=16;

	// memcpy(&plane, &scene_0, sizeof(scrPlan));
	scn_decomp ( scnz, curScene );

	// Анализ карты
	howTreasures=0;
	for ( y=0; y<sceneH; y++ ) {
		for ( x=0; x<sceneW; x++ ) {
			switch ( curScene[y][x] ) {
			// Сундук
			case 'T': {
				howTreasures++;
				break;
			}
			// Черт
			case 'D': {
				break;
			}
			// Герой
			case 'M': {
				hero_x=x;
				hero_y=y;
				curScene[y][x]=' ';
				break;
			}
			}
		}
	}

	draw_scene(curScene);
}

