/**
 * MMDRVSTART -  начальный адрес драйвера
 */
#include "memman.h"

// +00 void MMInit()
//jp _MMInit
void MMInit() __naked{
__asm;
	jp MMDRVSTART+00
__endasm;
}

// +03 mm_win_d* __MMgetMemWinsD()
//jp ___MMgetMemWinsD
mm_win_d* __MMgetMemWinsD() __naked{
__asm;
	jp MMDRVSTART+03
__endasm;
}
	
// +06 uint16_t MMgetWinPage(uint8_t w)
//jp _MMgetWinPage
uint16_t MMgetWinPage(uint8_t w) __naked{
	w;
__asm;
	jp MMDRVSTART+06
__endasm;
}
	
// +09 uint8_t MMgetWinFlags(uint8_t w)
//jp _MMgetWinFlags
uint8_t MMgetWinFlags(uint8_t w) __naked{
	w;
__asm;
	jp MMDRVSTART+09
__endasm;
}
	
// +12 mm_win_d* MMgetWinD(uint8_t w)
//jp _MMgetWinD
mm_win_d* MMgetWinD(uint8_t w) __naked{
	w;
__asm;
	jp MMDRVSTART+12
__endasm;
}
	
// +15 uint16_t MMgetPagesCount()
//jp _MMgetPagesCount
uint16_t MMgetPagesCount() __naked{
__asm;
	jp MMDRVSTART+15
__endasm;
}

// +18 uint8_t MMGetPageFlags(uint16_t page)
//jp _MMGetPageFlags
uint8_t MMGetPageFlags(uint16_t page) __naked{
	page;
__asm;
	jp MMDRVSTART+18
__endasm;
}
	
// +21 uint8_t MMSetPageWin(uint16_t page, uint8_t win)
//jp _MMSetPageWin
uint8_t MMSetPageWin(uint16_t page, uint8_t win) __naked{
	page;win;
__asm;
	jp MMDRVSTART+21
__endasm;
}
	
// +24 uint16_t MMgetPagesCountROM()
//jp _MMgetPagesCountROM
uint16_t MMgetPagesCountROM() __naked{
__asm;
	jp MMDRVSTART+24
__endasm;
}

// +27 uint8_t MMSetPageWinROM(uint16_t page, uint8_t win)
//jp _MMSetPageWinROM
uint8_t MMSetPageWinROM(uint16_t page, uint8_t win) __naked{
	page;win;
__asm;
	jp MMDRVSTART+27
__endasm;
}
