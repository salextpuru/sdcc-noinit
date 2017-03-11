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
	.winX=0, .winY=0, .winWidth=0, .winHeigh=0,
	.winColor= wcColorCode(wcGreen, wcBlue)
};

static zxuart*		uart;
static uint8_t cx;
static uint8_t cy;

static void esc_wait(){
	while(!wcKeyFunc(wcESC)){}
}

static char tHeader[0x128]="[ Terminal test plugin by SfS ]";
static char bHeader[0x128]="Status:";
static void draw_headers(){
	wcPrint(&w, tHeader, 4, 0, wcColorCode(wcLightYellow, wcBlue) );
	wcPrint(&w, bHeader, 4, w.winHeigh-1, wcColorCode(wcLightYellow, wcBlue) );
}

static void clw(){
	cx=cy=1;
	wcPRWOW(&w);
	draw_headers();
}

static uint8_t uart_select_menu(uint8_t x, uint8_t y){
	uint8_t r=0xFF;
	
	wcPrint(&w, "Select UART type:", x, y, wcColorCode(wcLightYellow, wcBlue) );
	wcPrint(&w, "1. ZXMC", x+4, y+2, wcColorCode(wcLightYellow, wcBlue) );
	wcPrint(&w, "2. ZiFi", x+4, y+3, wcColorCode(wcLightYellow, wcBlue) );
	
	while(1){
		wcWaitForFrame();
		if(wcKeyFunc(wcESC)){
			r=0xFF;
			break;
		}
		else{
			unsigned char c=wcKbScan(wcKeyTableC);
			if( ( c>='1' ) && (c<='2') ){
				r=c-'1';
				break;
			}
		}
	}
	
	return(r);
}

static void tnewline(uint8_t hidec){
	if(hidec){
		wcPRSRW(&w, " ", cx, cy, 1, wcColorCode(wcLightYellow, wcBlue) );
	}
	cx=1;
	cy++;
	if(cy>(w.winHeigh-2)){
		cy--;
		wcSCRLWOW(&w, wcSCRL_UP | wcSCRL_STEP(1) | wcSCRL_ATTRS | wcSCRL_CLEAR,
			  1, 1, w.winWidth-2, w.winHeigh-2);
	}
	// Cursor
	wcPRSRW(&w, " ", cx, cy, 1, wcColorCode(wcLightYellow, wcGreen) );
}

static void tputc(char c){
	wcPRSRW(&w, &c, cx, cy, 1, wcColorCode(wcLightYellow, wcBlue) );
	cx++;
	if(cx>(w.winWidth-2)){
		tnewline(0);
	}
	else{
		// Cursor
		wcPRSRW(&w, " ", cx, cy, 1, wcColorCode(wcLightYellow, wcGreen) );
	}
}

static void mainLoop(){
	uint16_t oldt=wcGetTimer();
	uint16_t pb=0;
	uint16_t pe=0;
	static uint8_t buf[0x1000];
	
	while(1){
		uint8_t  r;
		uint16_t rdsz;
		// Опрос клавиатуры
		if(oldt != wcGetTimer()){
			uint8_t  c;
			oldt=wcGetTimer();
			// ESC - выход
			if( wcKeyFunc(wcESC) ){
				break;
			}
			else if( wcKeyFunc(wcENTER) ){
				uart->write(&"\r\n", 2);
			}
			else if( c=wcKbScan(wcKeyTableALL) ){
				uart->write(&c, sizeof(c));
			}
		}
		
		rdsz=1;
		while( r = uart->read(buf+pe, rdsz) ){
			pe+=r;
			if(pe>=sizeof(buf)){
				pe=0;
			}
			if( ( rdsz = sizeof(buf) - pe ) > 0xFF ){
				rdsz=0xFF;
			}
		}
		
		// Вывод на экран принятого.
		if( pb!=pe ){
			uint8_t  c=buf[pb++];
			if(pb>=sizeof(buf)){
				pb=0;
			}
			//
			if(c>=0x20){
				tputc(c);
			}
			else switch(c){
				// next line
				case '\r':{
					tnewline(1);
					break;
				}
				case '\n':{
					// tnewline(1);
					break;
				}
				default:
					break;
			}
		}
	}
}

void main(){
	wcINTPL(wcTIME_DISABLE,0);
	clw();
	//
	*bHeader=0;
	switch( uart_select_menu(5,5) ){
		case 0:{
			strcat(bHeader, "Status: ZXMC ");
			uart=zxmc_uart();
			break;
		}
		case 1:{
			strcat(bHeader, "Status: ZiFi ");
			uart=zifi_uart();
			break;
		}
		default:
			closew();
			return;
	}
	clw();
	//
	if(uart->init()){
		wcPrint(&w, "UART NOT FOUND!", 10, 10, wcColorCode(wcLightRed, wcGray) );
		wcPrint(&w, "Press ESC for exit...", 10, 12, wcColorCode(wcWhite, wcBlue) );
		esc_wait();
		closew();
		return;
	}
	clw();
	mainLoop();
	// Exit
	closew();
}


