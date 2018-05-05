#include <types.h>
#include <string.h>
#include <stdint.h>
#include <spr0.h>
#include <im2.h>

#include "cspLogo.h"
#include "winprocs.h"
#include "printscale.h"
#include "spr2018.h"

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

static const char* issues[][4]={
	/*
	{"Welcome to","CSP 2018 party","in Novosibirsk","great siberian city!"},
	{"There is drinks!","Posiible will be womens!","Maybe dances!","Eating foods!"},
	{"Of course,","DEMO! ARTS! MUSICS! GAMES!","and","other ZX-Programms!"},
	*/
	{"Приветствуем участников","CSP 2018","в городе","Новосибирске!"},
	{"Есть Бухло!","Возможны Женщины!","Назревают Танцы!","Поглощается Еда!"},
	{"И, конечно","ДЕМО! ДЕМО! ДЕМО!","и ещё раз", "--- ДЕМО ---"},
	{"Сегодня у нас в гостях!","Известные!","Не очень известные!","Вообще не известные!"},
	{"Спектрумисты!","Друзья Спектрумистов!","Подруги Спектрумистов!","Жены Спектрумистов!"},
	//
	{NULL,NULL,NULL,NULL}
};

static uint16_t issuen=0;

static void printNextMsg() {
	uint8_t x;
	uint8_t i;
	uint8_t l;
	
	winSetAtr(0,0,32,8, 0104, 0xFF );
	
	if ( !issues[issuen][0] ) {
		issuen=0;
	}

	for (i=1; i<=2; i++) {
		for(l=0; l<4; l++){
			x=(0x20-strlen(issues[issuen][l]) )>>1;
			printStrScale(x,l+l,i,issues[issuen][l]);
		}
		waitINTS(20);
	}
	
	
	waitINTS(100);
	winSetAtr(0,0,32,8, 04, 0xFF );
	waitINTS(10);
	winSetAtr(0,0,32,8, 0101, 0xFF );
	waitINTS(10);
	winSetAtr(0,0,32,8, 01, 0xFF );
	waitINTS(10);
	winClearRnd(0,0,32,8);

	issuen++;
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
		// Analyze dump of AY
		// Volume
		winSetAtr(boxText[0].x, boxText[0].y, boxText[0].w, boxText[0].h, colorTable[ayRgDump[8]], 0x07 );
		winSetAtr(boxText[1].x, boxText[1].y, boxText[1].w, boxText[1].h, colorTable[ayRgDump[9]], 0x07 );
		winSetAtr(boxText[2].x, boxText[2].y, boxText[2].w, boxText[2].h, colorTable[ayRgDump[10]], 0x07 );
		// Freq
		winSetAtr(boxText[3].x, boxText[3].y, boxText[3].w, boxText[3].h, colorTable[ayRgDump[1]], 0x07 );
		winSetAtr(boxText[4].x, boxText[4].y, boxText[4].w, boxText[4].h, colorTable[ayRgDump[3]], 0x07 );
		winSetAtr(boxText[5].x, boxText[5].y, boxText[5].w, boxText[5].h, colorTable[ayRgDump[5]], 0x07 );
		winSetAtr(boxText[6].x, boxText[6].y, boxText[6].w, boxText[6].h, colorTable[ayRgDump[6]>>1], 0x07 );
		//
		lock=0;
	}
}

uint8_t checkMusic();

int main() {
	static uint8_t nsk_color=1;
	
	CLI();
	logoToScreen(3,9);
	
	im2Set();
	im2SetHandler( im2userHandler );
	
	SEI();
	
	winClear(0,0,32,8);
	
	spr0_out0_attr(&spr2018,0,16);
	
	while (1) {
		printNextMsg();
		if( checkMusic() ) {
			if( (++nsk_color) > 15 ) {nsk_color=1;}
			winSetAtr(0, 22, 32, 2, colorTable[nsk_color], 0x07 );
		}
	}
	//
	return 0;
}
