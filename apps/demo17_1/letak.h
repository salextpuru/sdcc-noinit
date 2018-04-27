/**
	@file letak.h

	Spite name: letak*

	W(chars): 3     H(CHARS):2
	PHASES: 4
	Phase's size:  bytes
	Sprite size:   bytes
	Color: 02

*/
#ifndef letak_H_DEFINED
#define letak_H_DEFINED
#include <stdint.h>
#include <spr0.h>

extern const Sprite0* const letak[4];	// Sprite phases
extern const Sprite0 letak_0;	// Sprite phase 0
extern const Sprite0 letak_1;	// Sprite phase 1
extern const Sprite0 letak_2;	// Sprite phase 2
extern const Sprite0 letak_3;	// Sprite phase 3

#endif /* letak_H_DEFINED */
