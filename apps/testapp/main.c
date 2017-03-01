#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <color.h>
#include <im2.h>
//
#include <stdint.h>
#include <string.h>
#include <math.h>
//
#define __SDCC_FLOAT_LIB 1
#include <float.h>

// Test iterations
#define iteration	300

float a=-0.5e-3;
float b=1.5e2;

union flong{
	float f;
	uint32_t l;
};

float fsadd(float a, float b)__naked;

/*
void fprint(float v){
	union flong f;
	f.f=v;
	printf("%f [%.8lX]",f.f, f.l);
}
*/

// Correct addition
void test_1(){
	union flong fl1;
	union flong fl2;
	//
	float fa1;
	float fa2;
	//
	int err;
	int ok;
	//
	int i;
	//
	err=0;
	ok=0;
	//
	printf("test_1() begin\n");
	//
	for(i=0; i<iteration; i++){
		// Generage two floats
		fl1.l = ((uint32_t)rand()) | (((uint32_t)rand())<<16);
		fl2.l = ((uint32_t)rand()) | (((uint32_t)rand())<<16);
		// Addition
		fa1 = fl1.f + fl2.f;
		fa2 = fsadd( fl1.f , fl2.f );
		// Ok or Error
		if( fa1 == fa2 ){
			ok++;
		}
		else{
			err++;
			fl1.f=fa1;
			fl2.f=fa2;
			printf("\nerr: %.8lX,%.8lX\n", fl1.l, fl2.l);
			printf("err: %.10f,%.10f\n", fl1.f, fl2.f);
		}
		//printf("[f1=%f] [f2=%f] ok=%i, err=%i\n", fl1.f, fl2.f, ok, err );
		printf("ok=%i, err=%i\r", ok, err);
	}
	printf("\ntest_1() end\n");
}

//
static volatile int	timer;
void timerhdl(){
	timer++;
}
void fdummy(float f){}

float testArray1[iteration];
float testArray2[iteration];

// Speed addition
void test_2(){
	int	time0;
	int	time1;
	//
	int i;
	//
	printf("\ntest_2() begin\n");
	//
	printf("Generate arrays. Wait.\n");
	for(i=0; i<iteration; i++){
		// Generage two floats
		testArray1[i] = ((uint32_t)rand()) | (((uint32_t)rand())<<16);
		testArray2[i] = ((uint32_t)rand()) | (((uint32_t)rand())<<16);
	}
	
	// Standart
	CLI();
	timer=0;
	im2SetHandler(timerhdl);
	im2Set();
	printf("Standart additions. Wait.\n");
	SEI();
	for(i=0; i<iteration; i++){
		// Addition
		fdummy(testArray1[i] + testArray2[i]);
	}
	time0 = timer;

	// SfS
	CLI();
	timer=0;
	im2SetHandler(timerhdl);
	im2Set();
	printf("SfS additions. Wait.\n");
	SEI();
	for(i=0; i<iteration; i++){
		// Addition
		fdummy(fsadd( testArray1[i], testArray2[i] ));
	}
	time1 = timer;
	//
	printf("Std add=%i, SfS add=%i\n",time0,time1);
	//
	printf("test_2() begin\n");
}

// Начало
void main(){
	CLI();
	//
	ccls(ATTRN(YELLOW,BLACK));
	print("Float running\n\n");
	/*
	printf("a=");fprint(a);putchar('\n');
	printf("b=");fprint(b);putchar('\n');
	printf("a+b= %f ",a+b);fprint(fsadd(a,b));putchar('\n');
	printf("\nOk\n");
	*/
	test_1();
	test_2();
	//
	while(1);
}
