#include <stdio.h>
#include <conio.h>
#include "testso_common.h"

void tsInit(){
	ccls(014);
	printf("Init test so v1 library\n\n");
}

void tsShowInfo(){
	printf("I am test so v1 library\n");
	common_info();
}

uint16_t tsAbs (int16_t n) {
	return (n<0)? -n : n;
}
