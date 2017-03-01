LIBNAME=libim2.lib

OBJS=im2.rel

$(LIBDIR)/$(LIBNAME): $(LIBNAME)
	install -m 0666 -D $(LIBNAME) $(LIBDIR)/$(LIBNAME)

$(LIBNAME): $(OBJS)
	$(CCLIB) a $(LIBNAME) *.rel

main.rel:
	$(CC) -c $(COPTS) main.c

%.rel:%.c
	$(CC) -c $(COPTS) $<

%.rel:%.s
	$(AS) -l -s -o $@ $<

clean: 
	rm -f *.lib *.lst *.sym *.exp *.bin *.map *.mem *.lnk *.ihx *.rel *.rst *.asm *.bin crt0.s *.rel *.hS *.\$$C
