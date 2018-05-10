/* Sprite candle_flame[4] */
#include <spr0.h>
static const unsigned char candle_flame_0[] = {
	0x55, 0x00, 0x03, 0x03, 0x00, 0x04, 0x00, 0x00, 0x0c, 0x00, 0x02, 
	0x0c, 0x04, 0x10, 0x2c, 0x00, 0x00, 0x0c, 0x40, 0x00, 0x1e, 0x00, 
	0x02, 0x3f, 0x08, 0x00, 0x3f, 0x00, 0x00, 0xfb, 0x80, 0x00, 0xff, 
	0x84, 0x10, 0xdb, 0xc0, 0x02, 0xf3, 0xc0, 0x00, 0xfb, 0xc0, 0x00, 
	0xf2, 0xc8, 0x00, 0xd3, 0xc0, 0x10, 0xe1, 0xe0, 0x01, 0xe9, 0xe0, 
	0x01, 0xa3, 0xe4, 0x01, 0xc8, 0xe0, 0x31, 0xda, 0xe0, 0x11, 0xca, 
	0xe0, 0x01, 0x6d, 0xe8, 0x09, 0xed, 0xe0, 0x08, 0xff, 0xc8, 0x42, 
	0x42, 0x42, 0x42, 0x72, 0x42, 0x42, 0x72, 0x42
};
static const unsigned char candle_flame_1[] = {
	0x55, 0x00, 0x03, 0x03, 0x00, 0x04, 0x00, 0x00, 0x0c, 0x00, 0x00, 
	0x0c, 0x00, 0x10, 0x0c, 0x20, 0x00, 0x0c, 0x00, 0x02, 0x1e, 0x00, 
	0x20, 0x3f, 0x04, 0x00, 0x3f, 0x00, 0x00, 0xfb, 0x80, 0x00, 0xff, 
	0x80, 0x00, 0xea, 0xd0, 0x08, 0xf3, 0xc0, 0x00, 0xdb, 0xc0, 0x00, 
	0xf2, 0xd0, 0x04, 0xe3, 0xc2, 0x00, 0xe1, 0xe0, 0x01, 0xc9, 0xe0, 
	0x01, 0xe1, 0xe0, 0x01, 0xc8, 0xe0, 0x11, 0xca, 0xe4, 0x01, 0xc8, 
	0xe0, 0x09, 0x6d, 0xe2, 0x01, 0xed, 0xe8, 0x00, 0xff, 0xc0, 0x42, 
	0x42, 0x42, 0x42, 0x72, 0x42, 0x42, 0x72, 0x42
};
static const unsigned char candle_flame_2[] = {
	0x55, 0x00, 0x03, 0x03, 0x00, 0x04, 0x00, 0x00, 0x0d, 0x00, 0x04, 
	0x0c, 0x00, 0x00, 0x8c, 0x40, 0x12, 0x0c, 0x04, 0x00, 0x1e, 0x10, 
	0x00, 0x3f, 0x00, 0x10, 0x3f, 0x00, 0x00, 0xeb, 0x84, 0x00, 0xbf, 
	0x80, 0x00, 0xfb, 0xd8, 0x02, 0xe3, 0xc0, 0x00, 0xbb, 0xc0, 0x00, 
	0xf2, 0xc0, 0x08, 0xb3, 0xc2, 0x00, 0xe1, 0xe0, 0x01, 0xe9, 0xe4, 
	0x01, 0x61, 0xe0, 0x05, 0xc8, 0xe0, 0x01, 0x8a, 0xe0, 0x01, 0xc8, 
	0xe4, 0x09, 0x6d, 0xe0, 0x05, 0xed, 0xe5, 0x00, 0xff, 0xc0, 0x42, 
	0x42, 0x42, 0x42, 0x72, 0x42, 0x42, 0x72, 0x42
};
static const unsigned char candle_flame_3[] = {
	0x55, 0x00, 0x03, 0x03, 0x00, 0x04, 0x00, 0x01, 0x0c, 0x00, 0x00, 
	0x0c, 0x80, 0x04, 0x4c, 0x30, 0x00, 0x0c, 0x00, 0x00, 0x1e, 0x08, 
	0x00, 0x3f, 0x00, 0x04, 0x3f, 0x00, 0x00, 0xfb, 0x84, 0x00, 0xff, 
	0x80, 0x04, 0xdb, 0xc0, 0x00, 0xf3, 0xd0, 0x10, 0xdb, 0xc0, 0x02, 
	0xf2, 0xc2, 0x02, 0xb3, 0xc2, 0x08, 0xa1, 0xe0, 0x01, 0xe1, 0xe0, 
	0x11, 0x65, 0xe4, 0x01, 0x48, 0xe0, 0x21, 0xca, 0xe2, 0x01, 0xc8, 
	0xe0, 0x01, 0x6d, 0xe0, 0x09, 0xed, 0xea, 0x00, 0xff, 0xc0, 0x42, 
	0x42, 0x42, 0x42, 0x72, 0x42, 0x42, 0x72, 0x42
};
static const Sprite0* candle_flame[4]={
	(Sprite0*)candle_flame_0,
	(Sprite0*)candle_flame_1,
	(Sprite0*)candle_flame_2,
	(Sprite0*)candle_flame_3,

};

static uint8_t candle_flame_counter;
static uint8_t candle_flame_delay;

void candle_flame_animate(){
	if( candle_flame_delay--){return;}
	candle_flame_delay=12;
	
	spr0_out0_attr(candle_flame[candle_flame_counter],1,8);
	candle_flame_counter=(candle_flame_counter+1)&3;
}
