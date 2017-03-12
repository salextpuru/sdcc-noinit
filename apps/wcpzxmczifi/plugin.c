#include <string.h>
#include <wcplugin.h>
#include <stdio.h>
#include <stdlib.h>
#include <zxmc_uart.h>
#include <zifi_uart.h>

#define closew() wcRRESB(&w);

/**
 * @brief Окно
 */
static wcWindow w={
	.winType = 0,
	.curColorMask=0x00,
	.winX=4, .winY=4, .winWidth=60, .winHeigh=18,
	.winColor= wcColorCode(wcLightGreen, wcBlue)
};

// UART drivers
static zxuart*		uart_zxmc;
static zxuart*		uart_zifi;

static void esc_wait(){
	while(!wcKeyFunc(wcESC)){}
}

//
static const char* tHeader="[ ZXMC UART control to internal ZiFi ]";
static const char* bHeader=" ";
//
static void draw_headers(){
	wcPrint(&w, tHeader, 4, 0, wcColorCode(wcLightYellow, wcBlue) );
	wcPrint(&w, bHeader, 4, w.winHeigh-1, wcColorCode(wcLightYellow, wcBlue) );
}

static void clw(){
	wcPRWOW(&w);
	draw_headers();
}

static uint8_t init_uarts(){
	//
	uart_zifi = zifi_uart();
	uart_zxmc = zxmc_uart();
	
	if( uart_zifi->init() ){
		wcPrint(&w, "ZiFi uart not found!", 2, 2, wcColorCode(wcLightRed, wcBlue) );
		return 1;
	}
	
	if( uart_zxmc->init() ){
		wcPrint(&w, "ZXMC uart not found!", 2, 2, wcColorCode(wcLightRed, wcBlue) );
		return 2;
	}
	
	bHeader = "ZXMC and ZiFi uart foud. Running.";
	draw_headers();
	return(0);
}

#define bSizes		0x800

static uint8_t	zifi_rdbuf[bSizes];
static uint16_t	zifi_rdbuf_b=0;
static uint16_t	zifi_rdbuf_e=0;

static uint8_t	zxmc_rdbuf[bSizes];
static uint16_t	zxmc_rdbuf_b=0;
static uint16_t	zxmc_rdbuf_e=0;

static uint16_t bModify(uint16_t* p){
	uint16_t r=*p;
	(*p)++;
	if( (*p) >=bSizes ){
		*p = 0;
	}
	return(r);
}

static void transferLoop(){
	uint8_t exit=0;
	
	while(!exit){
		uint8_t c;
		exit=1;
		//
		while( uart_zxmc->read(&c,1) ){
			switch (c){
				case '\n':
				case '\r':{
					zxmc_rdbuf[bModify(&zxmc_rdbuf_e)]='\r';
					zxmc_rdbuf[bModify(&zxmc_rdbuf_e)]='\n';
					break;
				}
				default:
					zxmc_rdbuf[bModify(&zxmc_rdbuf_e)]=c;
					break;
			}
			
			//
			exit=0;
		}
		//
		if( zxmc_rdbuf_b != zxmc_rdbuf_e ){
			if( uart_zifi->write(zxmc_rdbuf+zxmc_rdbuf_b,1) ){
				bModify(&zxmc_rdbuf_b);
				exit=0;
			}
		}
		
		//
		while( uart_zifi->read(&c,1) ){
			zifi_rdbuf[bModify(&zifi_rdbuf_e)]=c;
			exit=0;
		}
		//
		if( zifi_rdbuf_b != zifi_rdbuf_e ){
			if( uart_zxmc->write(&zifi_rdbuf+zifi_rdbuf_b,1) ){
				bModify(&zifi_rdbuf_b);
				exit=0;
			}
		}
	}
}

static void mainLoop(){
	
	uint16_t oldt=wcGetTimer();
	
	
	while(1){
		// Опрос клавиатуры
		if(oldt != wcGetTimer()){
			oldt=wcGetTimer();
			// ESC - выход
			if( wcKeyFunc(wcESC) ){
				break;
			}
		}
		
		// Передача данных туда и сюда
		transferLoop();
	}
	
}

void main(){
	wcINTPL(wcTIME_DISABLE,0);
	clw();
	// Инициализаця
	if( init_uarts() ){
		bHeader = "Press ESC to exit.";
		draw_headers();
		esc_wait();
		closew();
		return;
	}
	//
	clw();
	wcPrint(&w, "This programm lets control internal ZiFi board.",2,2, wcColorCode(wcLightYellow, wcBlue) );
	wcPrint(&w, "Connect you PC with ZXMC uart and control ZiFi board.",2,4, wcColorCode(wcLightYellow, wcBlue) );
	wcPrint(&w, "Speed 115200 only.",2,6, wcColorCode(wcLightYellow, wcBlue) );
	
	//
	mainLoop();
	// Exit
	closew();
}


