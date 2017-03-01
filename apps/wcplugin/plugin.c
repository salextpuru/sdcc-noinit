#include <string.h>
#include <wcplugin.h>

const wcWindow w={
	1,0xFF, // Header
	23,7,	// xy
	34,16,	// wh
	0xC0,	// color
	.data.type1.topHeader="TopHeader of window",
	.data.type1.botHeader="BotHeader of window",
	.data.type1.text="My text in window!"
};

void main(){
	// Edited buffer
	char buf[0x20];
	memset(buf,' ', sizeof(buf));
	strcpy(buf,"My text");

	// Draw window
	wcPRWOW(&w);
	
	wcPrint(&w, "Test 1 (LAT)", 2, 2, 0xF1);
	// wait for escape
	while(!wcKeyFunc(wcESC)){
		unsigned char c;
		wcWaitForFrame();
		c=wcKbScan(wcKeyTableC);
		if(c){
			wcPRSRW(&w, &c, 14, 2, 1, 0xf2);
		}
	}

	wcPrint(&w, "Test 2 (All locales)", 2, 4, 0xF3);
	// wait for escape
	while(!wcKeyFunc(wcESC)){
		unsigned char c;
		wcWaitForFrame();
		c=wcKbScan(wcKeyTableALL);
		if(c){
			wcPRSRW(&w, &c, 22, 4, 1, 0xF4);
		}
	}

	wcISTRinit2(&w,2, 6, 0, 18, buf, sizeof(buf));
	// wait for escape
	while(!wcKeyFunc(wcESC)){
		wcWaitForFrame();
		wcISTREdit2(&w);
	}
	wcPRSRW(&w, buf, 2, 7, sizeof(buf), 0xf5);
	
	wcISTRinit2IndTop(&w,2, 6, 0, 18, buf, sizeof(buf));
	// wait for escape
	while(!wcKeyFunc(wcESC)){
		wcWaitForFrame();
		wcISTREdit2Ind(&w);
	}
	wcPRSRW(&w, buf, 2, 7, sizeof(buf), 0xf5);
	
	wcISTRinit2IndBottom(&w,2, 6, 0, 18, buf, sizeof(buf));
	// wait for escape
	while(!wcKeyFunc(wcESC)){
		wcWaitForFrame();
		wcISTREdit2Ind(&w);
	}
	wcPRSRW(&w, buf, 2, 7, sizeof(buf), 0xf5);
	
	// Exit
	wcRRESB(&w);
}
