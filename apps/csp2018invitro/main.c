#include <types.h>
#include <string.h>
#include <stdint.h>
#include <spr0.h>
#include <im2.h>

#include "cspLogo.h"
#include "winprocs.h"
#include "spr2018.h"
#include "uSctrollText.h"
#include "logos.h"
#include "spr0_fade.h"

/**
 * -------------------------------- Эквалайзер ------------------------------------------
 */

/*
 * Количество буковок в эквалайзере
 */
enum {boxSize=7};

/*
 * Координаты и размеры буковок в эквалайзере
 */
static const struct {
	uint8_t x;
	uint8_t y;
	uint8_t w;
	uint8_t h;
} boxText[boxSize] = {
	{0,16,6,6},
	{6,16,4,6},
	{10,16,4,6},

	{16,16,4,6},
	{20,16,4,6},
	{24,16,4,6},
	{28,16,4,6},
};

// Defines for music.c
extern void (*music_im2h)();
uint8_t checkMusic();

/**
* Пролцедура получения дампа AY
*/
static uint8_t ayRgDump[0x10];
static void getAYdump() __naked {
	__asm;
	ld	e,#0x00 ; // Номер регистра
	ld	hl,#_ayRgDump ; // Адрес массива
	ld	bc,#0xFFFD ;// #FFFD - регистр адреса #BFFD - регистр данных
	ay_dump_loop1:
	;//
	ld	a,e
	out	(c),a
	in	a,(c)
	and	a,#0x0F
	ld	(hl),a
	;//
	inc	hl
	inc	e
	ld	a,#0x0E
	cp	a,e
	jr	nz, ay_dump_loop1
	ret
	__endasm;
}

/*
 * Таблица цветов для эквалайзера
 */
static const uint8_t colorTable[0x10]= {1,1,2,3,4,5,6,7,0101,0101,0102,0103,0104,0105,0106,0107};

/*
 * Смена картинок
 */
static uint16_t logos_timer;
static uint8_t logos_counter;

/*
 * Обработчик прерывания 1/50 сек
 */
void candle_flame_animate();

static void im2userHandler() {
	// Переменная, блокирующая повторный запуск фоновых процедур
	static volatile uint8_t lock;

	// Играем следующий кусочек музыки
	if (music_im2h) {
		music_im2h();
	}

	// AY DUMP
	getAYdump();

	// Увеличиваем
	logos_timer++;
	
	// Разрешаем прерывания.
	SEI();

	// Проверка повторного вызова (это ж прерывания!)
	if ( !lock ) {
		// Блокируем повторный вход в этот участок кода
		lock=1;
		// Сдвиг текста
		CheckShiftText();

		// Эквалайзер (подкрашиваем буковки цветами, полученными их дампа AY)
		// Volume
		winSetAtr(boxText[0].x, boxText[0].y, boxText[0].w, boxText[0].h, colorTable[ayRgDump[8]], 0x07 );
		winSetAtr(boxText[1].x, boxText[1].y, boxText[1].w, boxText[1].h, colorTable[ayRgDump[9]], 0x07 );
		winSetAtr(boxText[2].x, boxText[2].y, boxText[2].w, boxText[2].h, colorTable[ayRgDump[10]], 0x07 );
		// Freq
		winSetAtr(boxText[3].x, boxText[3].y, boxText[3].w, boxText[3].h, colorTable[ayRgDump[1]], 0x07 );
		winSetAtr(boxText[4].x, boxText[4].y, boxText[4].w, boxText[4].h, colorTable[ayRgDump[3]], 0x07 );
		winSetAtr(boxText[5].x, boxText[5].y, boxText[5].w, boxText[5].h, colorTable[ayRgDump[5]], 0x07 );
		winSetAtr(boxText[6].x, boxText[6].y, boxText[6].w, boxText[6].h, colorTable[ayRgDump[6]], 0x07 );
		
		candle_flame_animate();
		
		// Разблокируем вход в этот участок кода
		lock=0;
	}
}

// Просто BORDER 0
void border0() __naked {
	__asm;
	xor a
	out (0xFE),a
	ret
	__endasm;
}

int main() {
	// Установки и настройки
	CLI();
	// Свой обработчик прерываний
	im2Set();
	im2SetHandler( im2userHandler );
	// Очистка экрана
	border0();
	winSetAtr(0, 0, 32, 24, 0x00, 0xFF );
	winClear(0,0,32,8);
	// Вывод картинок
	logoToScreen(3,0);
	spr0_out0_attr(&spr2018,0,16);
	spr0_out0_attr(&logos_base,0,8);
	winSetAtr(5, 8, 12, 8, 0x01, 0xFF );
	// Инициализация бегщей строки
	InitShiftText();
	// Разрешаем прерывания
	SEI();

	// Основной цикл
	while (1) {
		uint8_t i;
		// Проверка - доиграла ли до конца музыка
		// и надо ли переходить к следующей мелодии
		checkMusic();
		if( logos_timer >= 500 ){
			Sprite0* spr=logos[logos_counter];
			logos_timer=0;
			for(i=0; i<8; i++){
				spr0_fade_step(spr,5,8);
				HALT();
			}
			spr0_out0_attr(spr,5,8);
			
			if( (++logos_counter) >=  logos_count() ){
				logos_counter=0;
			}
		}
	}
	//
	return 0;
}
