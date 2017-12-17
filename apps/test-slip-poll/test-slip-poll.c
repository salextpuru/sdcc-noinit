//
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
//
#include <conio.h>
#include <color.h>
//
#include "cmdtrscl.h"
#include <zxslip.h>
//
#include <zxmc_uart.h>
//


int main ( int argc, char **argv ) {
	//
	ccls(6);
	printf("Test esp-poll\n");
	zxmc_uart()->init();
	
	cmdtrscl_init(zxmc_uart());
	
	while( 1 ){
		printf("poll() query %u\n",zxslip_getId());
		esp_poll();
	}
	//
	return 0;
}
