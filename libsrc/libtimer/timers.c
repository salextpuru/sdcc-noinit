#include <im2.h>
#include <string.h>
#include "timers.h"

#define MAX_TIMERS	0x10

#define F_BUSY		1
#define F_CYCLYC	2

typedef struct {
	timert	timer;
	uint8_t	flags;
} timer;

static timer	timers[MAX_TIMERS];	// Счетчики


static void systimer_tick(){
	timer* t=timers;
	while( t < (timers+MAX_TIMERS) ){
		if( t->flags & F_BUSY ){
			if( t->timer ){
				t->timer --;
			}
		}
		t++;
	}
}

void timers_init(){
	CLI();
	memset(timers,0,sizeof(timers));
	im2Set();
	im2SetHandler(systimer_tick);
	SEI();
}

void timers_done(){
	CLI();
	im1Set();
}

timerid add_timer(){
	timer* t=timers;
	
	while( t < (timers+MAX_TIMERS) ){
		if( t->flags & F_BUSY ){
			t++;
			continue;
		}
		
		t->flags = F_BUSY;
		return (timerid)t;
	}
	return 0;
}

timert set_timer(timerid t, timert ticks){
	if(t){
		CLI();
		((timer*)t)->timer = ticks;
		SEI();
		return ticks;
	}
	return 0;
}

timert get_timer(timerid t){
	if(t){
		return ((timer*)t)->timer;
	}
	return 0;
}

void del_timer(timerid t){
	if(t){
		((timer*)t)->flags = 0;
	}
}
