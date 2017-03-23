#ifndef IPCONNECTOR_H
#define IPCONNECTOR_H

#include <stdint.h>

/**
 * @brief Сетевые протоколы
 */
enum tNetProtocols{
	protTCP = 0,
	protUDP = 1
};


/**
 * @brief Типы интерфейсов
 */
enum ifTypes{
	ifWIFICL 	= 0,	// WiFi-клиент
	ifWIFIAP 	= 1,	// WiFi-точка доступа
	ifWIFIAPCL	= 2	// WiFi-точка доступа и клиент
};

/**
 * @brief Описатель интерфейса
 */
typedef struct tIFNET {
	
	/**
	 * @brief Уникальный идентификатор интерфейса
	 */
	uint16_t	id;
	
	/**
	 * @brief Тип интерфейса
	 */
	uint8_t		type;
	 
	/**
	 * @brief  Флаги (зависят от типа интерфейса)
	 */
	uint8_t		flags;
	
	/**
	 * @brief Адрес интерфейса
	 */
	uint32_t	ip;
	
	/**
	 * @brief  Включить интерфейс
	 * 
	 * @param eth - указатель на описатель интерфейса
	 * @param ip - адрес IP (0.0.0.0 = DHCP)
	 * @param type - тип интерфейса (ifTypes)
	 * @param flags - флаги (зависят от типа интерфейса)
	 * @param ifdata - данные, зависящие от типа интерфейса (например имя и пароль)
	 * 
	 * @return int8_t - 0-ok или код ошибки
	 */
	int8_t (*up)(struct tIFNET* eth, uint32_t ip, uint8_t type, uint8_t flags, void* ifdata);
	
	/**
	 * @brief Выключить интерфейс
	 * @param eth - указатель на описатель интерфейса
	 * @param flags - флаги
	 * @return int8_t - 0-ok или код ошибки
	 */
	int8_t (*down)(struct tIFNET* eth, uint16_t flags);
	
	/**
	 * @brief  Соединиться
	 * 
	 * @param eth - указатель на описатель интерфейса
	 * @param ip - адрес IP
	 * @param port - порт
	 * @param protocol - протокол
	 * @return int8_t - -1 - ошибка, 0..127-номер соединения
	 */
	int8_t (*connect)(struct tIFNET* eth, uint32_t ip, uint16_t port, uint16_t protocol);
	
	/**
	 * @brief Закрыть соединение номер fd
	 */
	int8_t (*close)(struct tIFNET* eth, uint8_t fd );
	
	/**
	 * @brief Чтение данных из соединения номер fd
	 * 	Считывает не более size байт данных
	 * 	и помещает их в буффер buf.
	 * 
	 * @return
	 * 	Количество реально считанных байт данных.
	 * 	0 - данных не считано вообще, ждите.
	 * 	-1 - ошибка
	 */
	int16_t (*read)(struct tIFNET* eth, uint8_t fd, void* buf, uint16_t size);
	
	/**
	 * @brief Запись данных в соединение номер fd
	 * 	Записывает не более size байт данных из
	 * 	буфера buf.
	 * 
	 * @return
	 * 	Количество реально записанных байт данных.
	 * 	0 - данных не записано вообще, ждите.
	 * 	-1 - ошибка
	 */
	int16_t (*write)(struct tIFNET* eth, uint8_t fd, void* buf, uint16_t size);
	
	/**
	 * @brief Открыть на прослушивание порт port
	 * 
	 * @return int8_t - -1 - ошибка, 0..127-номер соединения
	 */
	int8_t (*listen)(struct tIFNET* eth, uint8_t port);
	
	/**
	 * @brief Функция опроса интерфейса. 
	 * 	Вызывается периодически для вычитывания данных, если пришли.
	 */
	void (*poll)(struct tIFNET* eth);
} tIFNET;

#endif // IPCONNECTOR_H
