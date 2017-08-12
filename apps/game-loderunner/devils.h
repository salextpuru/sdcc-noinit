#ifndef DEVILS_H
#define DEVILS_H

#include "direct.h"

/**
 * @brief Описание черта
 */
typedef struct devil{
	// координаты
	uint8_t		x;
	uint8_t		y;
	
	// Направление движения
	uint8_t		direct;		//Сейчас
	uint8_t		direct_old;	// На предыдущем шаге
}devil;

/**
 * @brief Проверка и перерисовка чертей
 */
void check_devils();

/**
 * @brief Максимальное количество чертей
 */
enum {
	DevilsMax=16
};

/**
 * @brief Начать добавление чертей
 */
void StartAddDevils();

/**
 * @brief Добавить черта в x,y.
 * 	Если чертей уже DevilsMax,
 * черт не добавляется
 * 
 */
void AddDevil(uint8_t x, uint8_t y);

#endif // DEVILS_H
