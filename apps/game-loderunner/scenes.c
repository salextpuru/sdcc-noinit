
#include "scenes.h"

/**
 *	Карта кодируется символами:
 * 
 *	D - черт (devil) Не более 10 шт
 * 	M - человек (MAN)
 * 	T - сундук (treasure)
 * 	L - лестница
 * 
 * 	b - Кирпич неуничтожимый [count8]
 * 	B - Кирпич уничтожимый [count8]
 *	U - верхний поручень [count8]
 * 	' ' (пробел) - пустое место [count8]
 * 
 * 	count8 - после символа идет один байт-счетчик
 * 
 * 	Программа кодирует карту на основе текстового файла
 * 
 * 	остальные символы - не кодируются
*/

void scn_decomp(uint8_t* scnz, scrPlan scn ){
	uint8_t c;
	uint16_t i;
	uint8_t counter;
	uint8_t* ptr;
	
	ptr=(uint8_t*)scn;
	
	i=0;
	while(i<sizeof(scrPlan)){
		c=*(scnz++);
		switch(c){
			// Неподсчитываемые символы
			case 'D':
			case 'M':
			case 'T':
			case 'L':{
				*(ptr++)=c;
				i++;
				break;
			}
			
			// Подсчитываемые символы
			case 'b':
			case 'B':
			case 'U':
			case ' ':{
				counter=*(scnz++);
				while((i<sizeof(scrPlan)) && (counter!=0)){
					*(ptr++)=c;
					i++;
					counter--;
				}
				
				break;
			}
			default:;
		}
	}
	//
}