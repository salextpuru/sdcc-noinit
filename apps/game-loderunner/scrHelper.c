#include <spr0.h>
#include <conio.h>
#include "scrHelper.h"
#include "sprites.h"

/**
 * @brief Инициализация экрана с 0xC000
 */
void scrInit(){
	spr0_set_scr_adr(0xC000);
	conio_set_scr_adr(0xC000);
	color(6);
	cls();
}
 
/**
 * @brief Перенос экрана с 0xC000 в 0x4000
 */
void scrFlip()__naked{
__asm;
	push 	hl
	push 	de 
	push 	bc
	ld 	hl,#0xC000
	ld 	de,#0x4000
	ld 	bc,#0x1B00
	ldir
	pop 	bc
	pop 	de
	pop 	hl
	ret
__endasm;
}

void scrCLS()__naked{
// Последние две строки не чистим - там статус
// Чистить весь экран? дурь! Чистим только атриубуты
__asm;
	push 	hl
	push 	de 
	push 	bc
	ld 	hl,#0xD800
	ld 	de,#0xD801
	ld 	bc,#0x02BF
	ld 	(hl),#00
	ldir
	pop 	bc
	pop 	de
	pop 	hl
	ret
__endasm;
}

void draw_scene(const scrPlan scn){
	uint8_t x;
	uint8_t y;
	
	scrCLS();
	
	for(y=0; y<sceneH; y++){
		for(x=0; x<sceneW; x++){
			switch(scn[y][x]){
				case 'B':
				case 'b':{
					spr0_out0_attr(&spr_brick, x, y);
					break;
				}
				case 'L':{
					spr0_out0_attr(&spr_ladder, x, y);
					break;
				}
				case 'T':{
					spr0_out0_attr(&spr_treasure, x, y);
					break;
				}
				case 'U':{
					spr0_out0_attr(&spr_upholder, x, y);
					break;
				}
				default:;
			}
		}
	}
}
