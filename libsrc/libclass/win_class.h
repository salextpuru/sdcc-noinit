/*----------------------------------------------------------------------------*/
/**
    @file win_class.h
    Класс-окно
*/
#ifndef win_class_h_E
#define win_class_h_E
/*----------------------------------------------------------------------------*/
#include <base_class.h>
#include <scrfunc.h>

/**
 * @brief Базовый класс-окно
 * 	Все, что он умеет делать - это рисовать окошко и
 * 	выводить в него курсор
 */
typedef struct {
	// -- Предок --
	tBaseClass	parent;
	
	// -- Виртуальные методы --
	void	(*Draw)(void* this);
	
	// -- Данные класса --
	
	// Размеры окна
	uint8_t	x;
	uint8_t	y;
	uint8_t	width;
	uint8_t	high;
	
	// Позиция курсора
	uint8_t	cx;
	uint8_t	cy;
	
	/**
	 * @brief цвет окна
	 */
	uint32_t	color;
	
	/**
	 * @brief цвет курсора
	 */
	uint32_t	ccolor;
	
	/**
	 * @brief тип курсора
	 */
	curTypes	ctype;
	
}tWinClass;

// Конструктор
void tWinClass_Init(tWinClass* this);

// Отрисовка класса (использует screen driver)
void tWinClass_Draw(void* this);
/*----------------------------------------------------------------------------*/
#endif /* win_class_h_E */
