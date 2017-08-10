# Config files
include *.mk

$(LIBDIR)/$(LIBNAME): $(LIBNAME)
	install -m 0666 -D $(LIBNAME) $(LIBDIR)/$(LIBNAME)

$(LIBNAME): $(HSFILES)  $(OBJS)
	$(CCLIB) a $(LIBNAME) *.rel

%.rel:%.c *.h
	$(CC) -c $(COPTS) $<

%.rel:%.s
	$(AS) -g -l -s -o $@ $<

clean:
	rm -f *.lib *.lst *.sym *.exp *.bin *.map *.mem *.lnk *.ihx *.rel *.rst *.asm *.bin crt0.s *.rel *.hS *.\$$C
