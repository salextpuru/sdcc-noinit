#ifndef WCPLUGINSP_H_INCLUDED
#define WCPLUGINSP_H_INCLUDED

#define	wcentrypoint	0x6006

inline static void wcpluginsp_globals()__naked{
__asm;
	.globl wcplsp_iy_init
	.globl wcplsp_get_a
	.globl wcplsp_get_ix
	.globl wcplsp_get_bc
	.globl wcplsp_get_de
	.globl wcplsp_get_hl

;// Macros
.macro	wcentry
	call	wcentrypoint
.endm

.macro	iy_init
	call	wcplsp_iy_init
.endm

.macro	get_a
	call	wcplsp_get_a
.endm

.macro	get_ix
	call	wcplsp_get_ix
.endm

.macro	get_bc
	call	wcplsp_get_bc
.endm

.macro	get_de
	call	wcplsp_get_de
.endm

.macro	get_hl
	call	wcplsp_get_hl
.endm

;// return
.macro	procret
	pop	ix
	pop	iy
	ret
.endm

;// return
.macro	procretnz
	pop	ix
	pop	iy
	ret	nz
.endm

;// return
.macro	procretz
	pop	ix
	pop	iy
	ret	z
.endm

__endasm;
}


#endif /* WCPLUGINSP_H_INCLUDED */
