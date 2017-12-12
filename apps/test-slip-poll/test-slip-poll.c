//
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
//
#include <conio.h>
#include <color.h>
//
#include <slip.h>
#include <slipcrc8.h>
#include <zxslip.h>
//
#include <zxmc_uart.h>
//
static zxuart*	esp_uart;	// uart
static uint8_t  slip_rbuf[0x100]; // recv buffer
static uint8_t  slip_sbuf[0x100]; // send buffer
uint16_t slip_rbufc;	// counter
static slip_recv_struct	slip_rec; // recorder
//

//
void dump(uint8_t* buf, uint16_t size ){
	int line=0;
	printf("\n");
	while( size-- ){
		if(*(buf) < 16 ){
			printf("0%X ", *(buf++) );
		}
		else{
			printf("%X ", *(buf++) );
		}
		if( (++line) >= 10 ){
			line=0;
			printf("\n");
		}
	}
	printf("\n");
}

static uint8_t slbegin(){
	slip_rbufc=0;
	return 0;
}
static uint8_t slend(){
	// Handle packet here
	printf("Recieve packet %u bytes\n",slip_rbufc);
	dump(slip_rbuf, slip_rbufc);
	return 0;
}

static uint8_t slrecv(uint8_t c){
	if( slip_rbufc >= sizeof(slip_rbuf) ){
		// Packet too big
		slip_rbufc=0;
		slip_rec.status = 0;
	}
	else{
		slip_rbuf[slip_rbufc++]=c;
	}
	return 0;
}

static uint8_t send_byte(uint8_t c) {
	while( !esp_uart->write(&c, 1) ){
		// Wait for byte sending
	}
}

static void esp_poll(){
	uint8_t* b=slip_sbuf;
	uint8_t* e=zxslip_crq_esp_poll(slip_sbuf);
	
	zxslip_setId(zxslip_getId()+1);
	
	while( b!=e ){
		slip_send_byte(*(b++), send_byte);
	}
}

static uint8_t wait;

int main ( int argc, char **argv ) {
	//
	__asm;
		ei
	__endasm;
	
	esp_uart=zxmc_uart();
	//
	ccls(6);
	//
	printf("- test-slip-poll -\n");
	//
	esp_uart->init();
	
	slip_recv_init(&slip_rec, slrecv, slbegin, slend );
	
	while( 1 ){
		uint8_t c;
		if( wait == 0 ){
			esp_poll();
			wait=50;
			printf("Poll()\n");
		}
		else{
			wait--;
		}
		
		__asm;
			halt
		__endasm;
		
		if( esp_uart->read(&c,1)>0 ){
			slip_recv_byte(&slip_rec, c);
		}
	}
	//
	return 0;
}
