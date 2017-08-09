#ifndef HERO_H
#define HERO_H
// Функции обработки действий героя и чертей
#include "scrHelper.h"

// Окружение героя (ф-ця getMedia)
extern uint8_t hero_on; // символ на месте героя
extern uint8_t hero_up; // символ над героем
extern uint8_t hero_dn; // символ под героем
extern uint8_t hero_rt; // символ справа
extern uint8_t hero_lf; // символ слева
extern uint8_t* hero_p; // указатель на символ на месте героя

// Координаты героя
extern uint8_t hero_x;
extern uint8_t hero_y;

/**
 * @brief Получить окружение точка x,y
 *  и поместить его в hero_xx
 */
void getMedia( uint8_t x, uint8_t y );

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

/**
 * @brief Отрисовка героя
 */
void draw_hero();

#endif // HERO_H
