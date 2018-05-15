# Config files
include *.mk

all: iface_gen autoconfig.asm
	make -f Makefile.mklib
	@for i in $(MMDRV) ; do \
	echo "---- Compile driver $$i ----" ; \
	make DRV=$$i -f Makefile.mkdrv ; \
	done

iface_gen:
	$(SCR)/make_shared_nopaged $(IFACE_H)

autoconfig.asm:
	$(AUTOCONFIG) config.mk $@

clean:
	make -f Makefile.mklib clean
	@for i in $(MMDRV) ; do \
	echo "---- Clean driver $$i ----" ; \
	make DRV=$$i -f Makefile.mkdrv clean ; \
	done
