	; Global config include
        .module crt0plug
	;
	.area _CABS (ABS)
	.area _DABS (ABS)
	; 
	.globl _entry_code
	.globl _exit_code
	.globl _ext_number
	.globl _file_name_adr
	.globl _active_panel_adr
	.globl _file_len
	;
        .globl _main
	; Start of program
        .area _CODE
	.globl s__INITIALIZER
	; ENTRY
	push	ix
	ld	(_entry_code),a
	ld	(_active_panel_adr),ix
	ld	(_file_name_adr),bc
	;
	ld	(_file_len),hl
	ld	(_file_len+2),de
	;
	ex	af,af' ; '
	ld	(_ext_number),a
        ; run-time init
        call	gs_init
        ; call main()
        call	_main

	; Exit
	ld	a,(_exit_code)
	pop	ix
	ret

	; API call
	

        ; Library
        .area _HOME
        .area _CONST
        .area _DATA
        ; Vars
_entry_code:
	.db	00	; A on entry
_exit_code:
	.db	00	; A on exit
_ext_number:
	.db	00	; Extention number
_file_name_adr:
	.dw	0000	; Open file name adr (char*)
_active_panel_adr:
	.dw	0000	; IX
_file_len:
	.ds	4	; long file len
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
