/**
    @file scrfunc.c
    Функции для вывода на экран
*/
#include <scrfunc.h>

static scrDriverFunc	scrDriver_ZX={
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
	//uint32_t	paper;
	.paper=0,
	
	/**
	 * @brief Текущий цвет экрана (тон)
	 */
	//uint32_t	ink;
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
	
	/**
	 * @brief Вывести строку в позицию курсора
	 * 	Выводится не более maxsize символов,
	 * 	остальное добивается пробелами,
	 * 	если строка короче maxsize
	 */
	//void	(*puts)(const char* s, uint8_t maxsize);
	
	/**
	 * @brief Установить позицию позицию курсора
	 */
	//void	(*curpos)(uint8_t x, uint8_t y);
	
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
uint16_t	ScrBegin=0x4000;


static void setcolor(tColor ink, tColor paper){
	scrDriver_ZX.ink = ink;
	scrDriver_ZX.paper = paper;
}

uint32_t get_win_size(uint8_t w, uint8_t h){
	// w*h*8 + w*h
	return( w*h*9 );
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