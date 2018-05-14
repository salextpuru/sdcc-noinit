#include <stdint.h>
#include <conio.h>
#include <memman.h>
#include <string.h>

void fill_ram_pages(){
	uint16_t pg;
	printf("\nFill: ");
	for(pg=0; pg<8; pg++){
		if( ( pg==2 ) || (pg == 5) ){
			printf("%u:S ",pg);
		}
		else {
			printf("%u:%X ",pg,pg);
			MMSetPageWin(pg,3);
			*((volatile uint8_t*)0xC000) = pg;
		}
	}
}

void check_ram_pages(){
	uint16_t pg;
	printf("\nCheck: ");
	for(pg=0; pg<8; pg++){
		if( ( pg==2 ) || (pg == 5) ){
			printf("%u:S ",pg);
		}
		else {
			MMSetPageWin(pg,3);
			printf("%u:%u ",pg,*((volatile uint8_t*)0xC000));
		}
	}
}

void main(){
	ccls(0106);
	printf("Start Test mm128\n");
	
	printf("Init\n");MMInit();
	
	printf("Pages RAM: %i\n",MMgetPagesCount());
	printf("Pages ROM: %i\n",MMgetPagesCountROM());
	
	
	fill_ram_pages();
	
	check_ram_pages();
	
	while(1){
	}
}
