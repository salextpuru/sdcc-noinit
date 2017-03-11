#include <zxmc_uart.h>
#include <stdint.h>

static void helper()__naked{
__asm;
	;// Data
	RG_DAT=	0xF8EF
	;// Speed
	RG_DLL=	0xF8EF
	RG_DLM=	0xF9EF
	;// Controls
	RG_FCR=	0xFAEF
	RG_LCR=	0xFBEF
	RG_MCR=	0xFCEF
	RG_LSR=	0xFDEF
	RG_MSR=	0xFEEF
	RG_SPR=	0xFFEF
__endasm;
}

static uint8_t zxmc_uart_init()__naked{
__asm;
	;// Set visible DLL DLM
	ld	bc,#RG_LCR
	ld	a,#0x83
	out	(c),a
	;// Set default speed 115200
	ld	bc,#RG_DLM
	ld	a,#0x01
	out	(c),a
	dec 	b
	ld	a,#0x00
	out	(c),a
	;// for check
	in	a,(c)
	cp	#0x00
	jr	nz, zxmc_uart_init_error
	;//
zxmc_uart_init_finalize:
	;// Set visible Data
	ld	bc,#RG_LCR
	ld	a,#0x03
	out	(c),a
	;// Clear
	ld	bc,#RG_FCR
	ld	a,#0x07
	out	(c),a
	xor	a
	out	(c),a
	;// Ok
	ld	l,#0x00
	ret
	;// Error
zxmc_uart_init_error:
	ld	l,#0xFF
	ret
__endasm;
}

static void zxmc_uart_setbauds_asm(uint16_t dl)__naked{
	dl;
__asm;
	pop	bc
	pop	hl
	push	hl
	push	bc

	;// Set visible DLL DLM
	ld	bc,#RG_LCR
	ld	a,#0x83
	out	(c),a
	;// Set speed 
	ld	bc,#RG_DLM
	ld	a,h
	out	(c),a
	dec 	b
	ld	a,l
	out	(c),a
	jr	zxmc_uart_init_finalize
__endasm;
}

static uint8_t	zxmc_uart_setbauds(uint32_t bps){
	uint16_t	dl;
	if( bps == 256000UL){
		// Extra speed
		dl=0;
	}else if(bps > 115200UL){
		// Error!
		return(0xFF);
	}
	else{
		dl = 115200UL / bps;
	}
	zxmc_uart_setbauds_asm(dl);
	return(0);
}

static uint8_t zxmc_uart_read(void* buf, uint8_t size)__naked{
	buf;size;
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
zxmc_uart_read_loop:
	ld	bc,#RG_LSR
	in	a,(c)
	and	#0x01
	jr	z, zxmc_uart_read_end
	;// read byte
	ld	bc,#RG_DAT
	in	a,(c)
	ld	(hl),a
	inc	hl
	dec	e
	jr	nz,zxmc_uart_read_loop
	;//
zxmc_uart_read_end:
	;// recieved size = d - e
	ld	a,d
	sub	e
	;//
	pop	ix
	ret
__endasm;
}

static uint8_t zxmc_uart_write(void* buf, uint8_t size)__naked{
	buf;size;
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
zxmc_uart_write_loop:
	ld	bc,#RG_LSR
	in	a,(c)
	and 	#0x20 ;// Very big question ??
	jr	nz, zxmc_uart_write_end
	;// write byte
	ld	bc,#RG_DAT
	ld	a,(hl)
	out	(c),a
	inc	hl
	dec	e
	jr	nz,zxmc_uart_write_loop
	;//
zxmc_uart_write_end:
	;// recieved size = d - e
	ld	a,d
	sub	e
	;//
	pop	ix
	ret
__endasm;
}

static zxuart zxmc_uart_dsc = {
	.init = zxmc_uart_init,
	.setbauds = zxmc_uart_setbauds,
	.read = zxmc_uart_read,
	.write = zxmc_uart_write
};

zxuart* zxmc_uart()__naked{
__asm;
	ld	hl,#_zxmc_uart_dsc
	ret
__endasm;
}
