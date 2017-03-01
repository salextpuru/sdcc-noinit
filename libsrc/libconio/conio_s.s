	.include "zxsysvar_const.hS"
	.include "conio_const.hS"

.globl _screen_adr
; Координаты курсора
.globl _cur_x
.globl _cur_y
.globl _font

;.globl __putc_ctl_buf;
;.globl __putc_ctl_count;
;.globl __putc_ctl_code;

        .module conio_s
	.area	_CODE


;-------------------------------------------------
; Вывод одного символа
; DE - координаты (Dy Ex), A - код символа
;-------------------------------------------------
out_char:
	; HL - symbol in font adr
	LD L,A
        LD H,#0
        ADD HL,HL
        ADD HL,HL
        ADD HL,HL
        LD BC,(_font)
        ADD HL,BC
        ; DE - screen adress
        LD A,D
        AND #7
        RRCA
        RRCA
        RRCA
        OR E
        LD E,A
        LD A,D
        AND #24
        LD D,A
        ld A,(_screen_adr+1)
        OR D
        LD D,A
        ; Запоминаем для атрибутов
        PUSH DE
        ; Копируем символ
        LD B,#8
out_char_1:
	LD A,(DE)

out_char_mode: LD A,(HL)	; // XOR (HL) AND (HL) OR (HL)

        LD (DE),A
        INC HL
        INC D
        djnz out_char_1
        ; Вспоминаем
        POP DE
        ;in: DE - screen adress
	;out:DE - attr adress
        LD A,D
        RRCA
        RRCA
        RRCA
        AND #3
        OR #0x58
        LD D,A
        ; Копируем атрибут
        LD A,(ATTR_T)
        LD (DE),A
        ;
        RET        ;возвращаемся...


;-------------------------------------------------
; Консольный вывод
;-------------------------------------------------
	; symbol in stack
_putchar::
_putchar_rr_s::
	ld      hl,#2
        add     hl,sp
	ld	a,(hl)
	jr	_putchar_a

_putchar_rr_dbs::
        ld      a,e
        ; output symbol in A-register

_putchar_a::
	push hl
	; Координаты
	ld de,(_cur_x)
	; тут можно отследить служебные
	; ----------------------------
	; \n	SYM_NL
	cp #SYM_NL
	jr z,out_str_nl
	; ----------------------------
	; \r	SYM_CR
	cp #SYM_CR
	jr z,out_str_r
	; ----------------------------
	; TAB	SYM_TAB
	cp #SYM_TAB
	jr nz, out_str_no_tab
	; Табуляция - 8 позиций
	ld a,#(1<<K_TAB)
	add e
	and #(255- 2^K_TAB + 1)
	ld e,a
	jr out_str_modify_x
out_str_no_tab:
	
	; ----------------------------
	; INK
;	cp #0x10
;	jr nz, out_str_no_ink
;	pop hl
;	inc hl
;	ld a,(ATTR_T)
;	and #(255-7)
;	ld e,a
;	ld a,(hl)
;	and #7
;	or a,e
;	ld (ATTR_T),a
;	inc hl
;	jr out_str_na
;out_str_no_ink:

	; ----------------------------
	; PAPER
;	cp #0x11
;	jr nz, out_str_no_paper
;	pop hl
;	inc hl
;	ld a,(ATTR_T)
;	and #(255-56)
;	ld e,a
;	ld a,(hl)
;	rlca
;	rlca
;	rlca
;	and #56
;	or a,e
;	ld (ATTR_T),a
;	inc hl
;	jr out_str_na
;out_str_no_paper:

	; ----------------------------
	; просто вывод печатного симвла
	; вывод
	push de
	call	out_char
	pop de
	; Пересчёт координат
	; X
	inc e
	; тут проверяется выход за границы строки
out_str_modify_x:
	ld a,#(SCR_TXT_W-1)
	cp e
	jr nc,out_str_cont
	; Новая строка
out_str_nl:
	; Y
	inc d
out_str_r:
	ld e,#0
	; тут проверяется выход за границы экрана
	ld a,#(SCR_TXT_H-1)
	cp d
	jr nc,out_str_cont
	dec d
	; скролл экрана
	push	de
	call scroll_up
	pop	de
	;
