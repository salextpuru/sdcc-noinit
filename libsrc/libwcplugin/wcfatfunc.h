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
void wcADIR(uint8_t mode);



#endif // WCFATFUNC_H
