	; Getters-Setters params from/to SP
	; All parametres gets via IY
	; - Entry C-code -
	; call wcplsp_iy_init
	; ....
	; call wcplsp_get_a
	; call wcplsp_get_ix
	; call wcplsp_get_bc
	; call wcplsp_get_de
	; call wcplsp_get_hl
	; .....
	; .....
	; .....
	; pop iy
	; ret
        .module wcpluginsp

	; Start of program
        .area _CODE
        ;
	.globl wcplsp_iy_init
	.globl wcplsp_get_a
	.globl wcplsp_get_ix
	.globl wcplsp_get_bc
	.globl wcplsp_get_de
	.globl wcplsp_get_hl

; Store iy
; IY=adress of first stack parametr
; IX - stored
wcplsp_iy_init:
	pop	bc
	push	iy
	ld	iy,#4
	add	iy,sp
	push	ix
	push	bc
	ret
; get a from stack
wcplsp_get_a:
	ld	a,(iy)
	inc	iy
	ret

; get ix from stack
wcplsp_get_ix:
	exx
	ld	c,(iy)
	inc	iy
	ld	b,(iy)
	inc	iy
	push	bc
	pop	ix
	exx
	ret

; get bc from stack
wcplsp_get_bc:
	ld	c,(iy)
	inc	iy
	ld	b,(iy)
	inc	iy
	ret

; get de from stack
wcplsp_get_de:
	ld	e,(iy)
	inc	iy
	ld	d,(iy)
	inc	iy
	ret

; get hl from stack
wcplsp_get_hl:
	ld	l,(iy)
	inc	iy
	ld	h,(iy)
	inc	iy
	ret
