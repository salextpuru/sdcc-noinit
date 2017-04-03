#ifndef TIMERS_H
#define TIMERS_H

#include <stdint.h>

/**
 * @brief Идентификатор таймера
 */
typedef uint16_t timerid;

/**
 * @brief тики таймера
 */
typedef uint16_t timert;

/**
 * @brief Инициализация пула таймеров
 */
void timers_init();

/**
 * @brief Завершение работы с пулом таймеров
 */
void timers_done();

/**
 * @brief Получить таймер
 * 
 * @return timerid
 */
timerid add_timer();

/**
 * @brief Установить таймер
 * 
 * @param t - Идентификатор таймера
 * @param ticks - сколько тиков установить
 * @return timert
 */
timert set_timer( timerid t, timert ticks);

/**
 * @brief Получить сколько тиков осталось
 * 
 * @param t - Идентификатор таймера
 * @return timert
 */
timert get_timer( timerid t );

/**
 * @brief Освободить таймер
 * 
 * @param t - Идентификатор таймера
 */
void del_timer( timerid t );

#endif // TIMERS_H
