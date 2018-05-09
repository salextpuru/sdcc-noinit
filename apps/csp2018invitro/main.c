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

enum {boxSize=7};

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


enum {
	wshStatDelay=0,
	wshStatShift=1,
};

static char ShiftText[]="Приветствуем всех на слёте CSP2018!!! "
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

static char* charShiftText=ShiftText;
static uint8_t symShiftCounter=0;
static int8_t ShiftTextDelay=5;
static const winShift winShiftText = {0,22,32,2};
static uint8_t winShiftStatus=wshStatDelay;
static uint16_t winShiftDelayCounter;

static void InitShiftText(){
	winSetAtr(31, 22, 1, 2, 0x00, 0xFF);
}

static void CheckShiftText(){
	if( (--ShiftTextDelay)<=0 ){
		shiftLeftPix(&winShiftText);
		ShiftTextDelay=2;
	}
	else{
		return;
	}
	
	if( (++symShiftCounter) >= 8 ){
		
		if( winShiftStatus == wshStatDelay ){
			winShiftDelayCounter++;
			if(winShiftDelayCounter >= 256 ){
				winShiftStatus = wshStatShift;
				winSetAtr(0, 22, 31, 2, 0104, 0xFF);
			}
		}
		else {
			symShiftCounter=0;
			if(!*charShiftText){
				charShiftText=ShiftText;
				winShiftStatus = wshStatDelay;
				winShiftDelayCounter=0;
			}
			else {
				printScale(31,22,2,*charShiftText);
				charShiftText++;
			}
		}
	}
}

// Defines for music.c
extern void (*music_im2h)();

// AY Dump
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

static const uint8_t colorTable[0x10]={1,1,2,3,4,5,6,7,0101,0101,0102,0103,0104,0105,0106,0107};

// IM2 handler
static void im2userHandler(){
static volatile uint8_t lock;
	// Check music
	if(music_im2h){music_im2h();}
	
	// AY DUMP
	getAYdump();
	
	// Fone proc
	SEI();
	if( !lock ){
		lock=1;
		// Shift Text
		CheckShiftText();
		// Analyze dump of AY
		// Volume
		winSetAtr(boxText[0].x, boxText[0].y, boxText[0].w, boxText[0].h, colorTable[ayRgDump[8]], 0x07 );
		winSetAtr(boxText[1].x, boxText[1].y, boxText[1].w, boxText[1].h, colorTable[ayRgDump[9]], 0x07 );
		winSetAtr(boxText[2].x, boxText[2].y, boxText[2].w, boxText[2].h, colorTable[ayRgDump[10]], 0x07 );
		// Freq
		winSetAtr(boxText[3].x, boxText[3].y, boxText[3].w, boxText[3].h, colorTable[ayRgDump[1]], 0x07 );
		winSetAtr(boxText[4].x, boxText[4].y, boxText[4].w, boxText[4].h, colorTable[ayRgDump[3]], 0x07 );
		winSetAtr(boxText[5].x, boxText[5].y, boxText[5].w, boxText[5].h, colorTable[ayRgDump[5]], 0x07 );
		winSetAtr(boxText[6].x, boxText[6].y, boxText[6].w, boxText[6].h, colorTable[ayRgDump[6]], 0x07 );
		//
		lock=0;
	}
}

void border0() __naked{
__asm;
	xor a
	out (0xFE),a
	ret
__endasm;
}

uint8_t checkMusic();

int main() {
	// Set IM2 handler
	CLI();
	im2Set();
	im2SetHandler( im2userHandler );
	// Clear
	border0();
	winSetAtr(0, 0, 32, 24, 0x00, 0xFF );
	winClear(0,0,32,8);
	// and LOGO
	spr0_out0_attr(&spr2018,0,16);
	logoToScreen(3,0);
	// Text for shift
	InitShiftText();
	//
	SEI();
	// Main loop
	while (1) {
		checkMusic();
	}
	//
	return 0;
}
