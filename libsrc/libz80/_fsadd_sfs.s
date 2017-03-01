;-----------------------------------------------------------------------
; C-compatible routines for working with floating-point numbers
;-----------------------------------------------------------------------
        .module float
	.area	_CODE
;-----------------------------------------------------------------------
; Float	- packed float on IEEE 754, 4 bytes, single precision
;
; Unpack- unpacked float, 5 bytes
;	+0 - exponent
;	+1..+4 - mantissa (signed)
;-----------------------------------------------------------------------
; Useful macros
;-----------------------------------------------------------------------

; Init IX to first stack parametr
.macro sp_ix_init
	push	ix
	ld	ix,#0004
	add	ix,sp
.endm

; Done proc. Restore IX and return
.macro sp_ix_done
	pop	ix
	ret
.endm

; store iy and allocate size bytes on stack
; corrupt bc
.macro sp_alloc_iy size
	push	iy
	ld	iy,#-size
	add	iy,sp
	ld	sp,iy
	ld	bc,#size
	push	bc
.endm

; free stack and restore iy
.macro sp_free_iy
	pop	iy
	add	iy,sp
	ld	sp,iy
	pop	iy
.endm

; Store unpack to (iy+n)
.macro store_unpack_iy n
	ld	n+0(iy),a
	ld	n+4(iy),d
	ld	n+3(iy),e
	ld	n+2(iy),h
	ld	n+1(iy),l
.endm

; Restore unpack mantissa (iy+n)
.macro get_mant_unpack_iy n
	ld	d,n+4(iy)
	ld	e,n+3(iy)
	ld	h,n+2(iy)
	ld	l,n+1(iy)
.endm
;-----------------------------------------------------------------------
; C-function a+b
;-----------------------------------------------------------------------
___fsadd::
;_fsadd::
	sp_ix_init
	; if a==0 return b
	call	_fsadd_geta
	call	flo_zero
	jr	nz,_fsadd_a_nz
_fsadd_retb:
	call	_fsadd_getb
	sp_ix_done
	;-- exit b --
	;
_fsadd_a_nz:
	; if b==0 return a
	call	_fsadd_getb
	call	flo_zero
	jr	nz,_fsadd_b_nz
_fsadd_reta:
	call	_fsadd_geta
	sp_ix_done
	;-- exit a --
	;
_fsadd_b_nz:
	; Allocate memory for 3 unpack
	; iy+00 - result (unpack)
	; iy+05 - a (unpack)
	; iy+10 - b (unpack)
	sp_alloc_iy 15
	; unpack a
	call	_fsadd_geta
	call	unpack
	store_unpack_iy 5
	; unpack b
	call	_fsadd_getb
	call	unpack
	store_unpack_iy 10

	; Exponent compare
	ld	a,5(iy)	; exp(a)
	sub	10(iy)	; exp(b)

	; ? exp(a) == exp(b)
	jr	z,_fsadd_shifta

	; ? exp(a)<exp(b)
	jr	c,_fsadd_alower
	cp	a,#24

	; if exp(a)-exp(b) < 24 then continue
	jr	c,_fsadd_shiftb
	; return (a) if b too low
	sp_free_iy
	jr	_fsadd_reta
	;
_fsadd_alower:
	neg
	cp	a,#24
	; if exp(b)-exp(a) < 24 then continue
	jr	c,_fsadd_shifta
	; return (b) if a too low
	sp_free_iy
	jr	_fsadd_retb

_fsadd_shiftb:
	; Get mant(a) to dehl
	get_mant_unpack_iy	10
	call	shift_flo
	; add mantissas
	ld	a,6(iy)
	add	a,l
	ld	1(iy),a
	ld	a,7(iy)
	adc	a,h
	ld	2(iy),a
	ld	a,8(iy)
	adc	a,e
	ld	3(iy),a
	ld	a,9(iy)
	adc	a,d
	ld	4(iy),a
	; exponent
	ld	a,5(iy)
	ld	0(iy),a
	;
	jr	_fsadd_norm_result

