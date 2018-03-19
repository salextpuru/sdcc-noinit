#include "zxscradr.h"

/**
* @brief Get screen address
* 
* Calling from assembler as call _asm_GetPixelAdr
* 
* in:	B = Y pixel position
* 	C = X pixel position
* 
* out:	Returns address in HL
*/
void  asm_GetPixelAdr() __naked {
__asm;
        ld a,b		; calculate y2,y1,y0
        and #0x07	; mask out unwanted bits
        or  #0x40	; set base address of screen
        ld h,a		; store in h
        ld a,b		; calculate y7,y6
        rra		; shift to position
        rra
        rra
        and #0x18	; mask out unwanted bits
        or h		; or with y2,y1,y0
        ld h,a		; store in h
        ld a,b		; calculate y5,y4,y3
        rla		; shift to position
        rla
        and #0xe0	;mask out unwanted bits
        ld l,a		; store in l
        ld a,c		; calculate x4,x3,x2,x1,x0
        rra		; shift into position
        rra
        rra
        and #0x1f	; mask out unwanted bits
        or l		; or with y5,y4,y3
        ld l,a		; store in l
        ret
__endasm;
}

/**
* @brief Вычислить адрес линии ниже текущей
* 
* вход: HL=адрес экранной линии
* выход: HL= адрес экранной линии ниже
*/
void asm_DownHL()__naked {
__asm;
	inc h
	ld a,h
	and #7
	ret nz
	ld a,l
	add a,#20
	ld l,a
	ret c
	ld a,h
	sub #8
	ld h,a
	ret
__endasm;
}

/**
* @brief Вычислить адрес линии выше текущей
* 
* вход: HL=адрес экранной линии
* выход: HL= адрес экранной линии выше
*/
void asm_UpHL()__naked {
__asm;
	ld a,h
	dec h
	and #7
	ret nz
	ld a,l
	sub #32
	ld l,a
	ret c
	ld a,h
	add a,#8
	ld h,a
	ret
__endasm;
}

