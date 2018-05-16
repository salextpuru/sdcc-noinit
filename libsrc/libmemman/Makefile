# Config files
include *.mk

all: crt0shared.asm  iface_shared.asm autoconfig.asm
	make -f Makefile.mklib
	@for i in $(MMDRV) ; do \
	echo "---- Compile driver $$i ----" ; \
	make DRV=$$i -f Makefile.mkdrv ; \
	done

iface_gen: $(SCR)/make_shared_nopaged
	$(SCR)/make_shared_nopaged $(IFACE_H) $(INTLIBNAME)

crt0shared.asm: iface_gen $(SCR)/make_shared_nopaged
	#

iface_shared.asm: iface_gen $(SCR)/make_shared_nopaged
	#

autoconfig.asm:
	$(AUTOCONFIG) config.mk $@

clean:
	make -f Makefile.mklib clean
	@for i in $(MMDRV) ; do \
	echo "---- Clean driver $$i ----" ; \
	make DRV=$$i -f Makefile.mkdrv clean ; \
	done
