#ifndef FILE_H
#define FILE_H

#include <time.h>
#include <device.h>

// Максимальное количество точек монтирования
#define MPOINTS_MAX	0x08

// Типы драйверов устройств
#define	DRV_VFS		0x00	/* устройство виртуальная файловая система */
//
#define	DRV_ZSPI	0x10
#define	DRV_NGSSPI	0x11
//
#define	DRV_NEMOIDE	0x12
#define	DRV_ES8266	0x20

// Типы файловых систем
#define FS_ROOT		0x00
#define FS_DEV		0x01
#define FS_VFAT		0x10

// Флаги монтирования
#define MFL_MOUNTED	0x01
#define MFL_RW		0x02

/**
 * @brief Описание точки монтирования
 */
typedef struct zMpoint {
	/**
	 * @brief Ссылка на драйвер устройства
	 */
	zDevice*	dev;
	
	/**
	 * @brief Номер устройства
	 */
	int16_t		minor;
	
	/**
	 * @brief Полный путь к точке монтирования
	 */
	const char*	mpath;
	
	/**
	 * @brief Тип файловой системы
	 */
	int16_t		fstype;
	
	/**
	 * @brief Флаги монтирования
	 */
	int16_t		flags;
} zMpoint;


/**
 * @brief Описатель элемента каталога
 */
typedef struct zDirent {
	int16_t	d_type;		/* тип файла*/
	int16_t	d_mode;		/* режим доступа к файлу */
	char	d_name[0x100];	/* имя файла */
} zDirent;

/**
 * @brief Описатель каталога
 */
typedef struct zDir {
	zMpoint*	mpoint;	/* Точка монтирования */
	//
	uint32_t	d_ino;	/* узел начала каталога */
	int32_t		d_off;	/* смещение (номер записи в каталоге) */
	uint16_t	d_reclen; /* Длина записи в каталоге */
	//
	zDirent		dirent;	/* Запись в каталоге */
} zDir;

typedef struct zFile {
	zMpoint*	mpoint;	// Точка монтирования
	//
	int16_t		f_type;	// тип файла
	uint16_t	f_mode;	// права доступа
	//
	uint32_t	f_size;	// полный размер в байтах
	uint32_t	f_pos;	// позиция указателя в файле
	//
	uint32_t	f_ino;	// узел начала файла
	uint32_t	f_blocks; // кол-во выделенных блоков по 512Б
	//
        zDevice*	f_device; // устройство (если это спец. файл)
        //
	time_t	st_atim;  /* время последнего доступа */
	time_t	st_mtim;  /* время последнего изменения */
	time_t	st_ctim;  /* время последней смены состояния */
} zFile;

/**
 * @brief Описание файловой системы
 */
typedef struct zFileSystem {
	/**
	 * @brief Тип файловой системы
	 */
	int16_t		fstype;
	
	/**
	 * @brief Точка монтирования
	 */
	zMpoint*	mpoint;
	
	/**
	 * @brief Монтирует файловую систему.
	 */
	int16_t	(*mount)(struct zFileSystem* fs, int16_t flags);
	
	/**
	 * @brief Размонтирует файловую систему.
	 */
	int16_t	(*umount)(struct zFileSystem* fs, int16_t flags);
	
	/**
	 * @brief Открыть каталог файловой системы
	 * 	return NULL - ошибка.
	 */
	zDir*	(*opendir)(struct zFileSystem* fs, const char *name, zDir* dir);
	
	/**
	 * @brief Считать очередную запись каталога, открытого opendir
	 * 	return NULL - конец каталога или ошибка
	 */
	zDirent* (*readdir)(struct zFileSystem* fs, zDir *dirp, zDirent *entry);
	
	/**
	 * @brief Удалить каталог
	 * 	path - Полный путь к каталогу
	 */
	int (*rmdir)(struct zFileSystem* fs, const char *path);
	
	/**
	 * @brief Создать каталог
	 * 	path - Полный путь к каталогу
	 */
	int (*mkdir)(struct zFileSystem* fs, const char *path, uint16_t mode);
	
	/**
	 * @brief Удалить файл
	 * 	path - Полный путь к файлу
	 */
	int (*unlink)(struct zFileSystem* fs, const char *path);
	
	/**
	 * @brief Закрыть каталог
	 */
	int (*closedir)(struct zFileSystem* fs, zDir *dirp);
	
	/**
	 * @brief Открыть файл
	 * 	path - Полный путь к файлу
	 */
	zFile* (*open)(struct zFileSystem* fs, const char* path);
	
	/**
	 * @brief Закрыть файл
	 */
	int (*close)(struct zFileSystem* fs, zFile* f );
	
	/**
	 * @brief Прочитать данные из заданного файла
	 */
	int16_t	(*read)(struct zFileSystem* fs, zFile* f,  void* buf, int16_t size);
	
	/**
	 * @brief Записать данные в заданный файл
	 */
	int16_t	(*write)(struct zFileSystem* fs, zFile* f, int16_t fd, void* buf, int16_t size);
	
	/**
	 * @brief Получить информацию о файле
	 */
	int (*stat)(struct zFileSystem* fs, const char *pathname, zFile* stat);
	
} zFileSystem;

#endif // FILE_H
