#ifndef SOCKET_H
#define SOCKET_H

#include <stdint.h>
#include <stdint.h>

/**
 * @brief IP-адрес
 */
typedef uint32_t	zsockIPadr;

/**
 * @brief Порт
 */
typedef uint16_t	zsockPort;

/**
 * @brief Типы сокета
 */
typedef enum {
	zsockClient = 0,	// Клиентский (запращивающий)
	zsockServer = 1		// Серверный (слушающий)
} zsockTypes;

/**
 * @brief Типы протокола
 */
typedef enum {
	zprotTCP = 0,
	zprotUDP = 1
} zsockProtocol;


typedef struct {
	// Начало и конец работы
	int8_t	(*init)(void* adrs);
	int8_t	(*done)();
	
	// Создание соединения с кем-то
	int8_t  (*connectto)(void* adr);
	
	// Начать принимать соединения от когото
	int8_t  (*listen)(void* adr);
	
	// Закрыть соединение
	int8_t	(*close)(int8_t fd);
	
	// Читать
	int8_t	(*read)(int8_t fd, void* buf, int16_t size);
	
	// Читать
	int8_t	(*write)(int8_t fd, void* buf, int16_t size);
	
} zNetDevice;


#endif // SOCKET_H
