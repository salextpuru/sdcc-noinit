#ifndef SCRHELPER_H
#define SCRHELPER_H

#include <stdint.h>

enum {
	sceneW=32,
	sceneH=22
};

typedef uint8_t scrPlan[sceneH][sceneW];

/**
 * @brief Инициализация экрана с 0xC000
 */
void scrInit();
 
/**
 * @brief Перенос экрана с 0xC000 в 0x4000
 */
void scrFlip();

/**
 * @brief Рисовать фон (лесенки и прочие кирпичи)
 */
void draw_scene(const scrPlan scn);


#endif // SCRHELPER_H
