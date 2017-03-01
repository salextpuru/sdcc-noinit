.include "ps2_const.hS"

        .module ps2_s
	.area	_CODE

;----------------------------------------------
; Init PS2 keyboard
.globl _InitPS2
_InitPS2:
	;
	ld	bc,	#0xEFF7
	ld	a,	#0x80
	out	(c),a
	;
	ld	bc,	#0xDFF7
	ld	a,	#0xFF
	out	(c),a
	;
	ld	bc,	#0xBFF7
	ld	a,	#0x02
	out	(c),a
	;
	ret
;----------------------------------------------
; Get scancode in HL
; L - scancode
; H - flags
;
; if E0 prefix then L bit 7 is 1
; if F0 (keyup) then H bit 0 is 1
;----------------------------------------------
.globl _GetPS2
_GetPS2:
ps2kbd_loop:
	ld	bc,	#0xDFF7
	ld	a,	#0xFF
	out	(c),a
	;
	ld	bc,	#0xBFF7
	in	a,(c)
	;
	cp	#0x00
	jr	z,ps2kbd_00
	cp	#0xF0
	jr	z,ps2kbd_F0
	cp	#0xE0
	jr	z,ps2kbd_E0
	cp	#0xFF
	jr	z,ps2kbd_FF
	jr	ps2kbd_translate
	; Переполнение буфера
ps2kbd_FF:
	;
	ld	bc,	#0xDFF7
	ld	a,	#0x0C
	out	(c),a
	ld	bc,	#0xBFF7
	ld	a,	#0x01
	out	(c),a
	; Не нажата ни одна клавиша
ps2kbd_00:
	ld	hl,#0
	ret
	; Префикс F0 (Отпускание клавиши)
ps2kbd_F0:
	ld	a,(ps2kbd_status)
	or	#0x01
	ld	(ps2kbd_status),a
	jr	ps2kbd_loop
	; Префикс E0
ps2kbd_E0:
	ld	a,(ps2kbd_status)
	or	#0x80
	ld	(ps2kbd_status),a
	jr	ps2kbd_loop
	; Считан код клавиши
ps2kbd_translate:
	ld	l,a
	ld	a,(ps2kbd_status)
	ld	h,a
	; Префикс E0 (в сканкоде устанавливаем 7й бит)
	and	#0x80
	or	l
	ld	l,a
	; Отпускание клавиши - бит 0 рег H
	ld	a,h
	and	#0x01
	ld	h,a
	; Обнуляем вспомогательный регистр
	xor	a
	ld	(ps2kbd_status),a
	;
	ret
	; Тут флаги - отпускание (бит 0) и расширенный код (бит 7)
ps2kbd_status:	.db #0x00
;----------------------------------------------

;----------------------------------------------
; Поиск кода по НL
; Вход:
;	HL: L - scancode H - flags
; Выход:
;	HL - адрес описателя (6 байт)
;	B = bit 1 0-pressed, 1-unpressed
;	a==0 - ничего не найдено
SearchPS2:
	push	hl
	pop	bc ; bc = hl
	;
	ld	hl,#recode_table
	ld	de,#0x0006 ; размер записи
SearchPS2Loop:
	ld a,(hl)
	; Конце таблички?
	or a
	ret z
	; Нашли что искали?
	cp c
	ret z
	; Продолжаем поиск
	add hl, de
	jr SearchPS2Loop
;----------------------------------------------

; Флаг KEXTEND - клавиша вне кои8
; KEXTEND=	1

; Флаг ICAPS - клавиша игнорирует постоянный регистр
ICAPS=	2

;----------------------------------------------
; Получить код клавиши в соответствии
; с учётом RUS-LAT ALT SHIFT
;----------------------------------------------
.globl _InKey
_InKey:
	push ix
	call InKey_IX_STORED
	pop ix
	ret
;
InKey_IX_STORED:
	; Получаем код и ищем его в таблице
	call	_GetPS2
	call	SearchPS2
	or	a
	jr	nz,inkey_found_key
	; Код не найден
inkey_not_found_key:
	ld	hl,#0x0000
	ret
	; Код найден
