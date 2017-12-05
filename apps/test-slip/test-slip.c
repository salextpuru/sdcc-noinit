#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <conio.h>
#include <color.h>

#include <slip.h>
#include <slipcrc8.h>

uint8_t sendbuf[0x40];
uint8_t slipbuf[0x80];
uint8_t recbuf[0x100];

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

void fill_sendbuf(){
	uint16_t i;
	for( i=0; i<sizeof(sendbuf); i++ ){
		sendbuf[i] = i;
	}
}

// SLIP buffer!
uint16_t slipbufc;

uint8_t toSLIPcb(uint8_t c){
	slipbuf[slipbufc++] =c;
}

// SLIP rec
slip_recv_struct	sr;

uint8_t slbegin(){
	printf("SLBEGIN detected!\n");
}
uint8_t slend(){
	printf("SLEND detected!\n");
}
uint16_t recbufc;
uint8_t slrecv(uint8_t c){
	recbuf[recbufc++]=c;
}

int main ( int argc, char **argv ) {
	int i;
	//
	ccls(6);
	//
	printf("- test-slip -\n");
	//
	fill_sendbuf();
	sendbuf[sizeof(sendbuf)-1] = slipcrc8buf(sendbuf, sizeof(sendbuf)-1);
	dump(sendbuf, sizeof(sendbuf));
	//
	slipbufc=0;
	slip_send_buf( sendbuf, sizeof(sendbuf), toSLIPcb );	
	dump(slipbuf, slipbufc);
	//
	recbufc=0;
	slip_recv_init(&sr, slrecv, slbegin, slend );
	slip_recv_buf(slipbuf, slipbufc, &sr);
	dump(recbuf, recbufc);
	printf("CRC8RECV=%.2X\n",slipcrc8buf(recbuf, recbufc-1));
	printf("CRC8RECVBUF=%.2X\n",recbuf[recbufc-1]);
	// diff
	for( i=0; i<recbufc; i++ ){
		if( sendbuf[i] != recbuf[i] ){
			printf("Diff pos %.4X sendbuf %.2X rec %.2X\n",i,sendbuf[i], recbuf[i]);
		}
	}
	//
	while(1);
	return 0;
}

