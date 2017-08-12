#include "devils.h"
#include "hero.h"
#include "scenes.h"
#include "sprites.h"

// Массив описания чертей
static devil devils[DevilsMax];

// Количество чертей на данной карте (не более DevilsMax)
static uint8_t Devils;

/**
 * Обработка поведения одного черта
 *	Окружение уже получено функцией getPointArea(d->x,d->y);
 */

extern uint8_t pseudoRand;

/**
 * @brief Изменить направление движения
 */
static void devil_setdir(devil* d, uint8_t dir){
	d->direct_old = d->direct;
	d->direct = dir;
}

/**
 * @brief Проверить - изменялось ли направление на пред. шаге
 * @return uint8_t - true = изменялось
 */
static uint8_t devil_ischdir(devil* d){
	return	!(d->direct_old == d->direct);
}

// Обработка поведения черта, стрящего на месте
static void devil_dnone(devil* d){
	// Пока что все черти стремятся налево :)
	devil_setdir(d, dirLeft);
}

// Обработка поведения черта, движущегося влево
static void devil_dleft(devil* d){
	// направление не менялось
	// Проверка лестниц
	if( !devil_ischdir(d) && (pseudoRand&1==1) ){
		if(point_on == 'L'){
			devil_setdir(d, dirUp);
			return;
		}
		
		if(point_dn == 'L'){
			devil_setdir(d, dirDown);
			return;
		}
	}
	
	if(	( point_lf == 'b' )||
		( point_lf == 'B' ) ){
		devil_setdir(d, dirRight);
		return;
	}
	else{
		d->x--;
		devil_setdir(d, dirLeft);
	}
}

// Обработка поведения черта, движущегося вверх
static void devil_dright(devil* d){
	// направление не менялось
	// Проверка лестниц
	if( !devil_ischdir(d) && (pseudoRand&1==1) ){
		if(point_on == 'L'){
			devil_setdir(d, dirUp);
			return;
		}
		
		if(point_dn == 'L'){
			devil_setdir(d, dirDown);
			return;
		}
	}
	
	if(	( point_rt == 'b' )||
		( point_rt == 'B' ) ){
		devil_setdir(d, dirLeft);
		return;
	}
	else{
		d->x++;
		devil_setdir(d, dirRight);
	}
}

// Обработка поведения черта, движущегося вниз
static void devil_dup(devil* d){
	if(	( point_up == 'b' )||
		( point_up == 'B' )||
		( point_on != 'L' ) ){
		devil_setdir(d, dirLeft);
		return;
	}
	
	// А не захотелось ли чертяке на турник ?
	if( ( point_lf == 'U' ) &&
		(pseudoRand&1==1) ){
		devil_setdir(d, dirLeft);
		return;	
	}
	
	if( ( point_rt == 'U' ) &&
		(pseudoRand&1==1) ){
		devil_setdir(d, dirRight);
		return;	
	}
	
	//
	d->y--;
	devil_setdir(d, dirUp);
}

// Обработка поведения черта, движущегося
static void devil_ddown(devil* d){
	if(	( point_dn == 'b' )||
		( point_dn == 'B' )){
		devil_setdir(d, dirLeft);
		return;
	}
	
	// А не захотелось ли чертяке на турник ?
	if( ( point_lf == 'U' ) &&
		(pseudoRand&1==1) ){
		devil_setdir(d, dirLeft);
		return;	
	}
	
	if( ( point_rt == 'U' ) &&
		(pseudoRand&1==1) ){
		devil_setdir(d, dirRight);
		return;	
	}
	
	//
	d->y++;
	devil_setdir(d, dirDown);
}

// Обработка поведения черта. Один шаг
static void hDevil(devil* d){
	getPointArea(d->x,d->y);
	
	// Падение
	if((point_on==' ')&&(point_dn==' ')){
		(d->y)++;
	}
	// Направления
	else switch (d->direct){
		case dirNone:{
			devil_dnone(d);
			break;
		}
		case dirLeft:{
			devil_dleft(d);
			break;
		}
		case dirRight:{
			devil_dright(d);
			break;
		}
		case dirUp:{
			devil_dup(d);
			break;
		}
		case dirDown:{
			devil_ddown(d);
			break;
		}
	}
}

/**
 * @brief Скорость чертей
 */
enum {devil_delay=3};
static uint8_t ddelay;

void check_devils(){
	uint8_t i;

	// Задержка
	if( (--ddelay) ){
		return;
	}
	ddelay=devil_delay;
	
	for(i=0; i<Devils; i++){
		// Удаляем черта
		draw_scene_block(curScene, devils[i].x , devils[i].y );
		// анализ его мыслей и желаний
		// сопоставление их с возможностями
		hDevil(devils+i);
		// Рисуем черта
		spr0_out0_attr(&spr_devil, devils[i].x, devils[i].y );
	}
}

void StartAddDevils(){
	Devils=0;
	ddelay=devil_delay;
}

void AddDevil(uint8_t x, uint8_t y){
	if( Devils>=DevilsMax ){
		return;
	}
	//
	devils[Devils].x=x;
	devils[Devils].y=y;
	devils[Devils].direct = dirNone;
	devils[Devils].direct_old = dirNone;
	//
	Devils++;
}
