	;// Only for Memor Managers!
	; Global config include
	.include /autoconfig.asm/
	;
        .module crt0
	;
	.area _CABS (ABS)
	.area _DABS (ABS)
        ; Entry POINT
        .area _CODE
        
        ;// +00 void MMInit();
        .globl _MMInit
        jp _MMInit

	;// +03 mm_win_d* __MMgetMemWinsD();
	.globl ___MMgetMemWinsD
	jp ___MMgetMemWinsD
	
	;// +06 uint16_t MMgetWinPage(uint8_t w);
	.globl _MMgetWinPage
	jp _MMgetWinPage
	
	;// +09 uint8_t MMgetWinFlags(uint8_t w);
	.globl _MMgetWinFlags
	jp _MMgetWinFlags
	
	;// +12 mm_win_d* MMgetWinD(uint8_t w);
	.globl _MMgetWinD
	jp _MMgetWinD
	
	;// +15 uint16_t MMgetPagesCount();
	.globl _MMgetPagesCount
	jp _MMgetPagesCount
	
	;// +18 uint8_t MMGetPageFlags(uint16_t page);
	.globl _MMGetPageFlags
	jp _MMGetPageFlags
	
	;// +21 uint8_t MMSetPageFlags(uint16_t page, uint8_t flags);
	.globl _MMSetPageFlags
	jp _MMSetPageFlags
	
	;// +24 uint8_t MMSetPageWin(uint16_t page, uint8_t win);
	.globl _MMSetPageWin
	jp _MMSetPageWin
	
	;// +27 uint16_t MMgetPagesCountROM();
	.globl _MMgetPagesCountROM
	jp _MMgetPagesCountROM

	;// +30 uint8_t MMSetPageWinROM(uint16_t page, uint8_t win);
	.globl _MMSetPageWinROM
	jp _MMSetPageWinROM
	
	;// +33 uint8_t MMgetFreePage(uint16_t* page);
	.globl _MMgetFreePage
	jp _MMgetFreePage
	
	;// +36 uint8_t MMuseFreePage(uint16_t* page);
	.globl _MMuseFreePage
	jp _MMuseFreePage
	
	;// +39 uint8_t MMfreePage(uint16_t page);
	.globl _MMfreePage
	jp _MMfreePage
	
        ; Library
        .area _HOME
        .area _CONST
        .area _DATA
        ;
	.area _INITIALIZED
	;
	.area _GSINIT
gs_init:
	; all run-time initializers
	.area _GSFINAL
	ret
	;
	.area _HEAP
	.area _HEAP_END
        ;
        .area _BSEG
        .area _BSS
	;
	.area _INITIALIZER
	;
