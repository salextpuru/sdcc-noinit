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
        call _MMInit

	;// +03 mm_win_d* __MMgetMemWinsD();
	call ___MMgetMemWinsD
	
	;// +06 uint16_t MMgetWinPage(uint8_t w);
	call _MMgetWinPage
	
	;// +09 uint8_t MMgetWinFlags(uint8_t w);
	call _MMgetWinFlags
	
	;// +12 mm_win_d* MMgetWinD(uint8_t w);
	call _MMgetWinD
	
	;// +15 uint16_t MMgetPagesCount();
	call _MMgetPagesCount
	
	;// +18 uint8_t MMGetPageFlags(uint16_t page);
	call _MMGetPageFlags
	
	;// +21 uint8_t MMSetPageWin(uint16_t page, uint8_t win);
	call _MMSetPageWin
	
	;// +24 uint16_t MMgetPagesCountROM();
	call _MMgetPagesCountROM

	;// +27 uint8_t MMSetPageWinROM(uint16_t page, uint8_t win);
	call _MMSetPageWinROM

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
