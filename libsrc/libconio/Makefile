LIBNAME=libconio.lib

HSFILES=conio_const.hS

OBJS= conio_s.rel conio.rel conio_var.rel  koi8r-8x8.rel
#printf.rel

$(LIBDIR)/$(LIBNAME): $(LIBNAME)
	install -m 0666 -D $(LIBNAME) $(LIBDIR)/$(LIBNAME)

$(LIBNAME): $(HSFILES)  $(OBJS)
	$(CCLIB) a $(LIBNAME) *.rel

main.rel:
	$(CC) -c $(COPTS) main.c

%.rel:%.c
	$(CC) -c $(COPTS) $<

%.rel:%.s
	$(AS) -l -s -o $@ $<

%.hS:%.h
	$(S2HS) $< $@

clean: 
	rm -f *.lib *.lst *.sym *.exp *.bin *.map *.mem *.lnk *.ihx *.rel *.rst *.asm *.bin crt0.s *.rel *.hS *.\$$C
