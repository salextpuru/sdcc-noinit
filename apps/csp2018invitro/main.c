#include <types.h>
#include <string.h>
#include <stdint.h>
#include <spr0.h>
#include <im2.h>

#include "cspLogo.h"
#include "winprocs.h"
#include "printscale.h"
#include "spr2018.h"
#include "winshifts.h"

/**
 * -------------------------------- Бегущая строка ------------------------------------------
 * Код ужасный и писался на раз-два ухнем:)
 */
enum {
	// Состояние ожидания.
	// Окно сдвигается, но новые буквы не выводятся
	wshStatDelay=0,
	// Состояние прокрутки.
	// После прокрутки на 8 пикселей - выводится новая буква
	wshStatShift=1,
};

// Собственно, текст. Любой длины (< 64К )
static char ShiftText[]=
        "Приветствуем всех на слёте CSP2018!!! "
        "Состоится сие действо 28-29 июля 2018 года в городе НОВОСИБИРСКЕ! "
        "Приглашаем всех, кого знаем и не знаем, особенно: "
        "AAA, AER, Alex Clap, aturbidflow, Baxter, BlackCat, BlastOff, Buddy, Burst, "
        "Canifol, Cardinal, Connect-2000, Corvax, Creator, Daniel, Debosh, Diamond, "
        "Djoni, dman, Dr.Bars, Fikus, Gibson, Grachev, Hrumer, John Norton Irr, "
        "Kakos_nonos, Kas29, Kowalski, Lzb, Maddev, Marinovsoft, Maxximum, "
        "Misha Pertsovsky, MMCM, Mr.Nick, MV1971, OLN, OTO-man, Quiet, Raider, "
        "RetroDroid, Sambura, Sayman, scalesmann^mc, shuran33, SlackDen, Sobos, "
        "Tiden, T!m0n, Tzerra, Voxon, wbc, wbr, Whitehalt, Xlat, ZeroXor, Zhizh, ZX_NOVOSIB, Шынни... "
        "И ДРУГИЕ!!! Простите, если кого-то не упомянули. Вас много, а мы одни:) Приезжайте все кто хочет! "
        ;

// Текущий выводимый символ
static char* charShiftText=ShiftText;
// Счетчик сдвигов символа (как досигает 8 - надо выводить следующий)
static uint8_t symShiftCounter=0;
// Задержка сдвига (в 1/50)
static int8_t ShiftTextDelay=5;
// Окно сдвига
static const winShift winShiftText = {0,22,32,2};
// Состояние (ожидание или сдвиг)
static uint8_t winShiftStatus=wshStatDelay;
// Счетчик сдвигов в состоянии ожидания
static uint16_t winShiftDelayCounter;

// Делаем невидимым выводимый символ (черное на черном:)
static void InitShiftText() {
	winSetAtr(31, 22, 1, 2, 0x00, 0xFF);
}

// Сдвиг
static void CheckShiftText() {
	// Уменьшаем счетчик задержки
	if ( (--ShiftTextDelay)<=0 ) {
		// Сдвиг на 1 пиксель
		shiftLeftPix(&winShiftText);
		ShiftTextDelay=2;
	} else {
		// Выход, счетчик задержки не упал до нуля
		return;
	}

	// Увеличиваем счетчик сдвига.
	// Если он равен 8, то надо выводить следующий символ
	if ( (++symShiftCounter) >= 8 ) {
		// Если состояние ожидания, то проверяем,
		// Закончилось ли оно
		if ( winShiftStatus == wshStatDelay ) {
			winShiftDelayCounter++;
			if (winShiftDelayCounter >= 256 ) {
				winShiftStatus = wshStatShift;
				winSetAtr(0, 22, 31, 2, 0104, 0xFF);
			}
		}
		// Состояние прокрутки
		else {
			symShiftCounter=0;
			// Если дошли до конца строки,
			// то переход в состояние ожидания
			if (!*charShiftText) {
				charShiftText=ShiftText;
				winShiftStatus = wshStatDelay;
				winShiftDelayCounter=0;
			}
			// Иначе вывод следующего символа
			else {
				printScale(31,22,2,*charShiftText);
				charShiftText++;
			}
		}
	}
}

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
 * Обработчик прерывания 1/50 сек
 */
static void im2userHandler() {
	// Переменная, блокирующая повторный запуск фоновых процедур
	static volatile uint8_t lock;

	// Играем следующий кусочек музыки
	if (music_im2h) {
		music_im2h();
	}

	// AY DUMP
	getAYdump();

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
	// Инициализация бегщей строки
	InitShiftText();
	// Разрешаем прерывания
	SEI();

	// Основной цикл
	while (1) {
		// Проверка - доиграла ли до конца музыка
		// и надо ли переходить к следующей мелодии
		checkMusic();
	}
	//
	return 0;
}
