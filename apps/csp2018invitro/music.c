#include <types.h>

#include <color.h>

#include <spr0.h>

#include "pt3xplayer.h"
#include "stc_player.h"
#include "im2.h"

void (*music_im2h)();

/* Music (PT2 and PT3) in files
 */
extern unsigned char jungle_pt3[];
extern unsigned char sanixon_pt3[];
extern unsigned char louboutin_pt3[];

/*
 * Structures, which define mode (unlooped) and type (PT2 or PT3)
 */
#define MUSFMT_PTX	0
#define MUSFMT_STC	1
 
typedef struct {
	void *music;
	BYTE mode;
	BYTE format;
}sMusic;

// Quantity of musics
sMusic musics[]={
	{&jungle_pt3, PT3_UNLOOP, MUSFMT_PTX },
	{&louboutin_pt3, PT3_UNLOOP, MUSFMT_PTX },
	{&sanixon_pt3, PT3_UNLOOP, MUSFMT_PTX },
//	{&mus01D_pt2, PT3_PT2 | PT3_UNLOOP, MUSFMT_PTX },
//	{&again_stc,   STC_UNLOOP, MUSFMT_STC },
//	{&love_stc,   STC_UNLOOP, MUSFMT_STC },
};

#define N_MUSICS	(sizeof(musics)/sizeof(sMusic))

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
			music_im2h = pt3Play;
			// mode and init
			pt3SetMode(sm->mode);
			pt3Init(sm->music);
			break;
		}
		case MUSFMT_STC:{
			music_im2h = stcPlay;
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
uint8_t checkMusic(){
	
	// Current music finished ?
	if( checkEndOfMusic(&musics[musicNumber]) || (musicNumber>=N_MUSICS) ){
		musicNumber++;
		if(musicNumber>=N_MUSICS){
			musicNumber=0;
		}
		initNewMusic(&musics[musicNumber]);
		return 1;
	}
	return 0;
}
