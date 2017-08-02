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
void CLI();

/*
 * 	Enable IRQ
 */
void SEI();
 
/**
 * @brief Wait for tick (1/50sec=20ms)
 * 	Interrupt must be enabled! Else your program will be infinity halt.
 * 
 * @param tick - number of INTs
 */
void waitINTS(uint8_t tick);

#endif /* IM2_DEFINED */
