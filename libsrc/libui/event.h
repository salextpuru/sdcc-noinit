#ifndef EVENT_H
#define EVENT_H

#include <stdint.h>

/**
 * @brief Типы событий
 */
typedef enum evType{
	// Пустое событие (событий нет)
	evEmpty=0,
	// Ожидание. Рассылается всем потомкам
	evIdle=1,
	// Нажата клавиша с кодом key
	evKbd=2,
	// Команда. Посылается в главный цикл обработки о детей
	evCmd=3,
	// Завершение текущего цикла обработки (закрытие окна)
	evClose=4
}evType;

/**
 * @brief Описатель события
 */
typedef struct {
	/** @brief Тип события */
	evType	ev;
	/** @brief В зависимости от типа события */
	union{
		uint16_t	key;
		uint16_t	cmd;
		void*		userData;
	};
}event;


#endif // EVENT_H
