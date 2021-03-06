#ifndef IM2_DEFINED
#define IM2_DEFINED

#include <stdint.h>

/**
 * 	Set handler for im2 irq
 */
void im2SetHandler(void* handler);

/*
 * 	Set IM2 mode
 */
void im2Set();

/*
 * 	Set IM2 mode
 */
void im1Set();

/*
 * 	Set IM0 mode
 */
void im0Set();

/*
 * 	Disable IRQ
 */
inline void CLI()__naked{
__asm;
	di
__endasm;
}

/*
 * 	Enable IRQ
 */
inline void SEI()__naked{
__asm;
	ei
__endasm;
}
 
/**
 * @brief Wait for tick (1/50sec=20ms)
 * 	Interrupt must be enabled! Else your program will be infinity halt.
 * 
 * @param tick - number of INTs
 */
void waitINTS(uint8_t tick);

/**
 * @brief Ждем один INT
 */
inline void HALT()__naked{
__asm;
	halt
__endasm;
}

#endif /* IM2_DEFINED */
