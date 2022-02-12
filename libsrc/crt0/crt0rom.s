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
	.org	0x38
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
	;; Set stack pointer directly above top of memory.
	ld	sp,#stack_top
	;; Initialise global variables
	call	gsinit
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
stack:
	.ds	__SSIZE
stack_top:
