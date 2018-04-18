#include <types.h>
#include <stdint.h>
#include <spr0.h>

#include "spr_shadow.h"

#define baseadr _sprd_xbh

enum{
	sprPhases = 4,
	sprites = 34,
	sprH=2,
	sprW=3
};

typedef uint16_t spritebook_spr[sprPhases];
extern const spritebook_spr spritebook[sprites];
extern const uint8_t spritebook_data[];

extern uint8_t sdccnoinit[];

typedef struct{
	int8_t x;
	int8_t y;
	int8_t sx;
	int8_t sy;
	uint8_t color;
	uint8_t phase;
}tSprctl;

tSprctl	sprctl[sprites];

void initData(){
	uint8_t atr;
	uint8_t i;
	tSprctl* pSprCtl;
	
	pSprCtl=sprctl;
	atr=0;
	
	// Fill sprites data
	for( i=0; i<sprites; i++){
		atr++;
		atr = ((atr&0x0F)>=7)?((atr&0x40)?1:0x41):atr;
		// 
		pSprCtl->color = atr;
		pSprCtl->x= (i >= (0x1F-sprW))?i-0x1F:i;
		pSprCtl->y= (i >= (0x17-sprH))?i-0x17:i;
		pSprCtl->sx=(i&1)?i&1:-1;
		pSprCtl->sy=(i&2)?1:-1;
		pSprCtl++;
	}
}

int main(){
	uint8_t i;
	// Init screen
	shsc_set_color(0x41);
	shsc_cls();
	
	initData();
	shsc_putmode();
	
while(1){
	tSprctl* pSprCtl;
	pSprCtl=sprctl;
	
	shsc_spr2scr(sdccnoinit, shsc_adr(0,0), 32, 24);
	shsc_atr2scr(0x01,  shsc_atradr(0,0) , 32, 24);
	
	for( i=0; i<sprites; i++){
		shsc_spr2scr(spritebook_data + spritebook[i][ pSprCtl->phase ],
			     shsc_adr(pSprCtl->x, pSprCtl->y), sprW, sprH);
		shsc_atr2scr( pSprCtl->color,  shsc_atradr(pSprCtl->x, pSprCtl->y) , sprW, sprH);

		pSprCtl->x+=pSprCtl->sx;
		if((pSprCtl->x >= (0x20 - sprW) ) || (pSprCtl->x <=0)) {
			pSprCtl->sx=-pSprCtl->sx;
			if(pSprCtl->x <0){
				pSprCtl->x=0;
			}
		}
		
		pSprCtl->y+=pSprCtl->sy;
		if((pSprCtl->y >= (0x18 - sprH) ) || (pSprCtl->y <=0)) {
			pSprCtl->sy=-pSprCtl->sy;
			if(pSprCtl->y <0){
				pSprCtl->y=0;
			}
		}
		
		
		pSprCtl->phase = (pSprCtl->phase+1)&(sprPhases-1);
		
		pSprCtl++;
	}
	shsc_flip();
	
}
	//
	return 0;
}
