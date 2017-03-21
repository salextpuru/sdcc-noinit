#ifndef FILE_H
#define FILE_H

#include <time.h>
#include <device.h>
#include <stdarg.h>

// Максимальное количество точек монтирования
#define MPOINTS_MAX	0x08

// Максимальное число открытых файлов
#define FILES_MAX	0x10

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
struct zFileSystem;
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
	 * @brief Длина пути
	 */
	uint16_t	mpathlen;
	
	/**
	 * @brief Файловая система
	 */
	struct zFileSystem*	fs;
	
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
	int16_t		d_off;	/* смещение (номер записи в каталоге) */
	uint16_t	d_reclen; /* Длина записи в каталоге */
	//
	zDirent		dirent;	/* Запись в каталоге */
} zDir;

typedef struct zFile {
	zMpoint*	mpoint;	// Точка монтирования
	//
	int16_t		f_type;	 // тип файла
	uint16_t	f_mode;	 // права доступа
	int16_t		f_flags; // флаги
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
	 * @brief Счетчик ссылок
	 */
	int16_t lcounter;
	
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
	zDirent* (*readdir)(struct zFileSystem* fs, zDir *dirp);
	
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
	zFile* (*open)(struct zFile* fs, const char* path, uint16_t flags, va_list mode);
	
	/**
	 * @brief Закрыть файл
	 */
	int (*close)(zFile* f );
	
	/**
	 * @brief Прочитать данные из заданного файла
	 */
	int16_t	(*read)(struct zFileSystem* fs, zFile* f,  void* buf, int16_t size);
	
	/**
	 * @brief Записать данные в заданный файл
	 */
	int16_t	(*write)(struct zFileSystem* fs, zFile* f, void* buf, int16_t size);
	
	/**
	 * @brief Получить информацию о файле
	 */
	int (*stat)(struct zFileSystem* fs, const char *pathname, zFile* stat);
	
} zFileSystem;

extern zMpoint	kmpoints[];

/**
 * @brief Поиск точки монтирования по полному пути
 * 
 * @param fullpath - полный путь
 * @return zMpoint*
 */
zMpoint* kgetmpoint(const char* fullpath);

/**
 * @brief Получить текущий каталог
 * 
 * @param buf - буфер
 * @param size - размер
 * @return char* - имя каталога или NULL, если буфер слишком мал.
 */
char *getcwd(char *buf, uint16_t size);

/**
 * @brief Установить текущий каталог
 * 
 * @param path - путь
 * @return int - 0, все хорошо, -1 - все плохо
 */
int8_t chdir(const char *path);

/**
 * @brief Открыть каталог
 * 
 * @param path - путь к каталогу
 * @param dir - данные для работы с каталогом
 * @return zDir*
 */
zDir*	opendir(const char *path, zDir* dir);

/**
 * @brief Закрыть каталог
 * 
 * @param dirp - каталог
 * @return int
 */
int closedir(zDir *dirp);

/**
* @brief Считать очередную запись каталога, открытого opendir
* 	return NULL - конец каталога или ошибка
*/
zDirent* readdir(zDir *dirp);

/**
 * @brief Открыть файл
 * 	path - путь к файлу
 * 	flags - флаги
 */
int16_t open(const char* path, uint16_t flags, ...);
	
/**
 * @brief Закрыть файл
 */
int16_t close(uint16_t fd);
	
/**
 * @brief Прочитать данные из заданного файла
 */
// int16_t	read(uint16_t fd, zFile* f,  void* buf, int16_t size);
	
/**
 * @brief Записать данные в заданный файл
 */
// int16_t	write(int16_t fd, void* buf, int16_t size);
	
/**
 * @brief Получить информацию о файле
 */
// int16_t stat(const char *pathname, zFile* stat);

#endif // FILE_H
