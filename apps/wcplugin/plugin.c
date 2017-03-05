#include <string.h>
#include <wcplugin.h>

const wcWindow w={
	1,0xFF, // Header
	4,4,	// xy
	70,18,	// wh
	0xC0,	// color
	.data.type1.topHeader="TopHeader of window",
	.data.type1.botHeader="BotHeader of window",
	.data.type1.text="My text in window!"
};

static char msgtable[]=
	"Message 0 hi!\r\r\x0\x0"
	"Message 1 Hihi!\r\r\x0\x0"
	"Message 2 Hahahai!\r\r\x0\x0";

static void clw(){
	wcPRWOW(&w);
}

void pause(uint8_t n){
	uint8_t i;
	for(i=0; i<n; i++){
		wcWaitForFrame();
	}
}

void scroll_test(uint8_t mode){
	uint8_t i,j,b;
	
	uint8_t n = w.winHeigh-2;
	
	for(i=0; i<w.winHeigh-2; i++){
		for(j=0; j<w.winWidth-2; j++){
			b = i+j;
			if(b<0x20){
				b+=0x20;
			}
			wcPRSRW(&w, &b, j+1, i+1, 1, 0xC0);
		}
		
	}
	
	for(i=0; i<n; i++){
		wcSCRLWOW(&w, mode, 1, 1, w.winWidth-2, w.winHeigh-2);
		pause(10);
	}
}

void main(){
	// Edited buffer
	char buf[0x20];
	memset(buf,' ', sizeof(buf));
	strcpy(buf,"My text");

	// Call gedpl (as spoken in manual)
	wcGEDPL();
	//
	clw();
	wcPrint(&w, "Test wcKbScan (LAT)", 1, 1, 0xF1);
	while(!wcKeyFunc(wcESC)){
		unsigned char c;
		wcWaitForFrame();
		c=wcKbScan(wcKeyTableC);
		if(c){
			wcPRSRW(&w, &c, 1, 3, 1, 0xf2);
		}
	}

	//
	clw();
	wcPrint(&w, "Test wcKbScan (All locales)", 1, 1, 0xF1);
	while(!wcKeyFunc(wcESC)){
		unsigned char c;
		wcWaitForFrame();
		c=wcKbScan(wcKeyTableALL);
		if(c){
			wcPRSRW(&w, &c, 1, 3, 1, 0xf2);
		}
	}

	//
	clw();
	wcPrint(&w, "Test wcISTR (mode 2, without indicators)", 1, 1, 0xF1);
	wcISTRinit2(&w, 1, 3, 0, 18, buf, sizeof(buf));
	// wait for escape
	while(!wcKeyFunc(wcESC)){
		wcWaitForFrame();
		wcISTREdit2(&w);
	}
	
	//
	clw();
	wcPrint(&w, "Test wcISTR (mode 2, with top indicators)", 1, 1, 0xF1);
	wcISTRinit2IndTop(&w, 1, 3, 0, 18, buf, sizeof(buf));
	// wait for escape
	while(!wcKeyFunc(wcESC)){
		wcWaitForFrame();
		wcISTREdit2Ind(&w);
	}
	
	//
	clw();
	wcPrint(&w, "Test wcISTR (mode 2, with bottom indicators)", 1, 1, 0xF1);
	wcISTRinit2IndBottom(&w, 1, 3, 0, 18, buf, sizeof(buf));
	// wait for escape
	while(!wcKeyFunc(wcESC)){
		wcWaitForFrame();
		wcISTREdit2Ind(&w);
	}
	
	// Draw window (clear)
	clw();
	wcTXTPR(&w, "The wcTXTPR test.\r"
			"\x09""Inverse colours\r\r"
			"\x01""Color1 ""\x02""Color2\r"
			"\x03""Color3 ""\x04""Color4\r"
			"\x05""Color5 ""\x06""Color6\r"
			"\x07""Color7 ""\x08""Color8\r",
		1, 1);
	while(!wcKeyFunc(wcESC)){}
	
	// Draw window (clear)
	clw();
	wcPrint(&w, "Test wcMEZZ", 1, 1, 0xF1);
	wcMEZZ(&w,0, msgtable, 1,3);
	wcMEZZ(&w,1, msgtable, 1,5);
	wcMEZZ(&w,2, msgtable, 1,7);
	while(!wcKeyFunc(wcESC)){}
	
	clw();
	wcPrint(&w, "Test wcSCRLWOW up", 25, 0, 0xF1);
	scroll_test(wcSCRL_UP | wcSCRL_STEP(1) | wcSCRL_ATTRS | wcSCRL_CLEAR);
	wcPrint(&w, "Test wcSCRLWOW up done", 25, 0, 0xF1);
	while(!wcKeyFunc(wcESC)){}
	
	clw();
	wcPrint(&w, "Test wcSCRLWOW down", 25, 0, 0xF1);
	scroll_test(wcSCRL_DOWN | wcSCRL_STEP(1) | wcSCRL_ATTRS | wcSCRL_CLEAR);
	wcPrint(&w, "Test wcSCRLWOW down done", 25, 0, 0xF1);
	while(!wcKeyFunc(wcESC)){}
	
	// Exit
	wcRRESB(&w);
}
