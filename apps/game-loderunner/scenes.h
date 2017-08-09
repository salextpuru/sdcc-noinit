#ifndef SCENES_H
#define SCENES_H

#include "scrHelper.h"

/**
 * @brief Размер сцены (знакоместа)
 */
enum {
	sceneW=32,
	sceneH=22
};

/**
 * @brief Тип-сцена
 */
typedef uint8_t scrPlan[sceneH][sceneW];

// Текущая сцена
extern scrPlan curScene;

// Сколько сундуков надо собрать?
extern uint8_t howTreasures;

/**
 * @brief Рисовать фон (лесенки и прочие кирпичи)
 */
void draw_scene(const scrPlan scn);

/**
 * @brief Декомпрессор сцены
 * 
 * @param scnz - упакованная сцена
 * @param scn - распакованная сцена
 */
void scn_decomp(uint8_t* scnz, scrPlan scn );

/**
 * @brief Распаковать и вывести на экран уровень
 * 
 * @param scnz 
 */
void setScene(uint8_t* scnz);

#endif // SCENES_H
