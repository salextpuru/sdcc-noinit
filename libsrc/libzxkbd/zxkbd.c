/*
 * Alex Shamin
 * INCOM Tomsk
 * 04:08:2017
 */

#include "zxkbd.h"

//--------------------------------------------------------
// info
//-------------------------------------------------------
//		Data in(port)
// Port	 Adr   0  1  2  3  4
//
// #FEFE  A8   CS  Z  X  С  V
// #FDFE  A9    A  S  D  F  G
// #FBFE  A10   Q  W  E  R  Т
// #F7FE  A11   1  2  3  4  5
// #EFFE  А12   0  9  8  7  6
// #DFFE  A13   P  O  I  U  Y
// #BFFE  A14   En L  K  J  H  
// #7FFE  A15   SP SS M  N  B
//-------------------------------------------------------
//		Data in(port) 		( Ъ Х Э Ж Ю Б Ё )
// Port	 Adr   0  1  2  3  4
//
// #FEFE  A8   CS  Я  Ч  С  М
// #FDFE  A9    Ф  Ы  В  А  П
// #FBFE  A10   Й  Ц  У  К  Е
// #F7FE  A11   1  2  3  4  5
// #EFFE  А12   0  9  8  7  6
// #DFFE  A13   З  Щ  Ш  Г  Н
// #BFFE  A14   En Д  Л  О  Р
// #7FFE  A15   SP SS И  Т  Ь
//-------------------------------------------------------

enum ctlCode{
	CS=1,
	SS=2,
	En=13
};

// Lat Upper Case
static const uint8_t lat_upper[40]={
	 CS, 'Z', 'X', 'С', 'V',	// #FEFE
	'A', 'S', 'D', 'F', 'G',	// #FDFE
	'Q', 'W', 'E', 'R', 'Т',	// #FBFE
	'1', '2', '3', '4', '5',	// #F7FE
	'0', '9', '8', '7', '6',	// #EFFE
	'P', 'O', 'I', 'U', 'Y',	// #DFFE
	 En, 'L', 'K', 'J', 'H',	// #BFFE
	' ',  SS, 'M', 'N', 'B'		// #7FFE
};

// Lat Lower Case
static const uint8_t lat_lower[50]={
	 CS, 'z', 'x', 'c', 'v',	// #FEFE
	'a', 's', 'd', 'f', 'g',	// #FDFE
	'q', 'w', 'e', 'r', 't',	// #FBFE
	'1', '2', '3', '4', '5',	// #F7FE
	'0', '9', '8', '7', '6',	// #EFFE
	'p', 'o', 'i', 'u', 'y',	// #DFFE
	 En, 'l', 'k', 'j', 'h',	// #BFFE
	' ',  SS, 'm', 'n', 'b'		// #7FFE
};

// Lat Upper Case + Symbol Shift
static const uint8_t lat_upper_SS[40]={
	 CS, ':', 'f', '?', '/',	// #FEFE
	'~', '|', '\\', '{','}',	// #FDFE
	'Q', 'W', 'E', '<', '>',	// #FBFE
	'!', '@', '#', '$', '%',	// #F7FE
	'_', ')','(', '\'', '&',	// #EFFE
	'\"',';', 'I', ']', '[',	// #DFFE
	 En, '=', '+', '-', '^',	// #BFFE
	' ',  SS, '.', ',', '*'		// #7FFE
};

// Lat Lower Case + Symbol Shift
#define lat_lower_SS lat_upper_SS

// RUS Upper Case ( Ъ Х Э Ж Ю Б Ё ) - только с SS
static const uint8_t rus_upper[40]={
	 CS, 'Я', 'Ч', 'С', 'М',	// #FEFE
	'Ф', 'Ы', 'В', 'А', 'П',	// #FDFE
	'Й', 'Ц', 'У', 'К', 'Е',	// #FBFE
	'1', '2', '3', '4', '5',	// #F7FE
	'0', '9', '8', '7', '6',	// #EFFE
	'З', 'Щ', 'Ш', 'Г', 'Н',	// #DFFE
	 En, 'Д', 'Л', 'О', 'Р',	// #BFFE
	' ',  SS, 'Ь', 'Т', 'И'		// #7FFE
};

