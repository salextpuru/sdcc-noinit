/**
	@file ball1.c

	Spite name: ball1*

	W(chars): 3     H(CHARS):2
	PHASES: 4
	Phase's size:  bytes
	Sprite size:   bytes
	Color: 01

*/
#include "ball1.h"


// Phase 0
const Sprite0 ball1_0 = {
	.sz =  54  + sizeof(Sprite0),
	.w = 3,
	.h = 2,
	.datap ={
		0x05,0x80,0x00,0x15,0x88,0x00,0x00,0x00,
		0x00,0x40,0x02,0x00,0x01,0xe0,0x00,0x02,
		0x73,0x00,0x02,0xf0,0x00,0xc2,0xf3,0x00,
		0xc2,0x73,0x00,0x01,0xe0,0x00,0xc0,0x00,
		0x00,0x00,0x00,0x00,0x40,0x02,0x00,0x00,
		0x00,0x00,0x11,0xa8,0x00,0x01,0xa0,0x00,
		01,01,01,01,01,01,}
};

// Phase 1
const Sprite0 ball1_1 = {
	.sz =  54  + sizeof(Sprite0),
	.w = 3,
	.h = 2,
	.datap ={
		0x00,0xa0,0x00,0x02,0x2c,0x00,0x00,0x0c,
		0x00,0x00,0x00,0x00,0x19,0xe0,0x80,0x1a,
		0x70,0x00,0x02,0xf0,0x40,0x32,0xf0,0x00,
		0x02,0x70,0xc0,0x21,0xe0,0x00,0x00,0x01,
		0x80,0x10,0x01,0x80,0x00,0x00,0x00,0x03,
		0x00,0x00,0x03,0x44,0x00,0x00,0x50,0x00,
		01,01,01,01,01,01,}
};

// Phase 2
const Sprite0 ball1_2 = {
	.sz =  54  + sizeof(Sprite0),
	.w = 3,
	.h = 2,
	.datap ={
		0x00,0x29,0x00,0x00,0x02,0x00,0x03,0x00,
		0xc0,0x03,0x00,0xc0,0x08,0x00,0x00,0x04,
		0x00,0x00,0x00,0x78,0x10,0x08,0x9c,0x00,
		0x00,0xbc,0x10,0x08,0xbc,0x00,0x00,0x9c,
		0x20,0x00,0x78,0x10,0x03,0x00,0xc0,0x03,
		0x00,0xc0,0x00,0x40,0x00,0x00,0x94,0x00,
		01,01,01,01,01,01,}
};

// Phase 3
const Sprite0 ball1_3 = {
	.sz =  54  + sizeof(Sprite0),
	.w = 3,
	.h = 2,
	.datap ={
		0x00,0x01,0x40,0x00,0x30,0x00,0x00,0xb0,
		0x30,0x00,0x80,0x00,0x00,0x00,0x18,0x02,
		0x00,0x18,0x00,0x07,0x80,0x02,0x09,0xc0,
		0x00,0x0b,0xc4,0x00,0x0b,0xc0,0x01,0x89,
		0xc4,0x01,0x87,0x80,0x00,0x00,0x10,0x00,
		0xc0,0xd0,0x00,0x00,0xc0,0x00,0x14,0x00,
		01,01,01,01,01,01,}
};

// Sprite phases
const Sprite0* const ball1[4]={&ball1_0,&ball1_1,&ball1_2,&ball1_3,};
