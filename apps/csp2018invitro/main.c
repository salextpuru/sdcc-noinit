#include <types.h>
#include <string.h>
#include <stdint.h>
#include <conio.h>
#include <spr0.h>
#include <im2.h>

static uint16_t rndnext=0x6AE7;

static void fadeRND3() __naked {
	__asm
	;// HL=adr of 1/3 screen
	ld	hl,#0x4000

	ld 	bc,#0x0800 ;// 2K (1/3 scr)

	push	hl
	fadeRND3L1:
	call	rndnext_g

	ld 	a,(_rndnext)
	and	(hl)
	ld 	(hl),a

	inc	hl
	dec 	bc
	ld	a,c
	or	b
	jr	nz,fadeRND3L1
	pop	hl

	ret

	rndnext_g:
	push	hl
	ld	hl,(_rndnext)
	ld 	a,#0x5A
	add	a,l
	ld 	l,a
	ld 	a,#0xA5
	adc 	a,h
	ld	h,a
	adc 	a,l
	ld 	l,a
	ld 	(_rndnext),hl
	pop	hl
	ret
	__endasm;
}

static void clear13() __naked {
	__asm
	;// HL=adr of 1/3 screen
	ld	hl,#0x4000
	;//
	ld 	bc,#0x07FF ;// 2K (1/3 scr)
	push	hl
	pop	de
	push	hl
	inc	de
	ld	(hl),#0
	ldir
	pop	hl
	ld 	c,h
	ld	a,h
	and	#0xF8
	add	a,#0x18
	ld	h,a
	ld	a,c
	and	#0x18
	rr	a
	rr	a
	rr	a
	add	a,h
	ld 	h,a
	ld 	bc,#0x00FF
	push	hl
	pop	de
	inc	de
	ld	(hl),#0
	ldir
	ret
	__endasm;
}

static const char* allText[]= {
	"÷ÎÉÍÁÎÉÅ! ÷îéíáîéå! ÷ÎÉÍÁÎÉÅ!",
	"28-29 éàìñ 2018 çïäá",
	"óïóôïéôóñ - CSP 2018 -",
	"÷ ÇÏÒÏÄÅ îï÷ïóéâéòóëå!",
	"âõèìï É öåîýéîù!",
	"ó÷ïé!",
	"äåíï ÏÔ õþáóôîéëï÷!",
	NULL
};

static const char** tPtr=allText;

static void printNextMsg() {
	uint8_t l;
	if ( !*tPtr ) {
		tPtr=allText;
	}

	l=strlen(*tPtr);
	conio_at((0x20-l)>>1,4);
	print(*tPtr);
	tPtr++;
}

static void clearTextArea() {
	uint8_t i;
	for (i=0; i<12; i++) {
		fadeRND3();
		HALT();
	}
	clear13();
}

void checkMusic();

int main() {
	logoToScreen();
	SEI();
	//
	color(0104);
	clear13();

	while (1) {
		printNextMsg();
		checkMusic();
		waitINTS(50);
		clearTextArea();
	}
	//
	return 0;
}