// Ъ - SS+ Ь
// Х - SS+ К
// Э - SS+ Ы
// Ж - SS+ Г
// Ю - SS+ У
// Б - SS+ В
// Ё - SS+ Е

// RUS Upper Case ( Ъ Х Э Ж Ю Б Ё )
static const uint8_t rus_upper_ss[40]={
	 CS, 'Я', 'Ч', 'С', 'М',	// #FEFE
	'Ф', 'Э', 'Б', 'А', 'П',	// #FDFE
	'Й', 'Ц', 'Ю', 'Х', 'Ё',	// #FBFE
	'1', '2', '3', '4', '5',	// #F7FE
	'0', '9', '8', '7', '6',	// #EFFE
	'З', 'Щ', 'Ш', 'Ж', 'Н',	// #DFFE
	 En, 'Д', 'Л', 'О', 'Р',	// #BFFE
	' ',  SS, 'Ъ', 'Т', 'И'		// #7FFE
};

// rus lower case ( ъ х э ж ю б ё ) - только с ss
static const uint8_t rus_lower[40]={
	 CS, 'я', 'ч', 'с', 'м',	// #fefe
	'ф', 'ы', 'в', 'а', 'п',	// #fdfe
	'й', 'ц', 'у', 'к', 'е',	// #fbfe
	'1', '2', '3', '4', '5',	// #f7fe
	'0', '9', '8', '7', '6',	// #effe
	'з', 'щ', 'ш', 'г', 'н',	// #dffe
	 En, 'д', 'л', 'о', 'р',	// #bffe
	' ', SS, 'ь', 'т', 'и'		// #7ffe
};

// ъ - ss+ ь
// х - ss+ к
// э - ss+ ы
// ж - ss+ г
// ю - ss+ у
// б - ss+ в
// ё - ss+ е

// rus lower case ( ъ х э ж ю б ё )
static const uint8_t rus_lower_ss[40]={
	 CS, 'я', 'ч', 'с', 'м',	// #fefe
	'ф', 'э', 'б', 'а', 'п',	// #fdfe
	'й', 'ц', 'ю', 'х', 'ё',	// #fbfe
	'1', '2', '3', '4', '5',	// #f7fe
	'0', '9', '8', '7', '6',	// #effe
	'з', 'щ', 'ш', 'ж', 'н',	// #dffe
	 En, 'д', 'л', 'о', 'р',	// #bffe
	' ',  SS, 'ъ', 'т', 'и'		// #7ffe
};

static const uint8_t* mode_table[8]={
	lat_lower,
	lat_upper,
	lat_lower_SS,
	lat_upper_SS,
	rus_lower,
	rus_upper,
	rus_lower_ss,
	rus_upper_ss
	
};

// Задержка на дребезг
#define delayDrizg	5

// Маска Caps Shift
#define CS_MASK		1
#define CS_BIT		0
// Маска Symbol Shift
#define SS_MASK		2
#define SS_BIT		1
// Маска RUS
#define RU_MASK		4
#define RU_BIT		2
// Маска Caps Lock
#define CL_MASK		8
#define CL_BIT		3

// Задержка на дребезг
static uint8_t		key_pause=0;

// Таблица, скан-кодов-бит, считанная с порта
static uint8_t		scan_port[8];
static uint8_t		modes=0; // bit 0 - CS; 1 - SS 2 - rus 3 - caps lock

// текущая клавиша
static uint16_t		key;

uint16_t zxKbdInKey(){
	uint16_t k = key;
	key=0;
	return k;
}

