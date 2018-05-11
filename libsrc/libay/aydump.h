/**
    @file aydump.h - Получить значение регистров муз. сопроцессора.
*/
#ifndef aydump_h_E
#define aydump_h_E
#include <stdint.h>

/**
* @brief Количество считываемых регистров AY8910/12
*/
#define AY_READING_REGS	0x10

/**
* @brief Значения регистров AY8910/12
*/
extern const uint8_t ayDump[];

/**
* @brief Получить значения регистров AY8910/12
* 	и поместить их в массив ayDump[]
*/
void ayDumpGet();

#endif /* aydump_h_E */
