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

/**
 * @brief Рисует один блок сцены с заданными координатами
 */
void draw_scene_block ( const scrPlan scn, uint8_t x, uint8_t y );


// Окружение точки (то есть заданного блока на карте, ф-ця getPointArea)
extern uint8_t point_on; // символ на заданном месте карты
extern uint8_t point_up; // символ над заданным местом карты
extern uint8_t point_dn; // символ под заданным местом карты
extern uint8_t point_rt; // символ справа от заданного места карты
extern uint8_t point_lf; // символ слева от заданного места карты
extern uint8_t* point_p; // указатель на заданном месте карты

/**
 * @brief Получить окружение точка x,y
 *  и поместить его в hero_xx
 */
void getPointArea ( uint8_t x, uint8_t y );

#endif // SCENES_H
