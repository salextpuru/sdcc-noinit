#ifndef DEVICE_H
#define DEVICE_H

#include <stdint.h>

/**
 * @brief Состояния устройства (poll)
 */

// Есть данные в для считывания
#define devpstatRdData		1

// Запись в устройство невозможна
#define devpstatWrDenided	2

/**
 * @brief Описатель устройства.
 */
typedef struct zDevice{
	/**
	 * @brief ID драйвера
	 */
	int16_t	major;
	
	/**
	 * @brief Счетчик ссылок
	 */
	int16_t f_counter;
	
	// -------- регистрация-удаление --------
	
	/**
	 * @brief Инициализация устройства.
	 * 	Вызывается при регистрации.
	 * 
	 * 	Если возвращает 0, все ок.
	 * 	Иначе - код ошибки < 0, устройство не регистрируется
	 */
	int16_t	(*init)(struct zDevice* dev, int16_t minor);
	
	/**
	 * @brief Выключить устройство.
	 * 	Вызывается при удалении устройства.
	 * 
	 * 	Если возвращает 0, все ок.
	 * 	Иначе - код ошибки < 0, устройство не удаляется
	 */
	int16_t	(*release)(struct zDevice* dev, int16_t minor);
	
	// -------- файловые операции --------
	
	/**
	 * @brief Открыть
	 */
	int16_t	(*open)(struct zDevice* dev, int16_t minor);
	
	/**
	 * @brief Закрыть
	 */
	int16_t	(*close)(struct zDevice* dev, int16_t minor);
	
	/**
	 * @brief Прочитать данные из заданного файла-устройства
	 */
	int16_t	(*read)(struct zDevice* dev, int16_t minor,  void* buf, int16_t size);
	
	/**
	 * @brief Записать данные в заданный файл-устройство
	 */
	int16_t	(*write)(struct zDevice* dev, int16_t minor, int16_t fd, void* buf, int16_t size);
	
	// -------- системные операции --------
	
	/**
	 * @brief Опросить устройство, вычитать буфера, записать буфера
	 * 
	 * 	Возвращает состояние >=0 (см. devpstat)
	 * 	или код ошибки < 0
	 * 
	 */
	int16_t	(*poll)(struct zDevice* dev, int16_t minor);
	
	/**
	 * @brief Управление устройством (все, что не вписывается в файловые операции)
	 * 	Возвращаемое значение зависит от запроса rq
	 */
	int16_t	(*ioctl)(struct zDevice* dev, int16_t minor, int16_t rq, ... );
	
} zDevice;

#endif // DEVICE_H
