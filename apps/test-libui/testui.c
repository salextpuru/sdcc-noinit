#include <window.h>
#include <im2.h>

// =1 - PS2 клавиатура
// =0 - ZX  клавиатура
#define PS2_KEYS	0

#if PS2_KEYS
	#include <keybops2.h>
#else
	#include <keybozx.h>
	#include <zxkbd.h>
#endif

window w1;
window w2;
window w3;

// Свой метод обработки события для окна
static void w3_hEvent(struct window* this, event* ev){
	char s[2]={0,0};
	
	// Печатаем код клавиши
	if(ev->ev == evKbd){
		this->draw(this);
		this->at(this, 2, 2);
		
		switch ( ev->key ){
			case kbdLEFT:{
				this->puts(this, "kbdLEFT");
				break;
			}
			case kbdRIGHT:{
				this->puts(this, "kbdRIGHT");
				break;
			}
			case kbdUP:{
				this->puts(this, "kbdUP");
				break;
			}
			case kbdDN:{
				this->puts(this, "kbdDN");
				break;
			}
			case kbdESC:{
				this->puts(this, "kbdESC");
				break;
			}
			default:
				s[0] = ev->key;
				this->puts(this, s);
		}
	}
	
	// Не утруждаемся обработкой ESC
	window_hEvent(this,ev);
}

int main(int argc, char* argv[]){
	// Драйвер экрана
	setScrDriverZX();
	// Драйвер клавиатуры
#if PS2_KEYS
	setKeyboardPS2();
#else
	setKeyboardZX();
	im2SetHandler(zxKbdScan);
	im2Set();
#endif
	SEI();
	//
	window_init(&w1);
	//window_exec(&w1);
	window_draw(&w1);
	window_at(&w1, 0,0);
	window_puts(&w1, "Window 1 Very long text");
	//
	window_init(&w2);
	w2.border = btSingl;
	w2.x=4; w2.y =2;
	w2.w= 22; w2.h=16;
	w2.paper = 2<<3;
	// window_exec(&w2);
	window_draw(&w2);
	window_at(&w2, 0,0);
	window_puts(&w2, "Window 2  Very long text");
	//
	window_init(&w3);
	w3.border = btDoubl;
	w3.x=16; w3.y =12;
	w3.w= 12; w3.h=8;
	w3.paper = 4<<3;;
	
	// Переопределяем метод. Легко!
	w3.hEvent = w3_hEvent;	
	window_exec(&w3);
	
	return 0;
}
