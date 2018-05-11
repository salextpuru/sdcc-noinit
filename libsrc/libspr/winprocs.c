#include <psernd.h>
#include "winprocs.h"

static void helperProcs() __naked {
__asm;

;// Загружает со стека координаты, длину и высоту (
loadLHBC:
	ld	l,0(ix) ;// X
	ld	h,1(ix) ;// Y
	ld	b,2(ix) ;// W
	ld	c,3(ix) ;// H
	ret
__endasm;
}

static void winClearEffectSimple() __naked {
__asm;
	ld	(hl), a
	ret
__endasm;	
}

static void winClearEffectRnd() __naked {
__asm;
	push	hl
	call	_rnd16
	pop	hl
	and	(hl)
	ld	(hl), a
	ret
__endasm;	
}


static const void* winClearProc=winClearEffectSimple;
void winClear(uint8_t x, uint8_t y, uint8_t w, uint8_t h ) __naked {
	x;y;w;h;
__asm;
	push	ix
	ld 	ix,#4
	add	ix,sp
	call	loadLHBC
	call	winClearEntry
	pop	ix
	ret
	
winClearEntry:
next_l:
	push	hl		;//p1
	push	bc		;//p2
	;// Вычисление адреса по координатам
	call sprXYtoHL ;// hl = screen adress
	;//
	xor	a
	ld	c,#8		;// 8 линий в строке символов
nextll:
	push	hl		;//p3
	push	bc		;//p4
	;// очистка одной линии в строке символов
nextw:
	;// Вызов процедуры для создания эффекта (HL - адрес экрана)
	ld	de,#winClearRet		;// return adress
	push	de
	ld	de,(_winClearProc)	;// calling adress
	push	de
	ret
winClearRet:
	inc	hl
	djnz	nextw
	;// следующая линия в строке символов
	pop	bc		;//g4
	pop	hl		;//g3
	inc	h
	dec	c
	jr nz,	nextll
	;//
	pop	bc		;//g2
	pop	hl		;//g1
	;//
	inc	h		;// y+=1
	dec	c		;// h-=1
	jr nz,	next_l
	ret
__endasm;
}

void winClearRnd(uint8_t x, uint8_t y, uint8_t w, uint8_t h ) __naked {
	x;y;w;h;
__asm;
	push	ix
	ld 	ix,#4
	add	ix,sp
	;//
	ld	hl,#_winClearEffectRnd
	ld	(_winClearProc),hl
	;//
	ld	b,#0x06
winClearRndLoop:
	push	bc
	;//
	call	loadLHBC
	call	winClearEntry
	;//
	halt
	;//
	pop	bc
	djnz	winClearRndLoop
	
	ld	hl,#_winClearEffectSimple
	ld	(_winClearProc),hl
	call	loadLHBC
	call	winClearEntry
	
	pop	ix
	ret
__endasm;
}

void winSetAtr(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t attr, uint8_t mask ) __naked {
	x;y;w;h;attr;mask;
__asm;
	push	ix
	ld 	ix,#4
	add	ix,sp
	ld	l,0(ix) ;// X
	ld	h,1(ix) ;// Y
	;// Вычисление адреса по координатам (bc используется!)
	call	sprXYtoHLattr
	;//
	ld	b,2(ix) ;// W
	ld	c,3(ix) ;// H
	
	;//
	ld	de,#0x0020	;// для ускорения - ширина экрана
attrh:
	push	bc
	push	hl
attrw:
	push	bc
	ld	a,5(ix) ;// mask
	ld	b,a	;// b=mask
	cpl		;// a=~mask
	and	(hl)	;// a=(hl) & ~mask
	ld	c,a	;// c=(hl) & ~mask
	ld	a,4(ix)	;// attr
	and	b	;// a=attr & mask
	or	c	;// a=(attr & mask) | ((hl) & ~mask)
	ld	(hl),a
	pop	bc
	//
	inc	hl
	djnz	attrw
	pop	hl
	pop	bc
	add	hl,de
	dec	c
	jr nz,	attrh
	;//
	pop	ix
	ret
__endasm;
}
