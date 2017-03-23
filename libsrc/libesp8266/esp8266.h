#ifndef LIBESP8266_H
#define LIBESP8266_H

#include <ipconnector.h>

/**
 * @brief Флаги конфигурации интерфейса esp8266
 */
enum esp8266flags{
	// Транспорт ZIFI-UART
	esp8266ZIFI = 0x00,
	// Транспорт ZXMC-UART
	esp8266ZXMC = 0x01
};

/**
 * @brief Авторизация для подключения к точке доступа (ifdata)
 */
typedef struct esp8266auth{
	const char* user;
	const char* passwd;
}esp8266auth;

extern tIFNET IFNET_ESP8266;

#endif // LIBESP8266_H
