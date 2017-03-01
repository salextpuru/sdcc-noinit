#include <types.h>

#include <conio.h>
#include <color.h>

#include <spr0.h>

#include "pt3xplayer.h"
#include "stc_player.h"
#include "im2.h"

/**
 * Sprites in files:
 *	yellow_b2.c
 *	red_b2.c
 *	green_b1.c
 */
extern Sprite0 spr_green_b1;
extern Sprite0 spr_yellow_b2;
extern Sprite0 spr_red_b2;

// Quantity of sprites
#define N_SPRITES	6

/*
 * Structures, which define coordinates and step-X and step-Y
 */
struct {
	BYTE x;	// X-coord
	BYTE y; // Y-coord
	BYTE sx;// step X
	BYTE sy;// step Y
	Sprite0* spr;
}spr[N_SPRITES]={
	{2, 2, 1, 1, &spr_green_b1},
	{10, 10, 1, 2, &spr_red_b2},
	{18, 18, 1, 2, &spr_yellow_b2},
	
	{2, 2, -1, 2, &spr_green_b1},
	{14, 12, 2, -1, &spr_red_b2},
	{15, 17, 1, -1, &spr_yellow_b2},
};

/* Music (PT2 and PT3) in files
 *	kiss_pt3.c
 *	mus010_pt3.c
 *	mus01D_pt2.c
 */
extern unsigned char kiss_pt3[];
extern unsigned char mus010_pt3[];
extern unsigned char mus01D_pt2[];

extern unsigned char again_stc[];
extern unsigned char love_stc[];



/*
 * Structures, which define mode (unlooped) and type (PT2 or PT3)
 */
#define MUSFMT_PTX	0
#define MUSFMT_STC	1
 
typedef struct {
	char *name;
	void *music;
	BYTE mode;
	BYTE format;
}sMusic;

// Quantity of musics
#define N_MUSICS	5

sMusic musics[N_MUSICS]={
	{"1: AGAIN STC ",&again_stc,   STC_UNLOOP, MUSFMT_STC },
	{"2: LOVE STC",&love_stc,   STC_UNLOOP, MUSFMT_STC },

	{"3: MUS01D PT2",&mus01D_pt2, PT3_PT2 | PT3_UNLOOP, MUSFMT_PTX },
	{"4: MUS010 PT3",&mus010_pt3, PT3_UNLOOP, MUSFMT_PTX },
	{"5: KISS PT3",&kiss_pt3,   PT3_UNLOOP, MUSFMT_PTX }
};

/*
 * delay, quant=20ms
 */
void delay(BYTE n){
	BYTE t;
	for(t=0; t<n; t++){
		__asm;
			halt;
		__endasm;
	}
}

/*
 * Draw all sprites
 */
void draw(){
	BYTE i;
	for(i=0; i<N_SPRITES; i++){
		spr0_out0_attr(spr[i].spr, spr[i].x, spr[i].y);
	}
}

/*
 * Move all sprites
 */
void step(){
	BYTE i;
	
	for(i=0; i<N_SPRITES; i++){
		spr0_out0_attr(spr[i].spr, spr[i].x, spr[i].y);
		
		spr[i].x += spr[i].sx;
		spr[i].y += spr[i].sy;
		
		if( (spr[i].x + (spr[i].spr->w)) >= 31){
			spr[i].sx = -spr[i].sx;
		}
		
		if( (spr[i].y + (spr[i].spr->h)) >= 23){
			spr[i].sy = -spr[i].sy;
		}
		
		if(spr[i].x <= 0){
			spr[i].sx = -spr[i].sx;
		}
		
		if(spr[i].y <=0 ){
			spr[i].sy = -spr[i].sy;
		}
		
		spr0_out0_attr(spr[i].spr, spr[i].x, spr[i].y);
	}
	
}


BYTE checkEndOfMusic(sMusic* sm){
	BYTE r=0;
	switch( sm->format ){
		case MUSFMT_PTX:{
			r = (pt3GetMode() & PT3_LOOP_FLAG)!=0;
			break;
		}
		case MUSFMT_STC:{
			r = (stcGetMode() & STC_LOOP_FLAG)!=0;
			break;
		}
		default:
			r = 1;
	}
	return(r);
}


void initNewMusic(sMusic* sm){
	CLI();
	switch( sm->format ){
		case MUSFMT_PTX:{
			// irq
			im2SetHandler( (void*)pt3Play );
			im2Set();
			// mode and init
			pt3SetMode(sm->mode);
			pt3Init(sm->music);
			break;
		}
		case MUSFMT_STC:{
			im2SetHandler( (void*)stcPlay );
			im2Set();
			stcSetMode(sm->mode);
			stcInit(sm->music);
			break;
		}
		default:;
	}
	SEI();
}

/*
 * Check for end of current music
 * and begin play next music
 */
char musicNumber=N_MUSICS;
void checkMusic(){
	
	// Current music finished ?
	if( checkEndOfMusic(&musics[musicNumber]) || (musicNumber>=N_MUSICS) ){
		musicNumber++;
		if(musicNumber>=N_MUSICS){
			musicNumber=0;
		}
		initNewMusic(&musics[musicNumber]);
	}
}

// Начало
void main(){
	// Init screen
	ccls(7);
	// Sprites output in XOR mode
	spr0_out0_setopt_xor();
	// Draw all sprites
	draw();
	// Loop
	while(1){
		// Sprites
		step();
		// Music
		checkMusic();
		//
		conio_at(0,0);
		print(musics[musicNumber].name);
		// Speed of screen output
		delay(2);
	}
}
