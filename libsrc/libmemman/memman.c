/**
 * MMDRVSTART -  начальный адрес драйвера
 */
#include "memman.h"

// +00
//jp _MMInit
void MMInit() __naked{
__asm;
	jp MMDRVSTART+00
__endasm;
}

// +03
//jp ___MMgetMemWinsD
mm_win_d* __MMgetMemWinsD() __naked{
__asm;
	jp MMDRVSTART+03
__endasm;
}
	
// +06
//jp _MMgetWinPage
uint16_t MMgetWinPage(uint8_t w) __naked{
	w;
__asm;
	jp MMDRVSTART+06
__endasm;
}
	
// +09
//jp _MMgetWinFlags
uint8_t MMgetWinFlags(uint8_t w) __naked{
	w;
__asm;
	jp MMDRVSTART+09
__endasm;
}
	
// +12
//jp _MMgetWinD
mm_win_d* MMgetWinD(uint8_t w) __naked{
	w;
__asm;
	jp MMDRVSTART+12
__endasm;
}
	
// +15
//jp _MMgetPagesCount
uint16_t MMgetPagesCount() __naked{
__asm;
	jp MMDRVSTART+15
__endasm;
}

// +18
//jp _MMGetPageFlags
uint8_t MMGetPageFlags(uint16_t page) __naked{
	page;
__asm;
	jp MMDRVSTART+18
__endasm;
}

// +21
//jp _MMSetPageFlags
uint8_t MMSetPageFlags(uint16_t page, uint8_t flags) __naked{
	page;flags;
__asm;
	jp MMDRVSTART+21
__endasm;
}
	
// +24
//jp _MMSetPageWin
uint8_t MMSetPageWin(uint16_t page, uint8_t win) __naked{
	page;win;
__asm;
	jp MMDRVSTART+24
__endasm;
}
	
// +27
//jp _MMgetPagesCountROM
uint16_t MMgetPagesCountROM() __naked{
__asm;
	jp MMDRVSTART+27
__endasm;
}

// +30
//jp _MMSetPageWinROM
uint8_t MMSetPageWinROM(uint16_t page, uint8_t win) __naked{
	page;win;
__asm;
	jp MMDRVSTART+30
__endasm;
}


// +33
//jp _MMgetFreePage
uint8_t MMgetFreePage(uint16_t* page) __naked{
	page;
__asm;
	jp MMDRVSTART+33
__endasm;
}

// +36
//jp _MMuseFreePage
uint8_t MMuseFreePage(uint16_t* page) __naked{
	page;
__asm;
	jp MMDRVSTART+36
__endasm;
}

// +39
//jp _MMfreePage
uint8_t MMfreePage(uint16_t page)  __naked{
	page;
__asm;
	jp MMDRVSTART+39
__endasm;
}
