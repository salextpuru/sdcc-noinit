/**
    @file base_class.c
    Базовое управление классами
*/

#include <base_class.h>

void tBaseClass_Init(tBaseClass*this){
	this->classid = getClassId(tBaseClass_Init);
}