out_str_cont:
	; сохраняем соординаты
	ld (_cur_x),de
	pop hl
;	inc hl
;	jr out_str_na
	ret

;-------------------------------------------------
;	Очистка экрана
;-------------------------------------------------
; С установкой цвета
.globl _ccls
_ccls:
	ld	hl,#2
	add	hl,sp
	ld	a,(hl)
	ld	(ATTR_P),a
; Текущим цветом
.globl _cls
_cls:
	; clear
	ld hl,(_screen_adr)
	ld de,(_screen_adr)
	inc de
	ld bc,#0x17FF
	ld (hl),#0
	ldir
	; attr
	inc hl
	inc de
	ld a,(ATTR_P)
	ld (ATTR_T),a
	
	; clear
	ld (hl),a
	ld bc,#0x2FF
	ldir
	
	; border
	ld (BORDCR),a
	rrca
	rrca
	rrca
	out (0xFE),a
	;x=0, y=0
	xor a
	ld (_cur_x),a
	ld (_cur_y),a
	;
	ret
;-------------------------------------------------
; Установить постоянные цвета
;-------------------------------------------------
.globl _color
_color:
	ld	hl,#2
	add	hl,sp
	ld	a,(hl)
	ld	(ATTR_P),a
	ld	(ATTR_T),a
	ret
;-------------------------------------------------
; Прокрутка экрана вверх
;-------------------------------------------------
scroll_up:
;	1 st
	LD DE,(_screen_adr)
	LD HL,#0x0020
	ADD HL,DE
	LD BC,#0x07E0
	LDIR
	LD B,#0x08
	LD A,	D
	AND	#0xF8
	LD	D,A	; DE = $40E0 
	PUSH	HL	; HL = $4800 store
L3:
	PUSH BC
	PUSH HL
	PUSH DE
	LD BC,	#0x0020
	LDIR
	POP DE
	POP HL
	POP BC
	INC D
	INC H
	DJNZ L3
;	2 st
	POP DE	; store HL = $4800 restore DE
	LD HL,	#0x0020
	ADD HL,DE
	;
	LD BC,	#0x07E0
	LDIR
	LD B,	#0x08
	LD A,	D
	AND	#0xF8
	LD	D,A	; DE = $40E0 
	;
	PUSH	HL	; HL = $5000 store
	
L4:
	PUSH BC
	PUSH HL
	PUSH DE
	LD BC,	#0x0020
	LDIR
	POP DE
	POP HL
	POP BC
	INC D
	INC H
	DJNZ L4
;	3 st
	POP DE	; store HL = #0x5000 restore DE
	LD HL,	#0x0020
	ADD HL,DE
	;
	LD BC,	#0x07E0
	LDIR
	LD B,	#0x08
; Очистка нижней строки
	or a
	LD DE,#0x0720
	SBC HL,DE
L5:
	PUSH BC
	PUSH HL
	LD B,	#0x20
L6:
	LD(HL),#0
	INC HL
	DJNZ L6
	POP HL
	POP BC
	INC H
	DJNZ L5
;	Атрибуты.

	RET
;-------------------------------------------------
; Вывод без операции (наложение с затиранием)
;-------------------------------------------------
.globl _conio_setopt_nop
_conio_setopt_nop:
	ld a,#0x7E
	ld (out_char_mode),a
	ret
;-------------------------------------------------
; Вывод AND
;-------------------------------------------------
.globl _conio_setopt_and
_conio_setopt_and:
	ld a,#0xA6	; and (hl)
	ld (out_char_mode),a
	ret
;-------------------------------------------------
; Вывод OR
;-------------------------------------------------
.globl _conio_setopt_or
_conio_setopt_or:
	ld a,#0xB6	; or (hl)
	ld (out_char_mode),a
	ret
;-------------------------------------------------
; Вывод XOR
;-------------------------------------------------
.globl _conio_setopt_xor
_conio_setopt_xor:
	ld a,#0xAE	; xor (hl)
	ld (out_char_mode),a
	ret
;-------------------------------------------------
