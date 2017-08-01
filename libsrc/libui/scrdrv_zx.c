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
	//uint16_t	paper;
	.paper=0,
	
	/**
	 * @brief Текущий цвет экрана (тон)
	 */
	//uint16_t	ink;
	.ink=7,
	
	/**
	 * @brief Позиция курсора
	 */
	//uint8_t		cur_x;
	.cur_x=0,
	//uint8_t		cur_y;
	.cur_y=0,
	
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
	//void	(*store_window)(void* buf, uint8_t x, uint8_t y, uint8_t w, uint8_t h);
	
	/**
	 * @brief Вывести окно из буфера на экран
	 */
	//void	(*restore_window)(void* buf, uint8_t x, uint8_t y, uint8_t w, uint8_t h);
	
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
	//void	(*border)(borderTypes btype, uint8_t x, uint8_t y, uint8_t w, uint8_t h);
};

/**
 *	Переменные драйвера
 */

// Начало экрана (для экрана 0 - 0x4000, для экрана 7 - 0xC000)
static uint16_t	ScrBegin=0x4000;

static void setcolor(tColor ink, tColor paper){
	scrDriver_ZX.ink = ink;
	scrDriver_ZX.paper = paper;
}

static uint32_t get_win_size(uint8_t w, uint8_t h){
	// w*h*8 + w*h
	return( w*h*9 );
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
	pop	de
	pop	bc
	;//
	ld 	a,(_scrDriver_ZX+2)
	ld	l,a
	ld 	a,(_scrDriver_ZX+4)
	or	a,l
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
	;//--------------------------------------
	xor	a
	ld	6(ix),a ;// cx
	ld	7(ix),a ;// cy
	;//--------------------------------------
	RET
;//-----------------------------------------------------------------------------
__endasm;
}

static void putc(char c){
	volatile uint8_t x = scrDriver_ZX.cur_x;
	volatile uint8_t y = scrDriver_ZX.cur_y;
	volatile uint8_t i = scrDriver_ZX.ink;
	volatile uint8_t p = scrDriver_ZX.paper;
__asm;
	ld 	a, 4(ix)
	ld 	e,-4(ix)
	ld 	d,-3(ix)
	
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
        ld 	a,-2(ix)
	ld	l,a
	ld 	a,-1(ix)
	or	a,l
        LD (DE),A
__endasm;
	; // Return automatic
}