inkey_found_key:
	push	hl
	pop	ix ; ix=hl
	; Ищем код в таблице
	; Учитывая постоянные и временные флаги
	push	bc
	call	get_ext_code
	pop	bc
	; HL - ext code
	; B[0] = unpressed
	bit 0,b
	jr nz,inkey_unpress ; отпускание клавиши
	;
	bit 0,h
	jr nz,inkey_press_ext ; нажатие не-символа
	; Выход. В l - код символа KOI8R, h=0
	ret
; Нажата служебная клавиша
inkey_press_ext:
	ld a,l
	; CAPS
	cp #CAPS
	jr nz, noCAPS
	;
	ld a,(ModePS2_P)
	xor #(1<<PS2_CAPS)
	ld (ModePS2_P),a
	ld	hl,#0x0000
	ret
noCAPS:
	; SHIFT нажатие
	ld a,l
	cp #LSHIFT
	push af
	cp #RSHIFT
	push af
	pop bc
	pop de
	ld a,c
	or e
	bit 6,a
	jr z,noSHIFTp
	;
	ld a,(ModePS2_T)
	set PS2_SHIFT,a
	ld (ModePS2_T),a
	ld	hl,#0x0000
	ret
noSHIFTp:
	; ALT нажатие
	ld a,l
	cp #LALT
	push af
	cp #RALT
	push af
	pop bc
	pop de
	ld a,c
	or e
	bit 6,a
	jr z,noALTp
	;
	ld a,(ModePS2_T)
	set PS2_ALT,a
	ld (ModePS2_T),a
	ld	hl,#0x0000
	ret
noALTp:
	; CTRL нажатие
	ld a,l
	cp #LCTRL
	push af
	cp #RCTRL
	push af
	pop bc
	pop de
	ld a,c
	or e
	bit 6,a
	jr z,noCTRLp
	;
	ld a,(ModePS2_T)
	set PS2_CTRL,a
	ld (ModePS2_T),a
	ld	hl,#0x0000
	ret
noCTRLp:
	ret

; Отпущена клавиша
inkey_unpress:
	; Выход, если обычная клавиша
	bit 0,h
	jr z,inkey_not_found_key
	ld a,l
	; CAPS
	cp #CAPS
	jr nz, noCAPSu
	ld	hl,#0x0000
	ret
noCAPSu:
	; SHIFT отпускание
	ld a,l
	cp #LSHIFT
	push af
	cp #RSHIFT
	push af
	pop bc
	pop de
	ld a,c
	or e
	bit 6,a
	jr z,noSHIFTu
	;
	ld a,(ModePS2_T)
	res PS2_SHIFT,a
	ld (ModePS2_T),a
	; check RUS-LAT
	bit PS2_CTRL,a
	jr z, noRusLat
	; Переключаем
	ld a,(ModePS2_P)
	xor #(1<<PS2_RUS)
	ld (ModePS2_P),a
noRusLat:
	ld	hl,#0x0000
	ret
noSHIFTu:
	; ALT отпускание
	ld a,l
	cp #LALT
	push af
	cp #RALT
	push af
	pop bc
	pop de
	ld a,c
	or e
	bit 6,a
	jr z,noALTu
	ld a,(ModePS2_T)
	res PS2_ALT,a
	ld (ModePS2_T),a
	ld	hl,#0x0000
	ret
noALTu:
	; CTRL отпускание
	ld a,l
	cp #LCTRL
	push af
	cp #RCTRL
	push af
	pop bc
	pop de
	ld a,c
	or e
	bit 6,a
	jr z,noCTRLu
	ld a,(ModePS2_T)
	res PS2_CTRL,a
	ld (ModePS2_T),a
	ld	hl,#0x0000
	ret
noCTRLu:
	ld	hl,#0x0000
	ret

