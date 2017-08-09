// LODE RUNNER SCENE COMPRESSOR
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

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

// Счетчик (0-несчитаемый символ)
static uint16_t counter;

// Символ, который считаем
static uint8_t c_c;

// Вывод в stdout
static void emit(uint8_t c){
	static int count=0;
	
	if(count == 0){
		printf("\t\t");
	}
	
	count+=printf("0x%.2X,",c);
	
	if(count>=48){
		printf("\n");
		count=0;
	}
	else{
		printf(" ");
	}
}

// Завершить подсчет
static void complete(){
	if(counter){
		emit(counter);
	}
	counter=0;
}

int main(int argc, const char* argv[]){
	uint8_t c;
	
	while( read(0,&c,1)>0 ){
		switch(c){
			// Неподсчитываемые символы
			case 'D':
			case 'M':
			case 'T':
			case 'L':{
				complete();
				emit(c);
				c_c=c;
				break;
			}
			
			// Подсчитываемые символы
			case 'b':
			case 'B':
			case 'U':
			case ' ':{
				if( (c != c_c) || (counter == 0xFF) ) {
					c_c=c;
					complete();
					emit(c);
				}
				
				counter++;
				break;
			}
			default:;
		}
	}
	
	complete();
	
	return 0;
}
