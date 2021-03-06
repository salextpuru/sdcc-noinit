#include <spr0.h>
#include <winprocs.h>
#include "psernd.h"
#include "cspLogo.h"

static const unsigned char logoCSP[] = {
	0x2b, 0x06, 0x19, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
	0xff, 0x00, 0xff, 0xff, 0xfd, 0x50, 0x00, 0x00, 0x05, 0xef, 0x00,
	0x00, 0xff, 0xa8, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xfc, 0xff, 0x00, 0xff, 0xff, 0xdb, 0x80, 0x00, 0x00,
	0x02, 0xb7, 0x00, 0x00, 0xef, 0x54, 0x00, 0x00, 0x00, 0x01, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xff, 0x00, 0xff, 0xff, 0xf5,
	0x00, 0x00, 0x00, 0x27, 0x7f, 0x00, 0x00, 0xfc, 0x84, 0x00, 0x00,
	0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0x00,
	0xff, 0xff, 0x6a, 0x00, 0x00, 0x00, 0x4a, 0xff, 0x00, 0x00, 0xe9,
	0x20, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xe0, 0xff, 0x00, 0xff, 0xf7, 0xf4, 0x00, 0x00, 0x00, 0x11, 0xff,
	0x00, 0x00, 0xc8, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xc0, 0xff, 0x00, 0xff, 0xef, 0xe8, 0x00, 0x00,
	0x00, 0x2b, 0xff, 0x00, 0x00, 0xd5, 0x04, 0x00, 0x00, 0x00, 0x1f,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0xff, 0x00, 0xff, 0xff,
	0x41, 0x00, 0x00, 0x00, 0x56, 0xff, 0x00, 0x00, 0xae, 0x00, 0x00,
	0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff,
	0x00, 0xff, 0xaa, 0xa6, 0x00, 0x00, 0x00, 0xab, 0xff, 0x00, 0x00,
	0x54, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xfe, 0xff, 0xff, 0x50, 0xff, 0x17, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xc1, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0x7a, 0xfe, 0xbc, 0x2b, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xe8, 0x6a, 0x00, 0x00, 0x01,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xff, 0xff, 0x5a, 0xff,
	0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd,
	0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff,
	0xff, 0x58, 0xff, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xe0, 0xff, 0xff, 0xdc, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x0f, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0x7a, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
	0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0xff, 0xff, 0xfa,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
	0xff, 0xff, 0x7a, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfd, 0x48, 0x5f,
	0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xfe, 0xff, 0xff, 0xff, 0x7a, 0xfd, 0xff, 0x00, 0x00, 0x05,
	0xbf, 0x01, 0xc0, 0xff, 0x9b, 0x00, 0xff, 0x00, 0x00, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0x7b, 0xea, 0xff,
	0x00, 0x00, 0x03, 0x6f, 0x00, 0xa0, 0xfd, 0x36, 0x00, 0xff, 0x00,
	0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xff,
	0x7f, 0xd7, 0xff, 0x00, 0x00, 0x16, 0xff, 0x00, 0xc0, 0xf6, 0x64,
	0x00, 0xff, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0x7f, 0xea, 0xff, 0x00, 0x00, 0x29, 0xff, 0x00,
	0x80, 0xf9, 0xd8, 0x00, 0xff, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0x7f, 0xe4, 0xff, 0x00, 0x00,
	0x13, 0xbf, 0x00, 0x80, 0xf3, 0xe0, 0x00, 0xff, 0x00, 0x0f, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0x98,
	0xff, 0x00, 0x00, 0x0c, 0xff, 0x00, 0x00, 0xff, 0x4a, 0x00, 0xff,
	0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0xff, 0xff,
	0xff, 0xff, 0x30, 0xff, 0x00, 0x00, 0x5b, 0xff, 0x00, 0x80, 0xea,
	0x90, 0x00, 0xff, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0x00, 0xff, 0xff, 0xff, 0xff, 0x20, 0xff, 0x00, 0x00, 0xb7, 0xff,
	0x00, 0x00, 0xdd, 0x40, 0x00, 0xff, 0x00, 0x7f, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0x40, 0xff, 0xff,
	0xff, 0xff, 0xff, 0x00, 0x5f, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff,
	0x00, 0xff, 0xff, 0x85, 0x61, 0xdf, 0x00, 0x25, 0xff, 0xff, 0xff,
	0xff, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xff, 0xff,
	0xff, 0xff, 0xfe, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x5f,
	0xff, 0xff, 0xff, 0xfe, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff,
	0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x07, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff,
	0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff,
	0xef, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff,
	0xff, 0xfe, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0xff,
	0xff, 0xff, 0xfc, 0xfe, 0x00, 0xff, 0xff, 0xff, 0x8f, 0x7f, 0x00,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff,
	0xf8, 0x1f, 0x00, 0xff, 0xff, 0xff, 0xff, 0xb1, 0x7f, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfd, 0x54, 0x00,
	0xd0, 0x00, 0xbb, 0x00, 0xdf, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xfd, 0xff, 0xff,
	0xf6, 0x88, 0x00, 0xa0, 0x11, 0x5f, 0x00, 0xdf, 0xff, 0xff, 0x00,
	0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xff,
	0xfd, 0xff, 0xff, 0xfd, 0x20, 0x00, 0xc0, 0x2a, 0xbf, 0x00, 0xdf,
	0xff, 0xff, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xf0, 0xff, 0xfd, 0xff, 0xff, 0xe9, 0x00, 0x00, 0x40, 0x43,
	0x7f, 0x00, 0xff, 0xfe, 0xff, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xfe, 0xd2, 0x00,
	0x00, 0x40, 0x25, 0xff, 0x00, 0xff, 0xfb, 0xff, 0x00, 0x00, 0x00,
	0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff,
	0xff, 0x80, 0x00, 0x00, 0x00, 0x4f, 0xff, 0x00, 0xdf, 0x96, 0xff,
	0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80,
	0xff, 0xfd, 0xff, 0xf5, 0x48, 0x00, 0x00, 0x40, 0x15, 0xff, 0x00,
	0xff, 0xb5, 0xff, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0x00, 0xff, 0xfd, 0xff, 0xfe, 0x80, 0x00, 0x00, 0x00,
	0x2b, 0xff, 0x00, 0xff, 0x6b, 0xff, 0x00, 0x00, 0x00, 0x7f, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xfa, 0x00, 0x00,
	0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xf0, 0xc6, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xee,
	0xfe, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8,
	0xff, 0xff, 0xff, 0x8e, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xdc, 0xfe, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xb0, 0xee, 0x00, 0x00, 0x07, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x10, 0xfe, 0x00,
	0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd,
	0x68, 0x6c, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xfe, 0x58, 0xac, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xfe, 0x84, 0x10, 0xa8, 0x00, 0x00, 0x7f,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x75,
	0x48, 0x10, 0x03, 0x01, 0x6d, 0x00, 0x00, 0xff, 0xa1, 0x00, 0x80,
	0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff,
	0xff, 0xff, 0xf2, 0x20, 0x00, 0x05, 0x0b, 0x3b, 0x00, 0x00, 0xff,
	0x38, 0x08, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xf8, 0xff, 0xff, 0xff, 0xff, 0xa5, 0x00, 0x00, 0x03, 0x15, 0xdf,
	0x00, 0x00, 0xf2, 0x54, 0x80, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x48, 0x00, 0x00,
	0x01, 0x02, 0xff, 0x00, 0x00, 0xe4, 0xa9, 0x20, 0x00, 0x00, 0x07,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff,
	0xd2, 0x00, 0x00, 0x01, 0x57, 0xff, 0x00, 0x00, 0xdb, 0x5a, 0x00,
	0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff,
	0xff, 0xff, 0xfe, 0xa8, 0x00, 0x00, 0x00, 0x29, 0xff, 0x00, 0x00,
	0xf2, 0x62, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0x80, 0xff, 0xff, 0xff, 0xf7, 0x4c, 0x00, 0x00, 0x01, 0x53,
	0xff, 0x00, 0x00, 0xc4, 0x46, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xf9, 0xd8, 0x00,
	0x00, 0x00, 0xaf, 0xff, 0x00, 0x00, 0x98, 0x00, 0x00, 0x00, 0x00,
	0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x38, 0x38, 0x38, 0x38,
	0x38, 0x38, 0x50, 0x7a, 0x50, 0x7a, 0x72, 0x72, 0x72, 0x70, 0x70,
	0x74, 0x74, 0x60, 0x60, 0x6c, 0x6c, 0x68, 0x68, 0x68, 0x68, 0x38,
	0x38, 0x38, 0x38, 0x38, 0x50, 0x7a, 0x7a, 0x50, 0x72, 0x50, 0x70,
	0x70, 0x70, 0x70, 0x60, 0x60, 0x60, 0x60, 0x68, 0x68, 0x68, 0x68,
	0x68, 0x38, 0x38, 0x38, 0x38, 0x38, 0x50, 0x7a, 0x7a, 0x7a, 0x50,
	0x72, 0x38, 0x70, 0x70, 0x74, 0x74, 0x60, 0x60, 0x6c, 0x6c, 0x68,
	0x68, 0x68, 0x68, 0x38, 0x38, 0x38, 0x38, 0x38, 0x50, 0x38, 0x38,
	0x38, 0x50, 0x70, 0x72, 0x78, 0x38, 0x70, 0x60, 0x60, 0x60, 0x60,
	0x38, 0x38, 0x68, 0x68, 0x68, 0x38, 0x38, 0x38, 0x38, 0x38, 0x50,
	0x7a, 0x50, 0x7a, 0x72, 0x72, 0x72, 0x70, 0x70, 0x74, 0x74, 0x60,
	0x60, 0x6c, 0x68, 0x68, 0x68, 0x68, 0x68, 0x38, 0x38, 0x38, 0x38,
	0x38, 0x50, 0x7a, 0x7a, 0x50, 0x50, 0x70, 0x70, 0x70, 0x38, 0x38,
	0x38, 0x38, 0x60, 0x60, 0x6c, 0x68, 0x68, 0x68, 0x68, 0x38, 0x38,
	0x38, 0x38, 0x38, 0x50, 0x7a, 0x7a, 0x7a, 0x72, 0x72, 0x72, 0x70,
	0x70, 0x74, 0x74, 0x60, 0x60, 0x6c, 0x6c, 0x6c, 0x68, 0x68, 0x68,
	0x38, 0x38, 0x38, 0x38, 0x38, 0x38
};

void logoToScreen ( uint8_t x, uint8_t y ) {
	spr0_out0_attr ( ( Sprite0* ) logoCSP, x,y );
	winSetAtr ( x, y, (( Sprite0* ) logoCSP)->w, (( Sprite0* ) logoCSP)->h, 0 , 0100 );
}
static uint8_t 	pos=3;
static uint8_t	enable=1;
static uint8_t  delay;

void logoAniStep() {
	uint8_t i;

	if ( !enable ) {
		if ( delay-- ) {
			return;
		}

		enable=1;
	}

	if ( pos!=3 ) for ( i=0; i<7; i++ ) {
			winSetAtr ( pos+i, 6-i, 1, 1, 0000, 0100 );
		}

	pos++;

	if ( pos!=21 ) for ( i=0; i<7; i++ ) {
			winSetAtr ( pos+i, 6-i, 1, 1, 0100, 0100 );
		}

	if ( pos >=21 ) {
		pos=3;
		enable=0;
		delay= rnd16() & 0xFF ;
	}
}
