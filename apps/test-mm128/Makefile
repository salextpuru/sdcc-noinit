# Config files
include *.mk

# Generate lib specificaton ( if LIBS variable defined in build.mk )
ifdef LIBS
LIBSMAKE:=$(addprefix $(LIBDIR)/, $(LIBS:=.lib) )
LIBSLINK:=$(addprefix -l , $(LIBSMAKE) )
endif

# Generate all targets
all: $(APPDIR)/$(APP).bin $(APPDIR)/$(APP)-code.tap  $(EXTTAPS) exttaps $(APPDIR)/$(APP)-basic.tap
	@echo "all ok"

$(APPDIR)/$(APP)%:$(APP)%
	install -m 0666 -D $< $@

# Binary image
$(APP).bin: autoconfig.asm crt0.rel $(OBJ) $(LIBSMAKE)
	$(LD) -imjwx -b _CODE=$(START) -o $(APP) crt0.rel $(OBJ) $(LIBSLINK) > /dev/null
	@if [[ -f $(APP).ihx ]]; then \
	echo "Hex generated: "$(APP).ihx ; \
	else \
	"Hex generated FAIL! Exit 1: "$(APP).ihx ; \
	exit 1 ; \
	fi
	$(HEX2BIN) -s $(START) $(APP).ihx 2>&1 >/dev/null
	$(BINMAN) $(APP).map $(APP).bin
	$(DZ80) -m=$(START) $(APP).bin > $(APP)_d.asm

%.rel:%.c
	$(CC) -c $(COPTS) $<

%.rel:%.s
	$(AS) $(ASOPTS) -l -s -o $@ $<

crt0.rel: $(CRT0PATH)
	$(AS) $(ASOPTS) -l -s -o $@ $<

autoconfig.asm:
	$(AUTOCONFIG) config.mk $@

$(APP)-code.tap: $(APP).bin
	bin2tap -a `printf "%i" $(START)` -r `printf "%i" $(START)` -o $@ $<

exttaps:
	@for i in $(EXTTAPS) ; do \
	bin2tap -a `printf "%i" $(EXTTAPS_START)` -r `printf "%i" $(EXTTAPS_START)` -o $$i".tap"  $$i ; \
	done
#
#	bin2tap -a `printf "%i" $(EXTTAPS_START)` -r `printf "%i" $(EXTTAPS_START)` -o 

LOADER_BAS="loader.bas~"
# Нам нужен нестандартный загрузчик. Так создадим ЕГО!
# 20 строка грузит test-mm128 code
# 30 строка грузит mm128.drv code
$(APP)-basic.tap: $(APP).bin
	echo "10 clear 24575" > $(LOADER_BAS)
	echo "20 load \"\" code" >> $(LOADER_BAS)
	echo "30 load \"\" code" >> $(LOADER_BAS)
	echo "40 randomize usr "`printf "%i" $(START)` >> $(LOADER_BAS)
	zmakebas -a 10 -o loader.tap $(LOADER_BAS)
	cat loader.tap $(APP)-code.tap > $@
	@for i in $(EXTTAPS) ; do \
	cat $$i".tap" >> $@ ; \
	done

clean:
	rm -rf *.rel *.lst *.sym *.exp *.bin *.map *.mem *.lnk *.ihx *.rel *.rst *.asm *.bin *.rel *.hS *.\$$C *.lk *.noi *.tap *.bas~

load:
	stty -F $(LDEVICE) $(LSPEED) raw -crtscts
	sleep 1
	cat $(APP).\$$C  > $(LDEVICE)
