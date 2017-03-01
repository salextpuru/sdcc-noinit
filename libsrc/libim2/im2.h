#ifndef IM2_DEFINED
#define IM2_DEFINED

/**
 * 	Set handler for im2 irq
 */
void im2SetHandler(void* handler)__naked;

/*
 * 	Set IM2 mode
 */
void im2Set()__naked;

/*
 * 	Set IM2 mode
 */
void im1Set()__naked;

/*
 * 	Set IM0 mode
 */
void im0Set()__naked;

/*
 * 	Disable IRQ
 */
void CLI()__naked;

/*
 * 	Enable IRQ
 */
void SEI()__naked;

#endif /* IM2_DEFINED */
