#include <stdint.h>
#include <conio.h>
#include <memman.h>
#include <string.h>
#include <im2.h>
#include <zxkbd.h>
#include <so.h>

void press_a_key(){
	printf("\nPress a key\n");
	while(!zxKbdInKey()){}
}

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
	
	printf("memwin_info\n");
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
	
	printf("mempage_info\n");
	
	for(i=0;i<MMgetPagesCount();i++){
		uint8_t flags = MMGetPageFlags(i);
		printf("%x:%i[%s%s%s]",i, MPG_GETWIN(flags),
			(flags & MPG_BUSY)?"MPG_BUSY ":"",
			(flags & MPG_FIXED)?"MPG_FIXED ":"",
			(flags & MPG_ABSENT)?"MPG_ABSENT ":""
		);
		printf("\n");
		if((++pview)>=8){
			break;
		}
	}
	
}

void get_use_test(){
	uint8_t i;
	uint16_t page;
	for(i=0;i<=MMgetPagesCount();i++){
		if( MMgetFreePage(&page) == MME_OK ){
			printf("get %u ",page);
			if( MMuseFreePage(&page) == MME_OK ){
				printf("use %u ",page);
			}
			else {
				printf("no free pages",page);
			}
		}
		else{
			printf("no free pages",page);
		}
		printf("\n");
	}
}

void free_test(){
	uint8_t i;
	for(i=0;i<=MMgetPagesCount();i++){
		printf("free %u ",i);
		if( MMfreePage(i) == MME_OK){
			printf("ok");
		}
		else{
			printf("skip");
		}
		printf("\n");
	}
}

//const char* memman_SetLoadAdr(void *loadAdress);

#define modAdr	0x6000

void main(){
	shared_link* p=get_shared_links_area();
	CLI();
	im2SetHandler(zxKbdScan);
	im2Set();
	SEI();
	ccls(0106);
	
	printf("Start Test mm128\n");
	
	// Настройка резидентной части
	p->load_adr=modAdr;
	p->page=5;
	
	// Reloctable
	printf("area %.4X\n",p);
	printf("nextlink %.4X\n",p->next_link);
	printf("loadadr %.4X\n",p->load_adr);
	printf("page %.4X\n",p->page);
	printf("flags %.4X\n",p->flags);
	printf("name %s\n",p->name);
	
	// Настройка подгружаемой части
	printf("Start %.4X end %.4X\n", modAdr, soReloc(modAdr) );
	
	printf("mm128 loaded\n");
		
	//
	press_a_key();cls();
	
	MMInit();
	printf("Init\n\n");
	
	printf("Pages RAM: %i\n",MMgetPagesCount());
	printf("Pages ROM: %i\n\n",MMgetPagesCountROM());
	memwin_info();
	press_a_key(); cls();
	
	mempage_info();
	press_a_key(); cls();
	
	fill_ram_pages();
	check_ram_pages();
	
	press_a_key(); cls();
	get_use_test();mempage_info();
	
	press_a_key(); cls();
	free_test();mempage_info();
	
	while(1){}
}