_fsadd_shifta:
	; Get mant(a) to dehl
	get_mant_unpack_iy	5
	call	shift_flo
	; add mantissas
	ld	a,11(iy)
	add	a,l
	ld	1(iy),a
	ld	a,12(iy)
	adc	a,h
	ld	2(iy),a
	ld	a,13(iy)
	adc	a,e
	ld	3(iy),a
	ld	a,14(iy)
	adc	a,d
	ld	4(iy),a
	; exponent
	ld	a,10(iy)
	ld	0(iy),a

	; Normalize resutl
_fsadd_norm_result:
	get_mant_unpack_iy	0
	; Store signum bit to B
	ld	b,d
	; Pozitive or negative ?
	bit	7,d
	; mant=-mant
	call	nz,mant_neg_d
_fsadd_norm_pos:
	ld	a,d
	or	a,e
	or	a,h
	or	a,l
	jr	z, ret_zero ; Return ZERO
	
	; Do it needs shift right ?
do_need_shift_right:
	ld	a,d
	or	a
	jr	z, do_need_shift_left
	inc	0(iy)
	; Right shift
	srl	d
	rr	e
	rr	h
	rr	l
	jr	do_need_shift_right
	;
do_need_shift_left:
	; Do it needs shift left ?
	bit	7,e
	jr	nz, pack_result
	dec	0(iy)
	; Left shift
	sla	l
	rl	h
	rl	e
	jr	do_need_shift_left
	;
pack_result:
	; sign to D
	ld	a,b
	and	a,#0x80
	ld	d,a
	; exponent
	ld	a,0(iy)
	sla	e ; drop hidden bit
	srl	a ; bit 0 to CY
	rr	e ; CY to bit 7 of E
	or	a,d ; add exponent to D
	ld	d,a
	; EXIT
ret_zero:
	sp_free_iy
	sp_ix_done ; return

; get a-float from stack
_fsadd_geta:
	ld	d,3(ix)
	ld	e,2(ix)
	ld	h,1(ix)
	ld	l,0(ix)
	ret
; get b-float from stack
_fsadd_getb:
	ld	d,7(ix)
	ld	e,6(ix)
	ld	h,5(ix)
	ld	l,4(ix)
	ret
;-----------------------------------------------------------------------
; Get exponent
; in:	dehl - float
;
; out:	a - exponent
flo_exp:
	ld	a,e
	rl	a
	ld	a,d
	rl	a
	ret

; Get mantissa
; in:	dehl - float
;	a - exponent
;
; out:	ehl (hi..lo) - integer24
flo_mant:
	or a
	jr	z,flo_mant_zexp
	; nonzero
	ld	a,e
	or	#0x80
	ld	e,a
	ret
	; zero
flo_mant_zexp:
	rl	l
	rl	h
	rl	e
	;
	ret

; Check ZERO
; in:	dehl - float
; out:	Z - zero or no
flo_zero:
	ld	a,d
	and	a,#0x7F ; Ignore SIGN!
	or	a,e
	or	a,h
	or	a,l
	ret

; Inverse mant sign
; in:	ehl (hi..lo) - integer24
; out:	-dehl (hi..lo) - integer24
mant_neg:
	;
	ld	d,#00
mant_neg_d:
	ld	c,#00
	;
	ld	a,c
	sub	a,l
	ld	l,a
	;
	ld	a,c
	sbc	a,h
	ld	h,a
	;
	ld	a,c
	sbc	a,e
	ld	e,a
	;
	ld	a,c
	sbc	a,d
	ld	d,a
	;
	ret

; Unpack float
unpack:
	call	flo_exp
	ld	b,a
	call	flo_mant
	bit	7,d
	jr	z,unpack_plus
	call	mant_neg
	ld	a,b
	ld	d,#0xFF
	ret

unpack_plus:
	ld	a,b
	ld	d,#00
	ret

; Fast right shift dehl on a bits (a = 0..23)
shift_flo:
	; shift 8 bits
	cp 	a,#8
	jr	c,shift_floa
	sub	a,#8
	ld	l,h
	ld	h,e
	ld	e,d
	jr	shift_flo
	;
shift_floa:
	; shift 1 bit
	or	a
	ret	z
	sra	d
	rr	e
	rr	h
	rr	l
	dec	a
	jr	shift_floa
;