; Получить символ в соответствии с режимом ModePS2
; ix = адрес описателя
; ix+1 - лат. малые
; ix+2 - лат. заглавные
; ix+3 - рус. малые
; ix+4 - рус. заглавные
; ix+5 - флаги.
;	ICAPS - не учитывать постоянный CAPS (только shift)
;	KEXTEND - расширенный код (несимвол) >255
; Выход - HL - расширенный код (l - KOI8, если h=0)
get_ext_code:
	; rus-lat
	ld	a,(ModePS2_P)
	ld	c,a
	ld	a,(ModePS2_T)
	xor	a,c ; Постоянно-временная шняга
	; Рус-лат
	bit	PS2_RUS,a
	jr	z, get_ext_code_lat
	ld	de,#0x003 ; смещение в таблице отн IX
	jr	get_ext_check_shift
	ret

get_ext_code_lat:
	ld	de,#0x001 ; смещение в таблице отн IX
	; Проверка Shift и Caps
get_ext_check_shift:
	ld	c,#0 ; Для инорирования CAPS
	ld	a,#ICAPS
	and	5(IX)
	jr nz,	get_ext_igncaps
	; Учитываем CAPS
	ld	a,(ModePS2_P)
	ld	c,a
	; Игнор CAPS
get_ext_igncaps:
	ld	a,(ModePS2_T)
	xor	a,c ; Постоянно-временная шняга
	;
	bit	PS2_CAPS,a
	jr	z, get_ext_code_small
	; Заглавные 
	inc	de
get_ext_code_small:
	; Код символа - в HL
	ld	a,#KEXTEND
	and	5(ix)
	ld	h,a
	add	ix,de
	ld	l,0(ix)
	;
	ret

; Постоянные режимы
ModePS2_P: ; PS2_RUS PS2_CAPS
	.db	0x00

; Временные режимы
ModePS2_T: ; PS2_ALT PS2_SHIFT PS2_CTRL
	.db	0x00

; Проверка нажатия CTRL
.globl _IsCTRL
_IsCTRL:
	ld	a,(ModePS2_T)
	bit	PS2_CTRL,a
	and 	#(1<<PS2_CTRL)
	ld	l,a
	ret

; Проверка нажатия ALT
.globl _IsALT
_IsALT:
	ld	a,(ModePS2_T)
	bit	PS2_ALT,a
	and 	#(1<<PS2_ALT)
	ld	l,a
	ret

; Проверка нажатия SHIFT
.globl _IsSHIFT
_IsSHIFT:
	ld	a,(ModePS2_T)
	bit	PS2_SHIFT,a
	and 	#(1<<PS2_SHIFT)
	ld	l,a
	ret

; Проверка Режима (рус-лат)
.globl _IsRUS
_IsRUS:
	ld	a,(ModePS2_P)
	ld	c,a
	ld	a,(ModePS2_T)
	xor	a,c ; Постоянно-временная шняга
	
	bit	PS2_RUS,a
	and 	#(1<<PS2_RUS)
	ld	l,a
	ret

; Проверка заглавные-строчные
.globl _IsUPPER
_IsUPPER:
	ld	a,(ModePS2_P)
	ld	c,a
	ld	a,(ModePS2_T)
	xor	a,c ; Постоянно-временная шняга
	
	bit	PS2_CAPS,a
	and 	#(1<<PS2_CAPS)
	ld	l,a
	ret

