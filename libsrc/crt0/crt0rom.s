	; Global config include
	.include /autoconfig.asm/
	;;
	.module crt0
	.globl	_main
	;;
	.area	_HEADER (ABS)
	;; Reset vector
	.org 	0x00
	di
	jp	init

	.org	0x08
	reti
	.org	0x10
	reti
	.org	0x18
	reti
	.org	0x20
	reti
	.org	0x28
	reti
	.org	0x30
	reti

	;; // INT (1/50 sec)
	.globl	_irq38
	.org	0x38
	push	af
	push	bc
	push	de
	push	hl
	exx
	ex	af,af' ; '
	push	af
	push	bc
	push	de
	push	hl
	call	_irq38
	pop	hl
	pop	de
	pop	bc
	pop	af
	exx
	ex	af,af' ; '
	pop	hl
	pop	de
	pop	bc
	pop	af
	ei
	reti
	
	;// Maye be placed entry points
	
	;// ...
	
	;// NMI
	.org	0x66
	retn
	
	; 128 byetes
	.org	0x0080
	;//
	;// Compiler feaure
	;//
	.area	_CODE
init:

    ;// ---------------------------------------------------
    ;// PREINIT_CODE FOR KAY/PHOENIX/SCORPION
    ;// SET page 8 to 0xC000
    ld  bc,#0x7FFD
    ld  a,#0x00
    out (c),a
    ld  bc,#0x1FFD
    ld  a,#0x12
    out (c),a
    ;// ---------------------------------------------------
    ;// Now:    ROM - service ROM PAGE
    ;//         RAM - from 0xC000 PAGE 8 (service monitor page)

    ;// Check signature
    ld  hl,#sign_d
    ld  de,#sign_c
sign_check_1:
    ld  a,(de)
    cp  (hl)
    jr  nz, sing_fail ;// signature fail
    inc hl
    inc de
    or  a
    jr  nz,sign_check_1 ;// continue checking
    ;; Signature Ok
    ;; Hot start
    ld a,#1 ;// 1 - hot start from 0x0000
    ld  (_start_type),a
    ld  sp,(sp_store)
    jr  goto_main

sing_fail: ;// Full init memory and start
	;; Set stack pointer directly above top of memory.
	ld	sp,#stack_top
    ld  (sp_store),sp

    ;; Copy Signature to RAM
    ld  hl,#sign_d
    ld  de,#sign_c
sign_copy_1:
    ld  a,(de)
    ld  (hl),a
    inc hl
    inc de
    or  a
    jr  nz, sign_copy_1

	;; Initialise global variables
	call	gsinit
goto_main:
	call	_main
	;//
_loop:
	halt
	jr	_loop

;// new feautures
.globl s__INITIALIZER
.globl s__INITIALIZED
.globl l__INITIALIZER

	.area   _GSINIT
gsinit::
	ld	bc, #l__INITIALIZER
	ld	a, b
	or	a, c
	jr	Z, gsinit_next
	ld	de, #s__INITIALIZED
	ld	hl, #s__INITIALIZER
	ldir
gsinit_next:
	.area   _GSFINAL
	ret

;; Ordering of segments for the linker.
	.area	_HOME
	.area	_CODE
	.area	_INITIALIZER
	.area   _GSINIT
	.area   _GSFINAL

;; // Global DATA
	.area	_DATA
	.area	_INITIALIZED
	.area	_BSEG
	.area   _BSS
	.area   _HEAP
;; //

;; // Constant for checking signature
.area	_CODE
sign_c:
    .ascii   "SINIT"
    .db 0

;; // Signature in data memory
.area	_DATA
sign_d:
    .ascii   "SINIT"
    .db 0

sp_store:
    .dw 0000

;// 0 - hard start from 0x0000
;// 1 - hot start from 0x0000
;// 2 - hard start from NMI
;// 3 - hot start from NMI
.globl _start_type
_start_type:
    .db 00

.area   _BSS
stack:
	.ds	__SSIZE
stack_top:
