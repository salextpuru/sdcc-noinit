#ifndef CONIO_H_DEFINED
#define CONIO_H_DEFINED

#include <types.h>
#include <stdio.h>
#include "conio_const.h"

/**
 * Печать строки (с управляющими символами - AT, TAB..)
 */
void print(const char* s);

/**
 * Печать строки (с управляющими символами - AT, TAB..)
 	Не более strsize
 */
void nprint(const char* s, uint8_t strsize);

/**
 * Печать строки (с управляющими символами - AT, TAB..)
 	Не более strsize и доливает пробелы до strsize, если строка короче
 */
void nprintspc(const char* s, uint8_t strsize);

/**
 * Очистка экрана текущим цветом
 */
void cls();

/**
 * Очистка экрана заданным цветом
 */
void ccls(BYTE c);

/**
 * Установить постоянные цвета
 */
void color(BYTE c);

void conio_setopt_nop();
void conio_setopt_and();
void conio_setopt_or();
void conio_setopt_xor();

void conio_at(uint8_t x, uint8_t y);

void conio_where(uint8_t* x, uint8_t* y);

#endif /* CONIO_H_DEFINED */