; Таблица перекодировки (KOI8R)
recode_table:
	;  scan		llat	ulat	lrus	urus	flags
	;  +0		+1	+2	+3	+4	+5

	; Осн. символы
	.db 0x1C,	'a',	'A',	'ф'|0x80,	'Ф'|0x80,	0
	.db 0x32,	'b',	'B',	'и'|0x80,	'И'|0x80,	0
	.db 0x21,	'c',	'C',	'с'|0x80,	'С'|0x80,	0
	.db 0x23,	'd',	'D',	'в'|0x80,	'В'|0x80,	0
	.db 0x24,	'e',	'E',	'у'|0x80,	'У'|0x80,	0
	.db 0x2B,	'f',	'F',	'а'|0x80,	'А'|0x80,	0
	.db 0x34,	'g',	'G',	'п'|0x80,	'П'|0x80,	0
	.db 0x33,	'h',	'H',	'р'|0x80,	'Р'|0x80,	0
	.db 0x43,	'i',	'I',	'ш'|0x80,	'Ш'|0x80,	0
	.db 0x3B,	'j',	'J',	'о'|0x80,	'О'|0x80,	0
	.db 0x42,	'k',	'K',	'л'|0x80,	'Л'|0x80,	0
	.db 0x4B,	'l',	'L',	'д'|0x80,	'Д'|0x80,	0
	.db 0x3A,	'm',	'M',	'ь'|0x80,	'Ь'|0x80,	0
	.db 0x31,	'n',	'N',	'т'|0x80,	'Т'|0x80,	0
	.db 0x44,	'o',	'O',	'щ'|0x80,	'Щ'|0x80,	0
	.db 0x4D,	'p',	'P',	'з'|0x80,	'З'|0x80,	0
	.db 0x15,	'q',	'Q',	'й'|0x80,	'Й'|0x80,	0
	.db 0x2D,	'r',	'R',	'к'|0x80,	'К'|0x80,	0
	.db 0x1B,	's',	'S',	'ы'|0x80,	'Ы'|0x80,	0
	.db 0x2C,	't',	'T',	'е'|0x80,	'Е'|0x80,	0
	.db 0x3C,	'u',	'U',	'г'|0x80,	'Г'|0x80,	0
	.db 0x2A,	'v',	'V',	'м'|0x80,	'М'|0x80,	0
	.db 0x1D,	'w',	'W',	'ц'|0x80,	'Ц'|0x80,	0
	.db 0x22,	'x',	'X',	'ч'|0x80,	'Ч'|0x80,	0
	.db 0x35,	'y',	'Y',	'н'|0x80,	'Н'|0x80,	0
	.db 0x1A,	'z',	'Z',	'я'|0x80,	'Я'|0x80,	0
	.db 0x54,	'[',	'{',	'х'|0x80,	'Х'|0x80,	0
	.db 0x5B,	']',	'}',	'ъ'|0x80,	'Ъ'|0x80,	0
	.db 0x4C,	0x3B,	':',	'ж'|0x80,	'Ж'|0x80,	0 ; -;-
	.db 0x52,	0x27,	0x22,	'э'|0x80,	'Э'|0x80,	0 ; ' "
	.db 0x41,	',',	'<',	'б'|0x80,	'Б'|0x80,	0
	.db 0x49,	'.',	'>',	'ю'|0x80,	'Ю'|0x80,	0
	.db 0x0E,	'`',	'~',	'ё'|0x80,	'Ё'|0x80,	0
	.db 0x29,	' ',	' ',	' ',	' ',	0 ; пробел

	; Знаки
	.db 0x4A,	'/',	'?',	'.',	',',	ICAPS
	.db 0x5D,	"\\",	"|",	"\\",	"/",	ICAPS
	.db 0x4E,	'-',	'_',	'-',	'_',	ICAPS
	.db 0x55,	'=',	'+',	'=',	'+',	ICAPS

	; Цифры
	.db 0x45,	'0',	0x29,	'0',	0x29,	ICAPS ; )
	.db 0x16,	'1',	'!',	'1',	'!',	ICAPS
	.db 0x1E,	'2',	'@',	'2',	0x22,	ICAPS
	.db 0x26,	'3',	'#',	'3',	'N',	ICAPS
	.db 0x25,	'4',	'$',	'4',	0x3B,	ICAPS ; точка с запятой никак...
	.db 0x2E,	'5',	'%',	'5',	'%',	ICAPS
	.db 0x36,	'6',	'^',	'6',	':',	ICAPS
	.db 0x3D,	'7',	'&',	'7',	'?',	ICAPS
	.db 0x3E,	'8',	'*',	'8',	'*',	ICAPS
	.db 0x46,	'9',	0x28,	'9',	0x28,	ICAPS ; (

	; спец
	.db 0x5A,	0x0A,	0x0A,	0x0A,	0x0A,	0 ; Enter
	.db 0x66,	0x08,	0x08,	0x08,	0x08,	0 ; Back Space
	.db 0x0D,	0x09,	0x09,	0x09,	0x09,	0 ; TAB
	.db 0x76,	0x1B,	0x1B,	0x1B,	0x1B,	0 ; ESC
	
	; Расширенные
	.db 0x58,	CAPS,	CAPS,	CAPS,	CAPS,	KEXTEND
	
	.db 0x12, LSHIFT, LSHIFT, LSHIFT, LSHIFT, KEXTEND
	.db 0x59, RSHIFT, RSHIFT, RSHIFT, RSHIFT, KEXTEND

	.db 0x11, LALT, LALT, LALT, LALT, KEXTEND
	.db 0x91, RALT, RALT, RALT, RALT, KEXTEND

	.db 0x14, LCTRL, LCTRL, LCTRL, LCTRL, KEXTEND
	.db 0x94, RCTRL, RCTRL, RCTRL, RCTRL, KEXTEND

	.db 0x9F, LWIN, LWIN, LWIN, LWIN, KEXTEND
	.db 0xA7, RWIN, RWIN, RWIN, RWIN, KEXTEND

	.db 0xF0, INSERT, INSERT, INSERT, INSERT, KEXTEND
	.db 0xEC, HOME, HOME, HOME, HOME, KEXTEND

	.db 0xFD, PGUP, PGUP, PGUP, PGUP, KEXTEND
	.db 0xFA, PGDN, PGDN, PGDN, PGDN, KEXTEND

	.db 0xF1, KDELETE, KDELETE, KDELETE, KDELETE, KEXTEND
	.db 0xE9, KEND, KEND, KEND, KEND, KEXTEND

	.db 0xF5, UP, UP, UP, UP, KEXTEND
	.db 0xF2, DN, DN, DN, DN, KEXTEND
	.db 0xEB, LEFT, LEFT, LEFT, LEFT, KEXTEND
	.db 0xF4, RIGHT, RIGHT, RIGHT, RIGHT, KEXTEND

	.db 0x05, F1,F1,F1,F1, KEXTEND
	.db 0x06, F2,F2,F2,F2, KEXTEND
	.db 0x04, F3,F3,F3,F3, KEXTEND
	.db 0x0C, F4,F4,F4,F4, KEXTEND
	.db 0x03, F5,F5,F5,F5, KEXTEND
	.db 0x0B, F6,F6,F6,F6, KEXTEND
	.db 0x83, F7,F7,F7,F7, KEXTEND
	.db 0x0A ,F8,F8,F8,F8, KEXTEND
	.db 0x01 ,F9,F9,F9,F9, KEXTEND
	.db 0x09 ,F10,F10,F10,F10, KEXTEND
	.db 0x78 ,F11,F11,F11,F11, KEXTEND
	.db 0x07 ,F12,F12,F12,F12, KEXTEND

	.db 0x77, NUMLOCK, NUMLOCK, NUMLOCK, NUMLOCK, KEXTEND
	.db 0xCA, KPDIV, KPDIV, KPDIV, KPDIV, KEXTEND
	.db 0x7C, KPMUL, KPMUL, KPMUL, KPMUL, KEXTEND
	.db 0x7B, KPMIMUS, KPMIMUS, KPMIMUS, KPMIMUS, KEXTEND
	.db 0x79, KPPLUS, KPPLUS, KPPLUS, KPPLUS, KEXTEND
	.db 0xDA, KPENTER, KPENTER, KPENTER, KPENTER, KEXTEND
	.db 0x71, KPPOINT, KPPOINT, KPPOINT, KPPOINT, KEXTEND

	.db 0x70, KP0, KP0, KP0, KP0, KEXTEND
	.db 0x69, KP1, KP1, KP1, KP1, KEXTEND
	.db 0x72, KP2, KP2, KP2, KP2, KEXTEND
	.db 0x7A, KP3, KP3, KP3, KP3, KEXTEND
	.db 0x6B, KP4, KP4, KP4, KP4, KEXTEND
	.db 0x73, KP5, KP5, KP5, KP5, KEXTEND
	.db 0x74, KP6, KP6, KP6, KP6, KEXTEND
	.db 0x6C, KP7, KP7, KP7, KP7, KEXTEND
	.db 0x75, KP8, KP8, KP8, KP8, KEXTEND
	.db 0x7D, KP9, KP9, KP9, KP9, KEXTEND

	; Конец таблицы
	.db 0x00
