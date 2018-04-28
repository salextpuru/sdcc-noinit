/**
	@file ball2.c

	Spite name: ball2*

	W(chars): 3     H(CHARS):2
	PHASES: 4
	Phase's size:  bytes
	Sprite size:   bytes
	Color: 02

*/
#include "ball2.h"


// Phase 0
const Sprite0 ball2_0 = {
	.sz =  54  + sizeof(Sprite0),
	.w = 3,
	.h = 2,
	.datap ={
		0x00,0x00,0x00,0x00,0x80,0x00,0x01,0xc0,
		0x00,0x03,0xe4,0x00,0x11,0xc0,0x00,0x00,
		0x80,0x00,0x00,0x10,0x00,0x10,0x84,0x00,
		0x39,0xce,0x00,0x10,0x84,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x08,0x08,0x00,0x00,
		0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		02,02,02,02,02,02,}
};

// Phase 1
const Sprite0 ball2_1 = {
	.sz =  54  + sizeof(Sprite0),
	.w = 3,
	.h = 2,
	.datap ={
		0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x20,
		0x00,0x07,0x00,0x00,0x02,0x04,0x00,0x00,
		0x0e,0x00,0x10,0x9f,0x00,0x01,0xce,0x00,
		0x03,0xe4,0x00,0x01,0xc0,0x00,0x10,0x80,
		0x00,0x00,0x04,0x00,0x00,0x20,0x00,0x02,
		0x70,0x00,0x00,0x20,0x00,0x00,0x00,0x00,
		02,02,02,02,02,02,}
};

// Phase 2
const Sprite0 ball2_2 = {
	.sz =  54  + sizeof(Sprite0),
	.w = 3,
	.h = 2,
	.datap ={
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,
		0x00,0x00,0x08,0x00,0x08,0x1c,0x00,0x00,
		0x08,0x00,0x00,0x00,0x00,0x04,0x80,0x00,
		0x21,0xc1,0x00,0x00,0x80,0x00,0x00,0x08,
		0x00,0x08,0x1c,0x00,0x1c,0x3e,0x00,0x08,
		0x1c,0x00,0x00,0x08,0x00,0x00,0x80,0x00,
		02,02,02,02,02,02,}
};

// Phase 3
const Sprite0 ball2_3 = {
	.sz =  54  + sizeof(Sprite0),
	.w = 3,
	.h = 2,
	.datap ={
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x02,0x20,0x00,0x00,0x00,0x00,0x10,
		0x00,0x00,0x38,0x04,0x00,0x10,0x00,0x00,
		0x00,0x80,0x00,0x00,0x04,0x00,0x20,0x0e,
		0x00,0x02,0x04,0x00,0x07,0x00,0x00,0x0f,
		0x80,0x00,0x07,0x10,0x00,0x02,0x00,0x00,
		02,02,02,02,02,02,}
};

// Sprite phases
const Sprite0* const ball2[4]={&ball2_0,&ball2_1,&ball2_2,&ball2_3,};