#ifndef HERO_H
#define HERO_H
// Функции обработки действий героя и чертей
#include "scrHelper.h"

// Координаты героя
extern uint8_t hero_x;
extern uint8_t hero_y;

/**
 * @brief  Клавиши управления
 */
enum {
	kUp='7',
	kDown='6',
	kLeft='5',
	kRight='8'
};

/**
 * @brief Проверка движения (падение и проч)
 */
void check_hero();

#endif // HERO_H
