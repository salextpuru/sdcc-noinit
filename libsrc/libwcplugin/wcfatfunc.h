#ifndef WCFATFUNC_H
#define WCFATFUNC_H

// 48	LOAD512
// i:	buf	- buffer for loading data
//	sectors	- sectors (512 bytes per sector)
// o:	next position in buffer
//	on NULL if EOF detected
void* wcLOAD512(void* buf, uint8_t sectors);

// 49	SAVE512
// i:	buf	- buffer for saving data
//	sectors	- sectors (512 bytes per sector)
// o:	next position in buffer
//	on NULL if EOF detected
void* wcSAVE512(void* buf, uint8_t sectors);

// 50	GIPAGPL позиционировать на начало файла переданного плагину
//	при запуске по расширению
//	(сразу после запуска плагина оная уже вызвана)
//	совместно со STREAM(57) можно работать только, если
//	клонировали поток, а не создавали таковой!!!
void wcGIPAGPL();

// 51	TENTRY	получить ENTRY(32) из коммандера
//	(структура как в каталоге FAT32)
//	i:  tentry - address of output buffer
//	o:	entry in buffer (32 bytes)
void wcTENTRY(void* tentry);

// 56	ADIR функции для работы с активным каталогом
//	i: mode #00 - спозиционировать на начало активного каталога (как на файл)
//	   mode #01 - сброс счётчиков для FindNext (вызывает GDIR, указатель становится на активном каталоге)
#define wcAdirGoToActiveDir	0x00
#define wcAdirResetFindNext	0x01
void wcADIR(uint8_t mode);

// 57	STREAM	работа с потоками
//	mode:
//		#FF: сделать активным root dir (более никаких параметров не учитывает)
//		#FE: клонировать активный поток в потоки #00 и #01.
//		     В момент запуска плагина активен поток из панели.
//		     Автоматически делается активным поток #00(никаких других параметров не учитывает)
//		#00/#01: номер потока, требует BC.
//	
//	part:
//		раздел (пока не учитывается)
//	
//	dev: 
//		0-SD(ZC)
//		1-NemoMaster
//		2-NemoSlave
//		4-SmucMaster
//		5-SmucSlave
//		0xFF - включает поток из mode (код возврата не учитывается)
//		0xFE - создает/пересоздает поток
//
//	return:	0  - 0k
//		FF - Error
//
#define	wcSTRMOD_00		0x00
#define	wcSTRMOD_01		0x01
#define	wcSTRMOD_CLONEACTIVE	0xFE
#define	wcSTRMOD_ACTIVEROOT	0xFF
//
#define	wcSTRDEV_SDZC	0x00
#define	wcSTRDEV_NEMOM	0x01
#define	wcSTRDEV_NEMOS	0x02
#define	wcSTRDEV_SMUCM	0x04
#define	wcSTRDEV_SMUCS	0x05
#define wcSTRDEV_CREATE	0xFE
#define wcSTRDEV_INCMOD	0xFF
uint8_t wcSTREAM(uint8_t mode, uint8_t part, uint8_t dev);

// File/Dir entry descriptor
typedef struct {
	uint32_t	size;
	uint16_t	date;
	uint16_t	time;
	uint8_t		flag;
	char		name[0];
} wcENTRY;

// 58	FindNext
//	return:
//		FF - end of directory, entry not found
//		00 - entry found, it can find next

// Mode defines:
#define		wcFindNextEntry		0x00
#define		wcFindNextFile		0x01
#define		wcFindNextDir		0x02
// Example:
//		uint8_t		buf[0x100+0x09];	// - Buffer (Maximum size)
//		wcENTRY*	entry=(void*)buf;	// - entry
//		// Find all file and dirs in current directory
//		while( !wcFINDNEXT(entry, wcFindNextEntry) ){
//			...... Enrty FOUND! DO SOMETHING
//			entry->size; entry->date;
//			entry->time; entry->flag; // (& 0x10=dir, else =file)
//			entry->name; // Maximum size depend from buffer size
//		}
//
//
uint8_t wcFINDNEXT(void* wcentry, uint8_t mode);

// 59	FENTRY
// i:
//	wcentry - pointer to wcENTRY
//	wcentry->flag = 0x00 for file
//	wcentry->flag = 0x10 for directory
//	wcentry->name - name or path
// o:
//	return 0	if file/dir found
//	return FF	if file/dir NOT found
//	if found, wcentry->size = size of found file
#define wcFENTRY_FILE		0x00
#define wcFENTRY_DIR		0x10
uint8_t wcFENTRY(void* wcentry);

#endif // WCFATFUNC_H
