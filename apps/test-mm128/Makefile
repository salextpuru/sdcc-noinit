# Config files
include *.mk

# Generate lib specificaton ( if LIBS variable defined in build.mk )
ifdef LIBS
LIBSMAKE:=$(addprefix $(LIBDIR)/, $(LIBS:=.lib) )
LIBSLINK:=$(addprefix -l , $(LIBSMAKE) )
endif

# Generate all targets
all: $(APPDIR)/$(APP).bin $(APPDIR)/$(APP).\$$C $(APPDIR)/$(APP)-code.tap $(APPDIR)/$(APP)-basic.tap $(EXTTAPS)
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

$(APP).\$$C: $(APP).bin
	$(BIN2HOB) $(APP).\$$C $(START) $(APP).bin

hob: $(APP).\$$C
	@echo "Hobeta Ok"

$(APP)-code.tap: $(APP).bin
	bin2tap -a `printf "%i" $(START)` -r `printf "%i" $(START)` -o $@ $<

# Нам нужен нестандартный загрузчик. Так создадим ЕГО!
# 20 строка грузит test-mm128 code
# 30 строка грузит mm128.drv code
$(APP)-basic.tap: $(APP).bin
	echo "10 clear 24575" > loader.bas
	echo "20 load \"\" code" >> loader.bas
	echo "30 load \"\" code" >> loader.bas
	echo "40 randomize usr "`printf "%i" $(START)` >> loader.bas
	zmakebas -a 10 -o loader.tap  loader.bas
	cat loader.tap $(APP)-code.tap $(EXTTAPS)  > $@

clean:
	rm -rf *.rel *.lst *.sym *.exp *.bin *.map *.mem *.lnk *.ihx *.rel *.rst *.asm *.bin *.rel *.hS *.\$$C *.lk *.noi *.tap loader.bas

load:
	stty -F $(LDEVICE) $(LSPEED) raw -crtscts
	sleep 1
	cat $(APP).\$$C  > $(LDEVICE)
