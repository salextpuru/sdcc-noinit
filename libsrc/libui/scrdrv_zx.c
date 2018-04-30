/**
    @file scrfunc.c
    Функции для вывода на экран
*/
#include <scrfunc.h>

static void setcolor(tColor ink, tColor paper);

static uint32_t get_win_size(uint8_t w, uint8_t h);

static void asm_helper_zx();

static void clear_window(uint8_t x, uint8_t y, uint8_t w, uint8_t h);

static void putc(char c);

static void curpos(uint8_t x, uint8_t y);

static void puts(const char* s, uint8_t maxsize);

static void curset(tColor color, curTypes t);

static void store_window(scrDriverStored* buf, uint8_t x, uint8_t y, uint8_t w, uint8_t h);

static void restore_window(scrDriverStored* buf);

scrDriverFunc	scrDriver_ZX={
	/**
	 * @brief размеры экрана
	 */
	//uint8_t w;
	.w=32,
	//uint8_t h;
	.h=24,
	
	/**
	 * @brief Текущий цвет экрана (фон)
	 */
	//tColor	paper;
	.paper=0,
	
	/**
	 * @brief Текущий цвет экрана (тон)
	 */
	//tColor	ink;
	.ink=7,
	
	/**
	 * @brief Позиция курсора
	 */
	//uint8_t		cur_x;
	.cur_x=0,
	//uint8_t		cur_y;
	.cur_y=0,
	// tColor	cur_color;
	.cur_color=56,
	
	/**
	 * @brief Тип курсора
	 */
	//curTypes	cur_type;
	.cur_type=ctNone,
	
	/**
	 * @brief Установка цвета
	 */
	//void (*setcolor)(tColor ink, tColor paper);
	.setcolor=setcolor,
	
	/**
	 * @brief Очистка окна текущими цветами
	 *	Координаты режутся по краям экрана
	 */
	//void (*clear_window)(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
	.clear_window = clear_window,
	
	/**
	 * @brief Вычисление размера памяти, потребного для сохранения окна,
	 * 	заданного размера
	 */
	//uint32_t (*get_win_size)(uint8_t w, uint8_t h);
	.get_win_size=get_win_size,
	
	/**
	 * @brief Сохранить окно заданного размера в буфере
	 */
	//void	(*store_window)(scrDriverStored* buf, uint8_t x, uint8_t y, uint8_t w, uint8_t h);
	.store_window=store_window,
	
	/**
	 * @brief Вывести окно из буфера на экран
	 */
	//void	(*restore_window)(scrDriverStored* buf);
	.restore_window=restore_window,
	
	/**
	 * @brief Вывести символ в позицию курсора цветом ink
	 */
	//void	(*putc)(char c);
	.putc = putc,
	
	/**
	 * @brief Вывести строку в позицию курсора
	 * 	Выводится не более maxsize символов
	 */
	//void	(*puts)(const char* s, uint8_t maxsize);
	.puts = puts,
	
	/**
	 * @brief Установить позицию позицию курсора
	 */
	//void	(*curpos)(uint8_t x, uint8_t y);
	.curpos = curpos,
	
	/**
	 * @brief Установить тип курсора
	 */
	//void	(*curset)(tColor color, curTypes t);
	
	/**
	 * @brief Вывести рамку заданного типа
	 */
	// void	(*border)(borderTypes btype, uint8_t x, uint8_t y, uint8_t w, uint8_t h);
	.border = borderUI
};

/**
 *	Переменные драйвера
 */

// Начало экрана (для экрана 0 - 0x4000, для экрана 7 - 0xC000)
static uint16_t	ScrBegin=0x4000;

static void	curset(tColor color, curTypes t){
	if( scrDriver_ZX.cur_type != btNone){
		// Убрать курсор
	}
	
	scrDriver_ZX.cur_color = color;
	scrDriver_ZX.cur_type = t;
	
	if( scrDriver_ZX.cur_type != btNone){
		// нарисовать курсор
	}
}

static uint8_t getColor(){
	return ((uint8_t)scrDriver_ZX.ink) | ((uint8_t)scrDriver_ZX.paper);
}

static void setcolor(tColor ink, tColor paper){
	register uint16_t i=ink;
	register uint16_t p=paper;
	scrDriver_ZX.ink = i;
	scrDriver_ZX.paper = p;
}

static uint32_t get_win_size(uint8_t w, uint8_t h){
	// w*h*8 + w*h
	return( w*h*9 + sizeof(scrDriverStored) );
}

static void curpos(uint8_t x, uint8_t y){
	scrDriver_ZX.cur_x=x;
	scrDriver_ZX.cur_y=y;
}

