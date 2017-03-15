#ifndef DEVICE_H
#define DEVICE_H

#include <stdint.h>

// Типы драйверов устройств
#define	DRV_VFS		0x00	/* устройство виртуальная файловая система */
//
#define	DRV_ZSPI	0x10
#define	DRV_NGSSPI	0x11
#define	DRV_NEMOIDE	0x12
#define	DRV_SMUCIDE	0x12
//
#define	DRV_TTYZXMC	0x20
#define	DRV_TTYZIFI	0x21

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
	 * @brief Номер устройства
	 */
	int16_t	minor;
	
	/**
	 * @brief Имя устройства
	 */
	const	char*	devname;
	
	/**
	 * @brief Счетчик ссылок
	 */
	int16_t lcounter;
	
	// -------- регистрация-удаление --------
	
	/**
	 * @brief Инициализация устройства.
	 * 	Вызывается при регистрации.
	 * 
	 * 	Если возвращает 0, все ок.
	 * 	Иначе - код ошибки < 0, устройство не регистрируется
	 */
	int16_t	(*init)(struct zDevice* dev);
	
	/**
	 * @brief Выключить устройство.
	 * 	Вызывается при удалении устройства.
	 * 
	 * 	Если возвращает 0, все ок.
	 * 	Иначе - код ошибки < 0, устройство не удаляется
	 */
	int16_t	(*release)(struct zDevice* dev);
	
	// -------- файловые операции --------
	
	/**
	 * @brief Открыть
	 */
	int16_t	(*open)(struct zDevice* dev);
	
	/**
	 * @brief Закрыть
	 */
	int16_t	(*close)(struct zDevice* dev);
	
	/**
	 * @brief Прочитать данные из заданного файла-устройства
	 */
	int16_t	(*read)(struct zDevice* dev,  void* buf, int16_t size);
	
	/**
	 * @brief Записать данные в заданный файл-устройство
	 */
	int16_t	(*write)(struct zDevice* dev, int16_t fd, void* buf, int16_t size);
	
	// -------- системные операции --------
	
	/**
	 * @brief Опросить устройство, вычитать буфера, записать буфера
	 * 
	 * 	Возвращает состояние >=0 (см. devpstat)
	 * 	или код ошибки < 0
	 * 
	 */
	int16_t	(*poll)(struct zDevice* dev);
	
	/**
	 * @brief Управление устройством (все, что не вписывается в файловые операции)
	 * 	Возвращаемое значение зависит от запроса rq
	 */
	int16_t	(*ioctl)(struct zDevice* dev, int16_t rq, ... );
	
} zDevice;

#endif // DEVICE_H
