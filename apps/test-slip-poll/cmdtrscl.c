/**
 * 	Transfer of command (client side)
 */
#include <slip.h>
#include <zxslip.h>

#include "cmdtrscl.h"

// Buffer sizes, etc
enum {
	zxslip_tbuffer_size=0x400,
	zxslip_rbuffer_size=0x400,
	//
	zxslip_time_out_senbyte = 128,
	zxslip_time_out_recbyte = 128
};

// TimeOut counter
static uint16_t		time_out;

// UART abstraction
static zxuart* uart;

// buffers
static uint8_t rbuf[zxslip_rbuffer_size];
static uint8_t tbuf[zxslip_tbuffer_size];

static uint16_t 	slip_rbufc;	// counter
static slip_recv_struct	slip_rec; // recorder

// Status
enum {
	statNone=0,	// Status after reset
	statWait,	// Wait for answer
	StatError	// Error detected
};

static uint8_t status;

// Reset protocol
static void reset() {
	slip_rbufc=0;
	slip_rec.status = 0;
	time_out = 0;
	status=statNone;
}

// Callback on Begin
static uint8_t slip_begin_cb() {
	slip_rbufc=0;
	return 0;
}

// Callback on End
static uint8_t slip_end_cb() {
	// Handle packet here
	zxslip_answer_parse(rbuf, slip_rbufc);
	return 0;
}

// On recv byte
static uint8_t slip_recv_cb(uint8_t c) {
	if ( slip_rbufc >= sizeof(rbuf) ) {
		// Packet too big (reset protocol)
		status = StatError;
		return 1;
	} else {
		rbuf[slip_rbufc++]=c;
	}
	return 0;
}

static uint8_t send_byte(uint8_t c) {
	time_out = 0;
	while ( !uart->write(&c, 1) ) {
		// Wait for byte sending
		if ( (++time_out) >= zxslip_time_out_senbyte ) {
			// Error (no check now!)
			status = StatError;
			return 1;
		}
	}
	return 0;
}

int8_t cmdtrscl_transfer(uint8_t* b, uint8_t* e) {
	zxslip_setId(zxslip_getId()+1);

	status = statWait;
	
	while ( ( b!=e ) && (status==statWait) ) {
		slip_send_byte(*(b++), send_byte);
	}

	time_out = 0;
	
	if( status!=statWait ){
		reset();
		return -2;
	}
	
	while ( status == statWait ) {
		uint8_t c;
		
		if ( (++time_out) >= zxslip_time_out_recbyte ) {
			status = StatError;
			return 1;
		}
		
		if ( uart->read(&c,1)>0 ) {
			slip_recv_byte(&slip_rec, c);
			time_out = 0;
		}
	}
	
	if( status!=statWait ){
		reset();
		return -3;
	}
	
	reset();
	return 0;
}

void esp_poll(){
	uint8_t* e= zxslip_crq_esp_poll(tbuf);
	cmdtrscl_transfer(tbuf, e);
}

static void esp_poll_cb(zxslip_pkt_header* h, zxslip_apkt_esp_poll* p){
	
}

void cmdtrscl_init(zxuart* uart_) {
	uart=uart_;
	slip_recv_init(&slip_rec, slip_recv_cb, slip_begin_cb, slip_end_cb );
	zxslip_a_esp_poll_cb=esp_poll_cb;
}
