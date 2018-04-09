#include <types.h>
#include <stdint.h>
#include <conio.h>
#include <spr0.h>

#include "spr_shadow.h"

#define baseadr _sprd_xbh

typedef uint16_t spritebook_spr[4];
extern const spritebook_spr spritebook[34];
extern const uint8_t spritebook_data[];

uint8_t* scradr;
uint8_t* spradr;

int main(){
	uint8_t i;
	uint8_t ph;
	uint8_t x;
	uint8_t y;
	uint8_t step;
	
	ph=0;
	step=0;
	
	
	// Init screen
	shsc_cls();
while(1){
	
	x=0;
	y=0;
	
	for( i=0; i<34; i++){
		spradr = spritebook_data + spritebook[i][ph];
		scradr=shsc_adr(x, y);
		
		__asm;
		push hl
		push de
		push bc
		
		ld hl,(_spradr)
		ld de,(_scradr)
		ld bc,#0x0203
		call _shsc_spr2scr_asm
		
		pop bc
		pop de
		pop hl
		__endasm;
		
		x+=4;
		if( x>=32 ){
			x=0;
			y+=3;
		}
	}
	shsc_flip();
	
	if( step == 0 ){
		if( ph>=3){
			step=1;
		}else{
			ph+=1;
		}
	}
	else {
		if( ph<1){
			step=0;
		}else{
			ph-=1;
		}
	}
	
}
	//
	return 0;
}
