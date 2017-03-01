#ifndef CONIO_H_DEFINED
#define CONIO_H_DEFINED

#include <types.h>
#include <stdio.h>
#include "conio_const.h"

/**
 * Печать строки (с управляющими символами - AT, TAB..)
 */
void print(const char* s)__naked;

/**
 * Очистка экрана текущим цветом
 */
void cls()__naked;

/**
 * Очистка экрана заданным цветом
 */
void ccls(BYTE c)__naked;

/**
 * Установить постоянные цвета
 */
void color(BYTE c)__naked;

void conio_setopt_nop()__naked;
void conio_setopt_and()__naked;
void conio_setopt_or()__naked;
void conio_setopt_xor()__naked;

void conio_at(uint8_t x, uint8_t y);

void conio_where(uint8_t* x, uint8_t* y);

#endif /* CONIO_H_DEFINED */
