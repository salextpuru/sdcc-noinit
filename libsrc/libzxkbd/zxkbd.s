	;; ZX Keyboard module
        .module zxkbd
	.area	_CODE
; Sizes etc
scan_table_size=8
; Output buffer (getchar())
buffer_size=8
; Timeout in 20ms
scan_timeout=5

; Bits
rus_bit=1
shift_bit=2

	.globl _kbd_scan
	.globl _scan_codes
	.globl _scan_timers

	; it calls every 1/50 set
_kbd_scan:
kbd_scan:
	push	ix
	ld	ix,#scan_codes
	ld	bc,#0xFEFE
	;
kbd_scan_loop:
	; Skip ?
	ld	a,scan_table_size(ix)
	or	a
	jr	nz, kbd_scan_dectimer
	; read
	in	a,(c)
	and	#0x1F
	ld	(ix),a
	; pressed ?
	cp	#0x1F
	jr	z, kbd_scan_skip
	ld	a, #scan_timeout
	ld	scan_table_size(ix),a
	jr	kbd_scan_skip
	; decrement timeout
kbd_scan_dectimer:
	dec	a
	ld	scan_table_size(ix),a
	; go to next line
kbd_scan_skip:
	; next line
	inc	ix
	; left shift with carry
	scf ; CY=1
	rl	b
	; if all lines was requested CY=0 after shift,
	; else - next loop
	jr	c,kbd_scan_loop
	;
	pop	ix
	ret

	.area	_DATA
	; Scan-table (8 scan-codes)
_scan_codes:
scan_codes:
	.ds scan_table_size
	; Timers on scan-codes
_scan_timers:
scan_timers:
	.ds scan_table_size
	; mode ( rus/lat, upper/lower )
zxkbd_mode:
	.ds 1
	;
zxkbd_buf:
	.ds buffer_size
;--------------------------------------------------------
; info
;-------------------------------------------------------
;		Data in(port)
; Port	 Adr   0  1  2  3  4
;
; #F7FE  A11   1  2  3  4  5
; #FBFE  A10   Q  W  E  R  ô
; #FDFE  A9    A  S  D  F  G
; #FEFE  A8   CS  Z  X  ó  V
; #EFFE  á12   0  9  8  7  6
; #DFFE  A13   P  O  I  U  Y
; #BFFE  A14   L  K  J  H  Enter
; #7FFE  A15   SS SP M  N  B
;-------------------------------------------------------
;		Data in(port) ( ÿ è ü ö à â ³ )
; Port	 Adr   0  1  2  3  4
;
; #F7FE  A11   1  2  3  4  5
; #FBFE  A10   ê  ã  õ  ë  å
; #FDFE  A9    æ  ù  ÷  á  ð
; #FEFE  A8   CS  ñ  þ  ó  í
; #EFFE  á12   0  9  8  7  6
; #DFFE  A13   ú  ý  û  ç  î
; #BFFE  A14   ä  ì  ï  ò  Enter
; #7FFE  A15   SS SP é  ô  ø
;-------------------------------------------------------
