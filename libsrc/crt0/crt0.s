	; Global config include
	.include /autoconfig.asm/
	;
        .module crt0
	;
	.area _CABS (ABS)
	.area _DABS (ABS)
	;
        .globl _main
	; Start of program
        .area _CODE
	.globl s__INITIALIZER
        ; Disable interrupt ?
        .if eq,__DISTART
        di
        .endif

        ; Caller stack ?
        .if eq,__CALLERSTACK
        ld	(sp_store),sp
        ld	sp,#(s__INITIALIZER+__SSIZE)
        .endif
        ; run-time init
        call	gs_init
        ; call main()
        call	_main

        ; Restore stack
        .if eq,__CALLERSTACK
        ld	sp,(sp_store)
        .endif

	; Enable interrupt ?
        .if eq,__DISTART
        ei
        .endif
	ret

        ; Shared Library Descriptors
	.globl __shared_links_begin
	.globl __shared_links_end

        .area _SHARED_LINKS
__shared_links_begin:
        .area _SHARED_LINKS_END
__shared_links_end:
        ;
        .area _HOME
        .area _CONST
        .area _DATA
        ;
	.if eq,__CALLERSTACK
sp_store:
	.dw	0
	.endif
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
	; Here is stack!
	; __SSIZE bytes
