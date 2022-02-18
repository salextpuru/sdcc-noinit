#ifndef __KEYIDLE_H__
#define __KEYIDLE_H__

uint16_t iGetChar();

#define EI() \
__asm \
    ei \
__endasm

#define DI() \
__asm \
    di \
__endasm


#endif /* __KEYIDLE_H__ */
