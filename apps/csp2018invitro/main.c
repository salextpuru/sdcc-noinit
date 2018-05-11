#include <types.h>
#include <string.h>
#include <stdint.h>
#include <spr0.h>
#include <spr0_fade.h>
#include <im2.h>
#include <zxkbd.h>
#include <winprocs.h>
#include <aydump.h>

#include "cspLogo.h"
#include "spr2018.h"
#include "uSctrollText.h"
#include "logos.h"

/**
 * -------------------------------- ���������� ------------------------------------------
 */

/*
 * ���������� ������� � �����������
 */
enum {boxSize=7};

/*
 * ���������� � ������� ������� � �����������
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
void keyMusic(uint16_t k);

/*
 * ������� ������ ��� �����������
 */
static const uint8_t colorTable[0x10]= {1,1,2,3,4,5,6,7,0101,0101,0102,0103,0104,0105,0106,0107};

/*
 * ����� ��������
 */
static uint16_t logos_timer;
static uint8_t logos_counter;

/*
 * ��������� �������� ������� �����
 */
void candle_flame_animate();

/*
 * ���������� ���������� 1/50 ���
 */

static void im2userHandler() {
	// ����������, ����������� ��������� ������ ������� ��������
	static volatile uint8_t lock;
	
	// ������ ��������� ������� ������
	if (music_im2h) {
		music_im2h();
	}

	// �����������
	logos_timer++;

	// �������� ���������� ������ (��� � ����������!)
	if ( lock ) {
		return;
	}
	// ��������� ��������� ���� � ���� ������� ����
	lock=1;
	// ��������� ����������.
	SEI();
	
	// AY DUMP
	ayDumpGet();
	
	// ����� ������
	CheckShiftText();
	// ���������� (������������ ������� �������, ����������� �� ����� AY)
	// Volume
	winSetAtr(boxText[0].x, boxText[0].y, boxText[0].w, boxText[0].h, colorTable[ayDump[8]], 0x07 );
	winSetAtr(boxText[1].x, boxText[1].y, boxText[1].w, boxText[1].h, colorTable[ayDump[9]], 0x07 );
	winSetAtr(boxText[2].x, boxText[2].y, boxText[2].w, boxText[2].h, colorTable[ayDump[10]], 0x07 );
	// Freq
	winSetAtr(boxText[3].x, boxText[3].y, boxText[3].w, boxText[3].h, colorTable[ayDump[1]], 0x07 );
	winSetAtr(boxText[4].x, boxText[4].y, boxText[4].w, boxText[4].h, colorTable[ayDump[3]], 0x07 );
	winSetAtr(boxText[5].x, boxText[5].y, boxText[5].w, boxText[5].h, colorTable[ayDump[5]], 0x07 );
	winSetAtr(boxText[6].x, boxText[6].y, boxText[6].w, boxText[6].h, colorTable[ayDump[6]], 0x07 );
		
	// �������� ������� �����
	candle_flame_animate();
	
	// ��� �������� ����
	logoAniStep();
	
	// ����� ���������� (� ����, �.�. ������ �������� 1-6 �����)
	zxKbdScan();
	// �������� - � ����� ���� ������� �������?
	keyMusic(zxKbdInKey());
	
	// ������������ ���� � ���� ������� ����
	CLI();
	lock=0;
}

// ������ BORDER 0
void border0() __naked {
	__asm;
	xor a
	out (0xFE),a
	ret
	__endasm;
}

int main() {
	// ��������� � ���������
	CLI();
	// ���� ���������� ����������
	im2Set();
	im2SetHandler( im2userHandler );
	// ������� ������
	border0();
	winSetAtr(0, 0, 32, 24, 0x00, 0xFF );
	winClear(0,0,32,8);
	// ����� ��������
	logoToScreen(3,0);
	spr0_out0_attr(&spr2018,0,16);
	spr0_out0_attr(&logos_base,0,8);
	winSetAtr(5, 8, 12, 8, 0x01, 0xFF );
	// ������������� ������ ������
	InitShiftText();
	
	// ��������� ����������
	SEI();

	// �������� ����
	while (1) {
		uint8_t i;
		// �������� - �������� �� �� ����� ������
		// � ���� �� ���������� � ��������� �������
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
