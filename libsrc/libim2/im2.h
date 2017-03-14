#ifndef IM2_DEFINED
#define IM2_DEFINED

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

#endif /* IM2_DEFINED */
