//
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
//
#include <conio.h>
#include <color.h>
//
#include "cmdtrscl.h"
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
		esp_poll();
	}
	//
	return 0;
}
