# Config files
include *.mk

all:
	make -f Makefile.mklib
	@for i in $(MMDRV) ; do \
	echo "---- Compile driver $$i ----" ; \
	make DRV=$$i -f Makefile.mkdrv ; \
	done

clean:
	make -f Makefile.mklib clean
	@for i in $(MMDRV) ; do \
	echo "---- Clean driver $$i ----" ; \
	make DRV=$$i -f Makefile.mkdrv clean ; \
	done
