# Library Name
LIBNAME=libwcplugin.lib

OBJS=keyfunc.rel  wccurhide.rel  wccurshow.rel  wcgadrw.rel \
     wcintpl.rel  wcmng0pl.rel  wcmng8pl.rel  wcmngcpl.rel \
     wcprint.rel  wcprsrw.rel  wcprwow.rel  wcrresb.rel \
     wcwaitforframe.rel  wcynmenu.rel wcpluginsp.rel \
     wcget0page.rel wcget1page.rel wcget2page.rel wcget3page.rel \
     wcgetabortflag.rel wcgetenterflag.rel wcgettimer.rel \
     wcistr2.rel wcistr2ind.rel wctxtpr.rel wcmezz.rel wcgedpl.rel \
     wcscrlwow.rel wcloadsave512.rel wcgipagpl.rel wctentry.rel \
     wcadir.rel wcstream.rel wcfindnext.rel
     
$(LIBDIR)/$(LIBNAME): $(LIBNAME)
	install -m 0666 -D $(LIBNAME) $(LIBDIR)/$(LIBNAME)

$(LIBNAME): $(OBJS)
	$(CCLIB) a $(LIBNAME) *.rel

main.rel:
	$(CC) -c $(COPTS) main.rel

%.rel:%.c
	$(CC) --disable-warning 221 -c $(COPTS) $<

%.rel:%.s
	$(AS) -l -s -o $@ $<

%.hS:%.h
	$(S2HS) $< $@

clean: 
	rm -f *.lib *.lst *.sym *.exp *.bin *.map *.mem *.lnk *.ihx *.rel *.rst *.asm *.bin crt0.s *.rel *.hS *.\$$C
