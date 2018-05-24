#include <types.h>
#include <string.h>
#include <stdint.h>
#include <im2.h>
#include <zxkbd.h>
#include <winprocs.h>

#include "equalizer.h"
#include "cspLogo.h"
#include "spr2018.h"
#include "uSctrollText.h"
#include "logos.h"
#include "music.h"

/**
 * -------------------------------- Эквалайзер ------------------------------------------
 */

/*
 * Обработчик прерывания 1/50 сек
 */

static void im2userHandler() {
	// Переменная, блокирующая повторный запуск фоновых процедур
	static volatile uint8_t lock;

	// Играем следующий кусочек музыки
	if ( music_im2h ) {
		music_im2h();
	}

	// Увеличиваем
	logos_int50();

	// Проверка повторного вызова (это ж прерывания!)
	if ( lock ) {
		return;
	}

	// Блокируем повторный вход в этот участок кода
	lock=1;
	// Разрешаем прерывания.
	SEI();

	// Сдвиг текста
	CheckShiftText();

	// Отрисовка эквалайзера
	equalizer_draw();

	// анимация пламени свечи
	candle_flame_animate();

	// Шаг анимации ЛОГО
	logoAniStep();

	// Опрос клавиатуры (в фоне, т.к. только кнопочки 1-6 важны)
	zxKbdScan();
	// Проверка - а может надо сменить мелодию?
	keyMusic ( zxKbdInKey() );

	// Разблокируем вход в этот участок кода
	CLI();
	lock=0;
	SEI();
}

// Просто BORDER 0
void border0() __naked {
	__asm;
	xor a
	out ( 0xFE ),a
	ret
	__endasm;
}

int main() {
	// Установки и настройки
	CLI();
	
	// Свой обработчик прерываний
	im2Set();
	im2SetHandler ( im2userHandler );
	
	// Очистка экрана
	border0();
	winSetAtr ( 0, 0, 32, 24, 0x00, 0xFF );
	winClear ( 0,0,32,8 );
	// Вывод картинок
	
	// CSP (цветное вверху экрана)
	logoToScreen ( 3,0 );
	
	// CSP2018 (Эквалайзер внизу экрана)
	spr2018_put();
	
	// Середина экрана
	logos_put();
	
	// Инициализация бегщей строки
	InitShiftText();

	// Разрешаем прерывания
	SEI();

	// Основной цикл
	while ( 1 ) {
		// Проверка - доиграла ли до конца музыка
		// и надо ли переходить к следующей мелодии
		checkMusic();
		
		// Проверка и смена картинки справа от свечи
		logos_check();
	}

	//
	return 0;
}
