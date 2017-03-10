#include <stdint.h>

static void helper()__naked{
__asm;
	;//
	zifi_command_reg	= 0xC7EF
	zifi_error_reg		= 0xC7EF
	zifi_data_reg		= 0xBFEF
	zifi_input_fifo_status	= 0xC0EF
	zifi_output_fifo_status	= 0xC1EF
	;//
	cmd_clear_input_fifo	= 1
	cmd_clear_output_fifo	= 2
__endasm;
}


uint8_t zifi_uart_init()__naked{
__asm;
	ld	bc,#zifi_command_reg
	ld      de,#0xfff1
	;//
	out     (c),e           ;// 0xf1 - Set API 1
	out     (c),d           ;// 0xFF - Get Version
	;//
	in      a,(c)
	cp      #0xff
	jr	z, zifi_uart_init_error
	;//
	ld      a,#(cmd_clear_input_fifo + cmd_clear_output_fifo)
	out     (c),a           ;// Clear FIFOs
	;//
	ld	l,#0x00
	ret

zifi_uart_init_error:
	ld	l,#0xFF
	ret
__endasm;
}

uint8_t zifi_uart_read(void* buf, uint8_t size)__naked{
__asm;
	push	ix
	ld	ix,#0004
	add	ix,sp
	;//
	ld	l,0(ix)
	ld	h,1(ix)
	ld	e,2(ix)
	ld	d,e ;// d=e=size
	;// is bytes in fifo?
zifi_uart_read_loop:
	ld	bc,#zifi_input_fifo_status
	in	a,(c)
	or	a
	jr	z, zifi_uart_read_end
	;// read byte
	ld	bc,#zifi_data_reg
	in	a,(c)
	ld	(hl),a
	inc	hl
	dec	e
	jr	nz,zifi_uart_read_loop
	;//
zifi_uart_read_end:
	;// recieved size = d - e
	ld	a,d
	sub	e
	;//
	pop	ix
	ret
__endasm;
}

uint8_t zifi_uart_write(void* buf, uint8_t size)__naked{
__asm;
	push	ix
	ld	ix,#0004
	add	ix,sp
	;//
	ld	l,0(ix)
	ld	h,1(ix)
	ld	e,2(ix)
	ld	d,e ;// d=e=size
	;// is bytes in fifo?
zifi_uart_write_loop:
	ld	bc,#zifi_input_fifo_status
	in	a,(c)
	or	a
	jr	z, zifi_uart_write_end
	;// write byte
	ld	bc,#zifi_data_reg
	ld	a,(hl)
	out	(c),a
	inc	hl
	dec	e
	jr	nz,zifi_uart_write_loop
	;//
zifi_uart_write_end:
	;// recieved size = d - e
	ld	a,d
	sub	e
	;//
	pop	ix
	ret
__endasm;
}
