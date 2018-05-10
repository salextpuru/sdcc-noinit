#ifndef __LOGOS__H__
#define __LOGOS__H__

#include <spr0.h>

// Базовая картинка
extern const Sprite0	logos_base;
// сменяемые картинки
extern const Sprite0*	logos[];
// Возвращает количество сменяемых картинок
uint8_t	logos_count();

#endif /* __LOGOS__H__ */
