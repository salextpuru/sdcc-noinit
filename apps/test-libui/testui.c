#include <window.h>
#include <zxkbd.h>
#include <im2.h>

window w1;
window w2;
window w3;

int main(int argc, char* argv[]){
	setScrDriverZX();
	//
	im2SetHandler(zxKbdScan);
	im2Set();
	SEI();
	//
	window_init(&w1);
	window_exec(&w1);
	window_at(&w1, 0,0);
	window_puts(&w1, "Window 1 Very long text");
	//
	window_init(&w2);
	w2.border = btSingl;
	w2.x=4; w2.y =2;
	w2.w= 22; w2.h=16;
	w2.paper = 2<<3;
	window_exec(&w2);
	window_at(&w2, 0,0);
	window_puts(&w2, "Window 2  Very long text");
	//
	window_init(&w3);
	w3.border = btDoubl;
	w3.x=16; w3.y =12;
	w3.w= 12; w3.h=8;
	w3.paper = 4<<3;;
	window_exec(&w3);
	window_at(&w3, 0,0);
	window_puts(&w3, "Window 3  Very long text");
	
	return 0;
}
