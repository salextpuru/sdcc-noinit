#include <types.h>
#include <string.h>
#include <stdint.h>
#include <spr0.h>
#include <im2.h>

#include "cspLogo.h"
#include "winprocs.h"
#include "printscale.h"
#include "spr2018.h"

static const char* issues[][4]={
	{"Welcome to","CSP 2018 party","in Novosibirsk","great siberian city!"},
	{"There is drinks!","Posiible will be womens!","Maybe dances!","Eating foods!"},
	{"Of course,","DEMO! ARTS! MUSICS! GAMES!","and","other ZX-Programms!"},
	/*
	{"Приветствуем участников","CSP 2018","в городе","Новосибирске!"},
	{"Есть Бухло!","Возможны Женщины!","Назревают Танцы!","Поглощается Еда!"},
	{"И, конечно","ДЕМО! ДЕМО! ДЕМО!","и ещё раз", "--- ДЕМО ---"},
	{"Сегодня у нас в гостях!","Известные!","Не очень известные!","Вообще не известные!"},
	{"Спектрумисты!","Друзья Спектрумистов!","Подруги Спектрумистов!","Жены Спектрумистов!"},
	*/
	{NULL,NULL,NULL,NULL}
};

static uint16_t issuen=0;

static void printNextMsg() {
	uint8_t x;
	uint8_t i;
	uint8_t l;
	
	winSetAtr(0,0,32,8, 0104, 0xFF );
	
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
	winSetAtr(0,0,32,8, 04, 0xFF );
	waitINTS(10);
	winSetAtr(0,0,32,8, 0101, 0xFF );
	waitINTS(10);
	winSetAtr(0,0,32,8, 01, 0xFF );
	waitINTS(10);
	winClearRnd(0,0,32,8);

	issuen++;
}

void checkMusic();

int main() {
	logoToScreen(3,9);
	SEI();
	
	winClear(0,0,32,8);
	
	spr0_out0_attr(&spr2018,0,16);
	
	while (1) {
		printNextMsg();
		checkMusic();
	}
	//
	return 0;
}
