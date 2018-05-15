#include <stdint.h>
#include <conio.h>
#include <memman.h>
#include <string.h>

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
		
		printf("\n");
	}
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

void main(){
	ccls(0106);
	printf("Start Test mm128\n");
	
	MMInit();
	printf("Init\n");
	
	printf("Pages RAM: %i\n",MMgetPagesCount());
	printf("Pages ROM: %i\n",MMgetPagesCountROM());
	
	memwin_info();
	
	fill_ram_pages();
	
	check_ram_pages();
	
	while(1){
	}
}
