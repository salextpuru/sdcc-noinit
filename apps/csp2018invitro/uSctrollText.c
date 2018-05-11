#include <winprocs.h>
#include <winshifts.h>
#include "printscale.h"

#include "uSctrollText.h"

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
void InitShiftText() {
	winSetAtr(31, 22, 1, 2, 0x00, 0xFF);
}

// Сдвиг
void CheckShiftText() {
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
