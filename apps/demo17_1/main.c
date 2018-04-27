#include <types.h>
#include <stdint.h>
#include <spr0.h>
#include <im2.h>

#include "ball1.h"
#include "ball2.h"
#include "ball3.h"
#include "letak.h"
#include "moln.h"

enum {
	sprPhases=4,
	sprites=5
};

// Структура положения спрайта
typedef struct {
	uint8_t		x;	// координаты
	uint8_t		y;
	int8_t		phase;	// текущая фаза (0..3)
	Sprite0**	phases; // Все фазы спрайта
	int8_t		sx;	// шаг по X
	int8_t		sy;	// шаг по Y
}sprMovie;

// Описания движения всех спрайтов
sprMovie sprMovies[sprites] = {
	{0,0,0,ball1,1,1},
	{4,4,0,ball2,0,1},
	{4,4,0,ball3,2,0},
	{8,8,0,letak,1,1},
	{12,12,0,moln,1,0},
};

int main() {
	uint8_t i;
	//
	spr0_set_scr_adr(0x6000);
	scr0_fill_atr(7);
	scr0_flip4000();
	
	SEI();
	
	while (1) {
		// Очистка только атрибутов! Это быстро, если фон однотонный
		scr0_fill_atr(0);
		
		// Вывод
		for(i=0; i<sprites; i++ ){			
			spr0_out0_attr( sprMovies[i].phases[sprMovies[i].phase],
					sprMovies[i].x,sprMovies[i].y);
			
			// Шагаем по X
			if( sprMovies[i].sx > 0 ){
				// Вправо
				sprMovies[i].phase++;
				// Шаг?
				if( sprMovies[i].phase >= sprPhases ){
					sprMovies[i].phase=0;
					sprMovies[i].x+=sprMovies[i].sx;
				}
			}else{
				// Влево
				sprMovies[i].phase--;
				// Шаг?
				if( sprMovies[i].phase < 0 ){
					sprMovies[i].phase=sprPhases-1;
					sprMovies[i].x+=sprMovies[i].sx;
				}
			}
			
			// Шагаем по Y
			sprMovies[i].y+=sprMovies[i].sy;
			
			// Меняем направлния, если достигнут край экрана
			if( ( sprMovies[i].sx > 0 ) && ( sprMovies[i].x >  29 ) ) {
				sprMovies[i].sx=-1;
			} else if( ( sprMovies[i].sx < 0 ) && ( sprMovies[i].x < 1 ) ) {
				sprMovies[i].sx=1;
			}
			
			if( ( sprMovies[i].sy > 0 ) && ( sprMovies[i].y >  21 ) ) {
				sprMovies[i].sy=-1;
			} else if( ( sprMovies[i].sy < 0 ) && ( sprMovies[i].y < 1 ) ) {
				sprMovies[i].sy=1;
			}
			
			
		}
		
		HALT();
		scr0_flip4000();
	}
	//
	return 0;
}
