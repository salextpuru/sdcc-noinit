#include <stdint.h>

static void puts(const char* s)__naked{
s;
__asm;
	ld	hl,#0x0002
	add	hl,sp
	// HL = адрес указателя на строку
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	// DE = адрес строки
	
puts_loop:
	ld	a,(de)
	or	a
	ret	z
	
	rst	0x10
	inc	de
	jr	puts_loop
__endasm;
}

static uint16_t putsn(const char* s)__naked{
s;
__asm;
	ld	hl,#0x0002
	add	hl,sp
	// HL = адрес указателя на строку
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	// DE = адрес строки
	ld	hl,#0000	;// Счетчик символов обнулен
	
putsn_loop:
	ld	a,(de)
	or	a
	ret	z
	rst	0x10
	inc	de
	inc	hl
	jr	putsn_loop
__endasm;
}

static uint64_t addll( uint64_t a, uint64_t b )__naked{
a;b;
__asm;
	ld	hl,#4
	add	hl,sp
	ex	de,hl	;// a = (de)
	;//
	ld	hl,#2
	add	hl,sp
	ld	c,(hl)
	inc	hl
	ld	b,(hl)	;// return = (bc)
	;//
	ld	hl,#12
	add	hl,sp	;// b = (hl)
	;// Делаем сложение add младших байтов
	ld	a,(de)
	add	a,(hl)
	ld	(bc),a
	inc	de
	inc	hl
	inc	bc
	;// Повторяем сложение adc ещё 7 раз
	exx
	ld	b,#7
addll7:
	exx
	ld	a,(de)
	adc	a,(hl)
	ld	(bc),a
	inc	de
	inc	hl
	inc	bc
	exx
	djnz	addll7
	
	ret
__endasm;
}


static char* int2hex(uint16_t i){
	static unsigned char hex[5];

	hex[4]=0;
	
	hex[3] = ((i&0x0F)>9)?((i&0x0F)+'A'-10):((i&0x0F)+'0');
	i=i>>4;
	hex[2] = ((i&0x0F)>9)?((i&0x0F)+'A'-10):((i&0x0F)+'0');
	i=i>>4;
	hex[1] = ((i&0x0F)>9)?((i&0x0F)+'A'-10):((i&0x0F)+'0');
	i=i>>4;
	hex[0] = ((i&0x0F)>9)?((i&0x0F)+'A'-10):((i&0x0F)+'0');
	i=i>>4;
	
	return hex;
}

static char* ll2hex(uint64_t ll){
	static unsigned char hex[17];
	
	int8_t i;
	
	hex[16]=0;
	
	for(i=15; i>=0; i--){
		hex[i] = ((ll&0x0F)>9)?((ll&0x0F)+'A'-10):((ll&0x0F)+'0');
		ll=ll>>4;
	}
	
	return hex;
}


long long a=0x1234567887654321;
long long b=0x1234567007654321;
long long c;

void main(){
	uint16_t n;
	//
	putsn("ex1: puts(\"Printed string\")");puts("\r\r");
	//
	n=putsn("ex2: putsn(\"string\")\r");
	puts(int2hex(n));puts(" symbols printed\r");
	//
	puts("\r\rex3: Add long long\r\r");
	//
	puts(" ");puts(ll2hex(a));puts("\r");
	puts("+\r");
	puts(" ");puts(ll2hex(b));puts("\r");
	puts(" ================\r");
	puts(" ");puts(ll2hex(addll(a,b)));puts("\r");
	
	
	while(1){
	}
}
