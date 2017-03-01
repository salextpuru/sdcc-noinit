LIBNAME=libps2.lib

HSFILES=ps2_const.hS

OBJS=ps2_s.rel

$(LIBDIR)/$(LIBNAME): $(LIBNAME)
	install -m 0666 -D $(LIBNAME) $(LIBDIR)/$(LIBNAME)

$(LIBNAME):$(HSFILES) $(OBJS)
	$(CCLIB) a $(LIBNAME) *.rel

main.rel:
	$(CC) -c $(COPTS) main.c

%.rel:%.c
	$(CC) -c $(COPTS) $<

%.rel:%.s
	$(AS) -l -s -o $@ $<

%.hS:%.h
	$(S2HS) $< $@

crt0.s: templates/crt0.s_tmpl
	ga_abs $< $@ $(CLOC) $(SSIZE)

clean: 
	rm -f *.lib *.lst *.sym *.exp *.bin *.map *.mem *.lnk *.ihx *.rel *.rst *.asm *.bin crt0.s *.rel *.hS *.\$$C
