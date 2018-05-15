#include <stdint.h>
#include <conio.h>
#include <memman.h>
#include <string.h>
#include <im2.h>
#include <zxkbd.h>

void fill_ram_pages(){
	uint16_t pg;
	printf("\nFill: ");
	for(pg=0; pg<8; pg++){
		if( ( pg==2 ) || (pg == 5) ){
			printf("%u:[S] ",pg);
		}
		else {
			printf("%u:[%X] ",pg,pg);
			MMSetPageWin(pg,3);
			*((volatile uint8_t*)0xC000) = pg;
		}
	}
	printf("\n");
}

void check_ram_pages(){
	uint16_t pg;
	printf("\nCheck: ");
	for(pg=0; pg<8; pg++){
		if( ( pg==2 ) || (pg == 5) ){
			printf("%u:[S] ",pg);
		}
		else {
			MMSetPageWin(pg,3);
			printf("%u:[%u] ",pg,*((volatile uint8_t*)0xC000));
		}
	}
	printf("\n");
}

void memwin_info() {
	mm_win_d* win;
	uint8_t i;
	for(i=0;i<4;i++){
		win=MMgetWinD(i);
		printf("%u: %s page %u.\n  Flags: ", i, (win->flags & MWF_ROM)?"ROM":"RAM", win->page );
		printf("WIN %u%s%s%s%s",MWF_GETWIN(win->flags),
			(win->flags & MWF_FIXED)?" MWF_FIXED":"",
			(win->flags & MWF_ROM)?" MWF_ROM":"",
			(win->flags & MWF_ERAM)?" MWF_ERAM":"",
			(win->flags & MWF_EROM)?" MWF_EROM":"");
		
		printf("\n\n");
	}
}

void mempage_info() {
	uint8_t i;
	uint8_t pview=0;
	for(i=0;i<MMgetPagesCount();i++){
		uint8_t flags = MMGetPageFlags(i);
		printf("%x:%i[%s%s%s]",i, MPG_GETWIN(flags),
			(flags & MPG_BUSY)?"MPG_BUSY ":"",
			(flags & MPG_FIXED)?"MPG_FIXED ":"",
			(flags & MPG_ABSENT)?"MPG_ABSENT ":""
		);
		printf("\n");
		if((++pview)>=8){
			press_a_key();cls();
		}
	}
	
}

void press_a_key(){
	printf("\nPress a key\n");
	while(!zxKbdInKey()){}
}

void main(){
	CLI();
	setScrDriverZX();
	im2SetHandler(zxKbdScan);
	im2Set();
	SEI();
	ccls(0106);
	printf("Start Test mm128\n");
	//
	press_a_key();cls();
	
	MMInit();
	printf("Init\n\n");
	
	printf("Pages RAM: %i\n",MMgetPagesCount());
	printf("Pages ROM: %i\n\n",MMgetPagesCountROM());
	memwin_info();
	press_a_key();cls();
	
	MMSetPageFlags(5,MPG_FIXED);
	MMSetPageFlags(2,MPG_FIXED);
	mempage_info();
	
	fill_ram_pages();
	check_ram_pages();
	
	while(1){
	}
}
