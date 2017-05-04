#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <timers.h>
#include <esp8266.h>

struct tIFNET ifesp8266;

void main(){
	int8_t ret=0;
	
	ccls(0016);
	print("Test ESP8266 socket\n");
	//
	timers_init();
	// DHCP WiFi client via ZiFi
	ret=IFNET_ESP8266.up(&ifesp8266, 0x00000000, ifWIFICL, esp8266ZIFI, NULL);
	printf("If up %i\n",ret);
	//
	while(1){
	}
}
