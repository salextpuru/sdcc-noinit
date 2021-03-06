/* Sprite musbtn[1] */
#include <spr0.h>
#include <winprocs.h>

enum {btnN=6};

static const struct {
	uint8_t x;
	uint8_t y;
}pos[btnN]={
	{5,1},
	{3,3},
	{1,5},
	{28,0},
	{26,2},
	{24,4}
};

const unsigned char musbtn_0[] = {
	0x28, 0x00, 0x02, 0x02, 0x03, 0xc0, 0x0f, 0xf0, 0x1c, 0x38, 0x30, 
	0x0c, 0x60, 0x06, 0x41, 0x82, 0xc3, 0xc2, 0xc7, 0xe3, 0xc7, 0xe3, 
	0xc3, 0xc3, 0x41, 0x82, 0x60, 0x06, 0x30, 0x0c, 0x1e, 0x38, 0x0f, 
	0xf0, 0x01, 0xc0, 0x41, 0x41, 0x41, 0x41
};

void musBtnDraw(uint8_t n){
	uint8_t i;
	for(i=0; i<btnN; i++){
		if( i!= n ){
			spr0_out0_attr((Sprite0*)musbtn_0,pos[i].x,pos[i].y);
		}
	}
	if( n<btnN ){
		spr0_out0((Sprite0*)musbtn_0,pos[n].x,pos[n].y);
		winSetAtr(pos[n].x,pos[n].y, 2, 2, 0104, 0xFF);
	}
}