static void clear_window(uint8_t x, uint8_t y, uint8_t w, uint8_t h)__naked{
__asm;
	push	ix
	ld	ix,#4
	add	ix,sp
	;//
	ld 	d,00(ix)
	ld 	e,01(ix)
	ld 	c,03(ix)
	ld 	b,02(ix)
	push	bc
	push	de
	call	wclear_asm
	call	_getColor
	pop	de
	pop	bc
	;//
	call	attrset_asm
	;//
	pop	ix
	ret
__endasm;
}

// Тут всякие подпрограммы на ассемблере
static void asm_helper_zx()__naked{
__asm;
;//-----------------------------------------------------------------------------
;// Рассчёт адреса по координатам (в знакоместах)
;//
;// вход:
;//	D - x-координата
;//	E - y-координата
;// Выход:
;//	HL - адрес в экранном файле
calc_sadr:
	ld	hl,#(_ScrBegin+1)
	ld	a,e
	and	#0x18
	add	(hl)
	ld	h,a
	ld	a,e
	and	#0x07
	or	a
	rra
	rra
	rra
	rra
	add	a,d
	ld	l,a
	ret
;//------------------------------------------------------------------------------
;// Рассчёт адреса атрибутов по координатам (в знакоместах)
;//
;// вход:
;//	D - x-координата
;//	E - y-координата
;// Выход:
;//	HL - адрес в файле атрибутов
calc_aadr:
	ld	hl,#(_ScrBegin+1)
	ld	a,e
	and	#0x18
	srl	a
	srl	a
	srl	a
	;//
	add	a,(hl)
	add	a,#0x18
	;//
	ld	h,a
	ld	a,e
	and	#0x07
	rra
	rra
	rra
	rra
	add	a,d
	ld	l,a
	ret
;//------------------------------------------------------------------------------
;// Очистка окна (без атрибутов)
;//	D - x
;//	E - y
;//	B - w
;//	C - h
;//------------------------------------------------------------------------------
wclear_asm:
next_l:
	push	de		;//p1
	push	bc		;//p2
	;// Вычисление адреса по координатам
	call	calc_sadr
	;//
	xor	a
	ld	c,#8		;// 8 линий в строке символов
nextll:
	push	hl		;//p3
	push	bc		;//p4
	;// очистка одной линии в строке символов
nextw:
	ld	(hl),a
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
	pop	de		;//g1
	;//
	inc	e		;// y+=1
	dec	c		;// h-=1
	jr nz,	next_l
	ret
;//------------------------------------------------------------------------------
;//	Установка атрибутов окна
;//	D - x
;//	E - y
;//	B - w
;//	C - h
;//	A - attr
;//------------------------------------------------------------------------------
attrset_asm:
	;// Вычисление адреса по координатам
	push	af
	call	calc_aadr
	pop	af
	;//
	ld	de,#0x0020	;// для ускорения - ширина экрана
attrh:
	push	bc
	push	hl
attrw:
	ld	(hl),a
	inc	hl
	djnz	attrw
	pop	hl
	pop	bc
	add	hl,de
	dec	c
	jr nz,	attrh
	RET
;//-----------------------------------------------------------------------------
__endasm;
}

static void _putc(char c, uint8_t x, uint8_t y)__naked{
	c; x; y;
__asm;
	push	ix
	ld	ix,#4
	add	ix,sp
	ld 	a, 0(ix)
	ld 	e,1(ix)
	ld 	d,2(ix)
	
;// DE - координаты (Dy Ex), A - код символа
out_char:
	; HL - symbol in font adr
	LD L,A
        LD H,#0
        ADD HL,HL
        ADD HL,HL
        ADD HL,HL
        LD BC,(_current_font)
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
        ld A,(_ScrBegin+1)
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
        call	_getColor ;// l= color
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
        ld a,l
        LD (de),a
	; // Return
	pop	ix
	ret
__endasm;
}

static void putc(char c){
	_putc(c, scrDriver_ZX.cur_x, scrDriver_ZX.cur_y );
}

static void puts(const char* s, uint8_t maxsize){
	uint8_t counter=0;
	
	while( (*s) && ( (counter<maxsize) || (maxsize==0) ) ){
		if( scrDriver_ZX.cur_x < scrDriver_ZX.w ){
			putc(*(s++));
			counter++;
			scrDriver_ZX.cur_x++;
		}
		else{
			scrDriver_ZX.cur_x=0;
			scrDriver_ZX.cur_y++;
			break;
		}
		
	}
}

void setScrDriverZX(){
	txt_screen_driver=&scrDriver_ZX;
	boxSingle="\x80\x81\x82\x83\x84\x85";
	boxDouble="\xA0\xA1\xA5\xA8\xAB\xAE";
}

