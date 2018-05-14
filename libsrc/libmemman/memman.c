/**
 * MMDRVSTART -  начальный адрес драйвера
 */
#include "memman.h"

// +00 void MMInit()
//call _MMInit
void MMInit() __naked{
__asm;
	call MMDRVSTART+00
	ret
__endasm;
}

// +03 mm_win_d* __MMgetMemWinsD()
//call ___MMgetMemWinsD
mm_win_d* __MMgetMemWinsD() __naked{
__asm;
	call MMDRVSTART+03
	ret
__endasm;
}
	
// +06 uint16_t MMgetWinPage(uint8_t w)
//call _MMgetWinPage
uint16_t MMgetWinPage(uint8_t w) __naked{
	w;
__asm;
	call MMDRVSTART+06
	ret
__endasm;
}
	
// +09 uint8_t MMgetWinFlags(uint8_t w)
//call _MMgetWinFlags
uint8_t MMgetWinFlags(uint8_t w) __naked{
	w;
__asm;
	call MMDRVSTART+09
	ret
__endasm;
}
	
// +12 mm_win_d* MMgetWinD(uint8_t w)
//call _MMgetWinD
mm_win_d* MMgetWinD(uint8_t w) __naked{
	w;
__asm;
	call MMDRVSTART+12
	ret
__endasm;
}
	
// +15 uint16_t MMgetPagesCount()
//call _MMgetPagesCount
uint16_t MMgetPagesCount() __naked{
__asm;
	call MMDRVSTART+15
	ret
__endasm;
}

// +18 uint8_t MMGetPageFlags(uint16_t page)
//call _MMGetPageFlags
uint8_t MMGetPageFlags(uint16_t page) __naked{
	page;
__asm;
	call MMDRVSTART+18
	ret
__endasm;
}
	
// +21 uint8_t MMSetPageWin(uint16_t page, uint8_t win)
//call _MMSetPageWin
uint8_t MMSetPageWin(uint16_t page, uint8_t win) __naked{
	page;win;
__asm;
	call MMDRVSTART+21
	ret
__endasm;
}
	
// +24 uint16_t MMgetPagesCountROM()
//call _MMgetPagesCountROM
uint16_t MMgetPagesCountROM() __naked{
__asm;
	call MMDRVSTART+24
	ret
__endasm;
}

// +27 uint8_t MMSetPageWinROM(uint16_t page, uint8_t win)
//call _MMSetPageWinROM
uint8_t MMSetPageWinROM(uint16_t page, uint8_t win) __naked{
	page;win;
__asm;
	call MMDRVSTART+27
	ret
__endasm;
}
