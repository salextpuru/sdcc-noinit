#include <stdint.h>
#include <zxkbd.h>

#include "keyidle.h"

// Get key with IDLE
uint16_t iGetChar(){
    uint16_t k=0;
    //
    while(!k) {
        #ifdef IDLE_FUNC
        IDLE_FUNC();
        #endif /* IDLE_FUNC */
        // Wait for 1/50 sec
        __asm;
            halt;
        __endasm;
        // get key
        k = zxKbdInKey();
    }
    //
    return k;
}

// Interrupt handler must me called
void irq38() { zxKbdScan(); }
