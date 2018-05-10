#include "psernd.h"
#include "spr0_fade.h"

void	spr0_fade_step(const Sprite0* adr, uint8_t x, uint8_t y) __naked{
	adr;x;y;
__asm;
	push	ix
	ld	ix,#4
	add	ix,sp
	;// adr
	ld	e,0(ix)
	ld	d,1(ix)
	;// x
	ld	l,2(ix)
	;// y
	ld	h,3(ix)
	push	de
	pop	ix
	;// Определяем адрес в экранной области
	call	sprXYtoHL

	;// DE - данные спрайта
	push	ix
	ld	de,#4
	add	ix,de
	push	ix
	pop	de
	pop	ix
	
	;// Ширина спрайта
	ld	c,2(ix)
	;// Высота спрайта
	ld	a,3(ix)
	add	a
	add	a
	add	a
	ld	b,a ; h*8 (в строках)
spr0_fade_step_hline:	;// Начало цикла по строкам
	push	bc
	;// выводим w байт (одну линию)
	push	hl
spr0_fade_step_line:
	;//
	//ld	a,(de)
	//ld	(hl),a
	;// Получаем случайное число в HL
	push	hl
	push	de
	push	bc
	exx
	call	_rnd16
	ld	a,l
	pop	bc
	pop	de
	pop	hl
	;// a= rnd, register shadows
	ld	b,a ;// b=mask
	cpl
	ld	c,a ;// c=~mask
	;//
	ld	a,(de) 
	and	b
	ld	b,a 
	;//
	ld	a,(hl)
	and	c   
	;//
	or	b   
	;//
	ld	(hl),a 
	
	;// unsahdow register
	exx
	;//
	inc	hl
	inc	de
	dec	c
	jr nz,	spr0_fade_step_line
	pop	hl
	;// Следующая строка на одну ниже
	call	scr_down_hl
	;// Вывод в ту же треть экрана
	pop	bc
	djnz	spr0_fade_step_hline	; Конец цикла по строкам (та же треть)
	;// Выход, если всё
	;//
	pop	ix
	ret
__endasm;
}