static void	store_window(scrDriverStored* buf, uint8_t x, uint8_t y, uint8_t w, uint8_t h)__naked{
__asm;
	push	ix
	ld	ix,#4
	add	ix,sp
	;//
	ld	l,0(ix) ;// buf
	ld	h,1(ix)
	;// 
	ld 	(hl),#0	;// modeZX
	inc	hl
	ld 	d,2(ix); // x
	ld 	(hl),d
	inc	hl
	ld 	e,3(ix); // y (DE=xy)
	ld 	(hl),e
	inc	hl
	ld 	a,4(ix); // w
	ld 	(hl),a
	inc	hl
	ld 	a,5(ix); // h
	ld 	(hl),a
	inc 	hl
	;
	push	hl	;// hl = datap[];
			;// DE=xy
	call calc_sadr	;// HL=screen adr
	pop	de	;// de = datap[];
	;// copy form hl to de
	;// Высота спрайта
	ld	b,5(ix)
	;// Начало цикла по строкам
store_window_hline:
	push	bc
	;// высота знакоместа (строки)
	ld	c,#8
	push	hl
	;// выводим 8 линий (одну строку)
store_window_line8:
	ld	b,4(ix)
	;// выводим w байт (одну линию)
	push	hl
store_window_line:
	ld	a,(hl)
	ld	(de),a
	inc	hl
	inc	de
	dec	b
	jr nz,	store_window_line
	pop	hl
	;// следующая линия экрана
	inc	h
	dec	c
	jr nz,	store_window_line8
	pop	hl
	;// Следующая строка
	ld	a,#0x20
	add	a,l
	ld	l,a
	;// Если был перенос - то переход к след. трети экрана
	jr	nc, store_window_1_3
	;// следующая треть экрана
	ld	a,#0x08
	add	a,h
	ld	h,a		; hl = hl + 0x0800
store_window_1_3:
	; Вывод в ту же треть экрана
	pop	bc
	djnz	store_window_hline	; Конец цикла по строкам (та же треть)
	
	;// атрибуты
	push de
	ld 	d,2(ix);
	ld 	e,3(ix);
	call	calc_aadr
	pop de
	;//
	;// Высота спрайта
	ld	b,5(ix)
	ld	c,4(ix)
	;// Начало цикла по строкам
store_windowa_hline:
	;// линия
	push	bc
	push	hl

store_windowa_line:
	ld	a,(hl)
	ld	(de),a
	inc	de
	inc	hl
	dec	c
	jr nz, store_windowa_line

	pop	hl
	ld	bc,#0x0020
	add	hl,bc
	pop	bc
	djnz	store_windowa_hline
	
	;// Выход, если всё
	pop	ix
	ret
__endasm;
}

static void	restore_window(scrDriverStored* buf)__naked{
__asm;
	push	ix
	ld	ix,#4
	add	ix,sp
	;//
	ld	l,0(ix) ;// HL=buf
	ld	h,1(ix)
	push	hl
	pop	ix	;// IX=buf
	;//
	ld 	de,#5
	add	hl,de
	push	hl 	;// hl = datap[];
	;//
	ld	e,2(ix) ;
	ld	d,1(ix)	;// DE=xy
	;//
	call calc_sadr	;// HL=screen adr
	pop	de	;// de = datap[];
	;// copy form hl to de
	;// Высота спрайта
	ld	b,4(ix)
	;// Начало цикла по строкам
restore_window_hline:
	push	bc
	;// высота знакоместа (строки)
	ld	c,#8
	push	hl
	;// выводим 8 линий (одну строку)
restore_window_line8:
	ld	b,3(ix)
	;// выводим w байт (одну линию)
	push	hl
restore_window_line:
	ld	a,(de)
	ld	(hl),a
	inc	hl
	inc	de
	dec	b
	jr nz,	restore_window_line
	pop	hl
	;// следующая линия экрана
	inc	h
	dec	c
	jr nz,	restore_window_line8
	pop	hl
	;// Следующая строка
	ld	a,#0x20
	add	a,l
	ld	l,a
	;// Если был перенос - то переход к след. трети экрана
	jr	nc, restore_window_1_3
	;// следующая треть экрана
	ld	a,#0x08
	add	a,h
	ld	h,a		;// hl = hl + 0x0800
restore_window_1_3:
	; Вывод в ту же треть экрана
	pop	bc
	djnz	restore_window_hline	; Конец цикла по строкам (та же треть)
	
	;// атрибуты
	push de
	ld 	d,1(ix);
	ld 	e,2(ix);
	call	calc_aadr
	pop de
	;//
	;// Высота спрайта
	ld	b,4(ix)
	ld	c,3(ix)
	;// Начало цикла по строкам
restore_windowa_hline:
	;// линия
	push	bc
	push	hl

restore_windowa_line:
	ld	a,(de)
	ld	(hl),a
	inc	de
	inc	hl
	dec	c
	jr nz, restore_windowa_line

	pop	hl
	ld	bc,#0x0020
	add	hl,bc
	pop	bc
	djnz	restore_windowa_hline
	
	;// Выход, если всё
	pop	ix
	ret
__endasm;
}
