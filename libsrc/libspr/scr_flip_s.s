;-------------------------------------------------
; Стандартный экран 256x192, знакоместа,
; атрибуты посимвольно
;-------------------------------------------------
	.globl _spr0_scr_adr

        .module scr_flip_s
	.area	_CODE
;-------------------------------------------------
; Перенос экрана из теневого (_spr0_scr_adr) в 0x4000
.globl _scr0_flip4000
_scr0_flip4000:
	ld	hl,(_spr0_scr_adr)
	ld	de,#0x4000
	ld	bc,#0x1B00
	ldir
ret
;-------------------------------------------------
; Перенос экрана из теневого (_spr0_scr_adr) в 0xC000
.globl _scr0_flipC000
_scr0_flipC000:
	ld	hl,(_spr0_scr_adr)
	ld	de,#0xC000
	ld	bc,#0x1B00
	ldir
ret
;-------------------------------------------------
; Очищает теневой экран (только пикселы)
.globl _scr0_clr_pix
_scr0_clr_pix:
	xor	a
; Заполняеи теневой экран содержимым A (только пикселы)
scr0_fill_pix_asm:	
	ld	hl,(_spr0_scr_adr)
	push	hl
	pop	de
	inc	de
	ld	(hl),a
	ld	bc,#0x17FF
	ldir
ret
;-------------------------------------------------
; Заполняеи теневой экран содержимым A (только пикселы)
.globl _scr0_fill_pix
_scr0_fill_pix:
	ld	hl,#0x0002
	add	hl,sp
	ld	a,(hl)
	call	scr0_fill_pix_asm
ret
;-------------------------------------------------
; Очищает теневой экран (только атрибуты)
.globl _scr0_clr_atr
_scr0_clr_atr:
	xor	a
; Заполняеи теневой экран содержимым A (только пикселы)
scr0_fill_atr_asm:	
	ld	hl,(_spr0_scr_adr)
	;
	ex	af,af'	;'
	ld	a,#0x18
	add	a,h
	ld	h,a
	ex	af,af'	;'
	; hl = hl + 0x1800
	push	hl
	pop	de
	inc	de
	ld	(hl),a
	ld	bc,#0x02FF
	ldir
ret
;-------------------------------------------------
; Заполняеи теневой экран содержимым A (только пикселы)
.globl _scr0_fill_atr
_scr0_fill_atr:
	ld	hl,#0x0002
	add	hl,sp
	ld	a,(hl)
	call	scr0_fill_atr_asm
ret
;-------------------------------------------------
