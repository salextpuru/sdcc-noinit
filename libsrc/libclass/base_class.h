/**
    @file base_class.h
    Базовое управление классами
*/
#ifndef base_class_h_E
#define base_class_h_E

#include <stdint.h>
/*----------------------------------------------------------------------------*/

// Получить ClassId по адресу Конструктора
#define getClassId( constructor )	((uint16_t)(&constructor))

/**
 * @brief Базовый класс.
 */
typedef struct {
	/**
	 * @brief Уникальный ID класса
	 * 	В классе всегда есть Конструктор
	 * 	и всегда должен зполнять данное поле
	 */
	uint16_t	classid;
	
}tBaseClass;
 
/**
 * @brief Конструктор
 * 
 * @param this p_this - указатель на конструируемый объект
 */
void tBaseClass_Init(tBaseClass*this);
/*----------------------------------------------------------------------------*/
#endif /* base_class_h_E */
