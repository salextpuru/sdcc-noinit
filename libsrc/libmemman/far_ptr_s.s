;-------------------------------------------------

;-------------------------------------------------
        .module far_ptr_s
	.area	_CODE
;-------------------------------------------------
.globl	_MMgetWinPage
.globl	_MMSetPageWin

;  адрес на стеке
;
;
.globl	far_jump
far_jump:
	push	ix
	ld	ix,#4
	add	ix,sp
	
	ld	a,01(ix)
	rlca
	rlca
	and	#3	; Окно памяти
	
	;// uint16_t MMgetWinPage(uint8_t w);
	;// Store page in win A
	push	af
	push	af
	inc	sp
	call	_MMgetWinPage
	inc	sp
	pop	af
	;// RET
	push	af	;// old win A
	inc	sp
	push	hl	;// old page in HL

	;// Set page in A to needs
	;// uint8_t MMSetPageWin(uint16_t page, uint8_t win);
	push	af
	inc	sp
	ld	h,03(ix) ;; A3
	ld	l,02(ix) ;; A2
	push	hl
	call	_MMSetPageWin
	pop	hl
	inc	sp

	;// Call
	inc	sp
	ld	hl,#far_jump_ret
	push	hl
	ld	h,01(ix) ;; A1
	ld	l,00(ix) ;; A0
	push	hl
	ret		;// CALL
	;// 
far_jump_ret:
	;// Set old page
	call	_MMSetPageWin
	;//	RET
	pop	hl
	inc	sp
	;
	pop	ix
	ret
;-------------------------------------------------
