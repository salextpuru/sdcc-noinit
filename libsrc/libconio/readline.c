#include "readline.h"
#include <conio.h>
#include <ps2.h>

static int  pos;	// position in buffer
static int  csize;	// current buffer size

// coords
static 	BYTE x;
static 	BYTE y;

static char cursor[2];
static BYTE xc;
static BYTE yc;

#define MINSERT	0
#define MREPLACE 1

static BYTE mode;

#define INSERT_CURSOR	0x8C
#define REPLACE_CURSOR	0x8D

static void draw_cur(BYTE hide){
	if(!hide){
		xc= (x + pos)%SCR_TXT_W ;
		yc= y + (x + pos)/SCR_TXT_W ;
	}
	
	conio_at(xc,yc);
	
	conio_setopt_xor();
	print(cursor);
	conio_setopt_nop();
	
	y-=last_scroll;
	yc-=last_scroll;
}

static void setmode(BYTE m){
	draw_cur(1);
	
	if(m==MINSERT){
		mode=MINSERT;
		cursor[0]=INSERT_CURSOR;
	}
	else{
		mode=MREPLACE;
		cursor[0]=REPLACE_CURSOR;
	}
	cursor[1]=0;
	
	draw_cur(0);
}

int readline(char* buffer, int size){
	static char init_flag=0;
	
	BYTE fexit;
	
	// for ZERO
	size--;
	
	// check and init
	if(!init_flag){
		init_flag=1;
		InitPS2();
		cursor[0]=INSERT_CURSOR;
		cursor[1]=0;
	}
	
	x=cur_x;
	y=cur_y;
	
	// main loop
	fexit=0;
	pos=0;
	csize=0;
	//
	draw_cur(0);
	setmode(MINSERT);
	//
	// show cursor
	while(!fexit){
		WORD key;
		BYTE k;
		
		// end of buffer
		buffer[csize]=0;
		
		// Hide cursor
		draw_cur(1);
		
		// show string
		cur_x = x;
		cur_y = y;
		print(buffer);
		y-=last_scroll;
		yc-=last_scroll;
		print(" ");
		y-=last_scroll;
		yc-=last_scroll;
		
		// show cursor
		draw_cur(0);
		
		// Wait for key pressed
		while(!(key = InKey())){}
		//
		k = key & 0xFF;
		//
		if(key & (KEXTEND<<8)){
			// extend key
			switch(k){
				case LEFT:{
					if(pos){
						pos--;
					}
					break;
				}
				case RIGHT:{
					if(pos<csize){
						pos++;
					}
					break;
				}
				case INSERT:{
					setmode(!mode);
					break;
				}
				case HOME:{
					pos=0;
					break;
				}
				case KEND:{
					pos=csize;
					break;
				}
				
			}
		}
		else if(k<0x20){
			// kontrol key
			switch(k){
				case '\n':{
					// Hide cursor
					draw_cur(1);
					
					fexit=1;
					break;
				}
				// backspace
				case 0x08:{
					if((csize)&&(pos)){
						char* p=buffer+pos-1;
						char* pn=p+1;
						int count = csize-pos;
						while(count--){
							*(p++) = *(pn++);
						}
						csize--;
						pos--;
					}
					break;
				}
			}
		}else{
			// simple char
			if(mode==MINSERT){
				// shift place
				if(csize<size){
					char* e=buffer+csize+1;
					char* pe=e-1;
					int count = csize-pos;
					while(count--){
						*(e--) = *(pe--);
					}
					buffer[pos++]=key;
					csize++;
				}
			}
			else{
				buffer[pos++]=key;
				if(pos>=csize){
					if(csize<size){
						csize++;
					}else{
						pos--;
					}
				}
			}
		}
		
	}
}