void zxKbdScan()__naked{
__asm;
	;// Если задержка на дребезг - выходим,
	;// уменьшая счетчик
	ld 	a,(_key_pause)
	or 	a
	jr 	z, scanINTscanInit
	dec 	a
	ld 	(_key_pause),a
	;// Выход, если задержка по дребезгу
	ret
	;// Собственно сканирование
scanINTscanInit:
	ld 	hl,#_scan_port
	ld 	bc,#0xFEFE
scanINTscan:
	;//	Считываем. Если не 0x1f - то есть нажатие
	in	a,(c)
	and	#0x1F
	ld 	(hl),a
	inc 	hl
	;// Нет нажатия
	scf 		;// CY=1
	rl	b	;// b = b<<1 | 1
	;// Если CY=0, то все строки отсканированы.
	jr	c,scanINTscan
	
	;// Теперь в _scan_port вся таблица.
	;// Выставляем признаки SS и CS
	;// CS
	ld	a,(_scan_port+0)
	ld	b,a
	or 	a,#CS_MASK
	ld 	(_scan_port+0),a
	// SS
	ld	a,(_scan_port+7)
	ld	c,a
	or 	a,#SS_MASK
	ld 	(_scan_port+7),a
	;// 
	ld 	a,b
	and 	#CS_MASK
	ld 	b,a
	ld 	a,c
	and 	#SS_MASK
	or	b
	cpl
	and 	#(CS_MASK | SS_MASK)
	ld 	c,a
	ld 	a,(_modes)
	and 	#~(CS_MASK | SS_MASK)
	or 	c
	ld 	(_modes),a
	;// Признаки выставлены
	ld 	a,#3
	cp 	c
	jr	nz, noChangeLang
	;// Меняем раскладку
	ld	a,#delayDrizg
	ld 	(_key_pause),a
	ld 	a,(_modes)
	xor	#RU_MASK
	ld 	(_modes),a
	;// После смены раскладки - выход с пузой
	ret
	
	;// Тут же мы проверяем что нажато
noChangeLang:
	;// Выбор таблицы
	ld 	a,(_modes)
	bit 	CL_BIT,a
	jr	z, noCaps
	xor 	#CS_MASK
noCaps:
	and	#(CS_MASK | SS_MASK | RU_MASK) ;// a=number of table
	ld 	e,a
	ld	d,#0
	ld 	hl,#_mode_table
	add 	hl,de
	add 	hl,de	;// HL = HL + 2*DE
	ld 	e,(hl)
	inc 	hl
	ld 	d,(hl)
	ex 	de,hl
	;// HL = таблица
	ld 	de,#_scan_port
	ld 	b,#8
next_line:
	ld 	a,(de)
	cp	#0x1F
	jr 	nz, key_found
	push	de
	ld 	de,#5
	add 	hl,de
	pop 	de
	inc 	de
	djnz 	next_line
	;// Клавиш не нажато. выход
	ret
	
	;//
key_found:
	bit	0,a
	jr 	z,getCode
	inc 	hl
	rrca
	jr	key_found 
getCode:
	ld 	a,(hl)
	ld 	c,a
	;// Caps lock?
	cp 	a,#'2'
	jr 	nz,addKey
	ld 	a,(_modes)
	bit 	CS_BIT,a
	jr 	z,addKey
	;// Toggle CAPS LOCK
	xor	#CL_MASK
	ld 	(_modes),a
	;//
	jr	exitKbd
addKey:
	ld 	a,c
	ld 	(_key),a

exitKbd:
	;//
	ld	a,#delayDrizg
	ld 	(_key_pause),a
	;//
	ret
__endasm;
}

/**
 * @brief Получить язык
 */
uint8_t  zxKbdIsRus(){
	return (modes & RU_MASK)?1:0;
}

/**
 * @brief Установить язык
 */
uint8_t  zxKbdSetLang(uint8_t lang){
	modes = lang?(modes|RU_MASK):(modes&~RU_MASK);
}

/**
 * @brief Получить регистр
 */
uint8_t  zxKbdIsCaps(){
	uint8_t cl=(modes & CL_MASK)?1:0;
	return  (modes&CS_MASK)?cl^1:cl;
}

/**
 * @brief Установить регистр
 */
uint8_t  zxKbdSetCaps(uint8_t caps){
	modes = caps?(modes|CL_MASK):(modes&~CL_MASK);
}

uint8_t zxKbdIsSHIFT(){
	return (modes & CS_MASK)?1:0;
}

uint8_t zxKbdIsCTRL(){
	return (modes & SS_MASK)?1:0;
}

uint8_t zxKbdIsALT(){
	return 0;
}
