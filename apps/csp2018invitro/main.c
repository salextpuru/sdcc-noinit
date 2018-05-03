#include <types.h>
#include <string.h>
#include <stdint.h>
#include <conio.h>
#include <spr0.h>
#include <im2.h>



#include "cspLogo.h"
#include "scrarea13.h"
#include "printscale.h"

static const char* issues[][4]={
	{"Приветствуем участников","CSP 2018","в городе","Новосибирске!"},
	{"Есть Бухло!","Возможны Женщины!","Назревают Танцы!","Поглощается Еда!"},
	{"И, конечно","ДЕМО! ДЕМО! ДЕМО!","и ещё раз", "--- ДЕМО ---"},
	{"Сегодня у нас в гостях!","Известные!","Не очень известные!","Вообще не известные!"},
	{"Спектрумисты!","Друзья Спектрумистов!","Подруги Спектрумистов!","Жены Спектрумистов!"},
	{NULL,NULL,NULL,NULL}
};

static uint16_t issuen=0;

static void printNextMsg() {
	uint8_t x;
	uint8_t i;
	uint8_t l;
	if ( !issues[issuen][0] ) {
		issuen=0;
	}

	for (i=1; i<=2; i++) {
		for(l=0; l<4; l++){
			x=(0x20-strlen(issues[issuen][l]) )>>1;
			printStrScale(x,l+l,i,issues[issuen][l]);
		}
		waitINTS(20);
	}
	waitINTS(100);
	clearTextArea(0,0104);

	issuen++;
}

void checkMusic();

int main() {
	ccls(0104);
	logoToScreen(3,9);
	SEI();
	
	while (1) {
		printNextMsg();
		checkMusic();
		//waitINTS(50);
	}
	//
	return 0;
}
