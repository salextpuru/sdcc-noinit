#include <wcplugin.h>

const wcWindow w={
	1,0, // Header
	23,7,	// xy
	34,16,	// wh
	0xC0,	// color
	.data.type1.topHeader="TopHeader of window",
	.data.type1.botHeader="BotHeader of window",
	.data.type1.text="My text in window!"
};

void main(){
	// Draw window
	wcPRWOW(&w);
	
	// Draw header
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

	// Draw header
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

	// Exit
	wcRRESB(&w);
}
