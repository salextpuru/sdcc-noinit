// Библиотека управления перемещаемыми объектами
#include <so.h>
#include <testso.h>

// Это вспомогательная часть
#include <stdio.h>
#include <conio.h>
#include <zxkbd.h>
#include <im2.h>

// Адрес куда грузим библиотеку

// Первая
#define so_v1_load_addr		((void*)0x8000)

// Вторая
#define so_v2_load_addr		((void*)0x9000)

void findFunc(soHeader* soH, const char* name) {
	soFuncDsc*	sofunc = getSoFuncName(soH,name);
	
	printf("Func %s %s %.4X->%4X\n",
		name,
		sofunc?"y":"n",
		sofunc,
		sofunc?sofunc->jumadr:0
	);
}

void loadLib(soHeader* soH) {
	// Перемещение по заданному адресу
	// pend - первый свободный адрес за библиотекой
	void* pend = soReloc( soH );
	uint16_t	n=0;
	shared_link* respart;
	soFuncDsc*	sofunc;
	
	
	printf("Load [%s]: %.4X - %4X\n", soH->name, soH, pend );
	
	// Настройка резидентной части
	if( respart = tune_shared_obj( soH ) ){
		printf("Res [%s] tuned at %.4X\n",respart->name, respart);
	}
	else {
		printf("[%s] not find res\n",soH->name);
	}
	
	printf("functions: %u\n\n",soH->nfunc);
	
	while( sofunc=getSoFuncDsc(soH, n++) ){
		printf("f[%i]: %s at 0x%.4X\n", n, sofunc->name, sofunc->jumadr);
	}
	
	printf("\n\n");
	
	findFunc(soH, "aaa");
	findFunc(soH, "tsInit");
	findFunc(soH, "tsShowInfo");
}

void press_a_key(){
	printf("\nPress a key\n");
	while(!zxKbdInKey()){}
}

void main(){
	// Инициализация клавиатуры
	CLI();
	im2SetHandler(zxKbdScan);
	im2Set();
	SEI();
	ccls(006);
	
	// Инициализируем первую библиотеку
	loadLib(so_v1_load_addr);
	press_a_key();
	
	// Запускаем её
	// Работаем как с обычными функциями
	tsInit();
	tsShowInfo();
	press_a_key();
	
	// Инициализируем вторую библиотеку
	ccls(006);
	loadLib(so_v2_load_addr);
	press_a_key();
	
	// Запускаем её
	// Работаем как с обычными функциями
	tsInit();
	tsShowInfo();
	
	
	
	while(1){}
}
