/**
    @file scrfunc.c
    Функции для вывода на экран
*/
#include <scrfunc.h>

scrDriverFunc*	txt_screen_driver;

uint8_t*	current_font = (uint8_t*)0x3C00;

box_symbols	boxSingle;
box_symbols	boxDouble;

void borderUI(uint8_t btype, uint8_t x, uint8_t y, uint8_t w, uint8_t h){
	box_symbols bs;
	uint8_t	i;
	switch( btype ){
		case btNone:{
			bs=0;
			break;
		}
		case btSingl:{
			bs=boxSingle;
			break;
		}
		case btDoubl:{
			bs=boxDouble;
			break;
		}
		default:
			bs=0;
	}
	
	if(!bs){
		return;
	}
	
	
	for(i=1; i<(w-1); i++){
		txt_screen_driver->curpos( x+i,y );
		txt_screen_driver->putc(bs[0]);
		txt_screen_driver->curpos( x+i,y+h-1 );
		txt_screen_driver->putc(bs[0]);
	}
	
	for(i=1; i<(h-1); i++){
		txt_screen_driver->curpos( x,y+i );
		txt_screen_driver->putc(bs[1]);
		txt_screen_driver->curpos( x+w-1, y+i );
		txt_screen_driver->putc(bs[1]);
	}
	
	txt_screen_driver->curpos( x,y );	txt_screen_driver->putc(bs[2]);
	txt_screen_driver->curpos( x+w-1,y );	txt_screen_driver->putc(bs[3]);
	txt_screen_driver->curpos( x,y+h-1 );	txt_screen_driver->putc(bs[4]);
	txt_screen_driver->curpos( x+w-1,y+h-1 ); txt_screen_driver->putc(bs[5]);
}
