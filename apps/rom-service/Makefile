# Config files
include *.mk

# Generate lib specificaton ( if LIBS variable defined in build.mk )
ifdef LIBS
LIBSMAKE:=$(addprefix $(LIBDIR)/, $(LIBS:=.lib) )
LIBSLINK:=$(addprefix -l , $(LIBSMAKE) )
endif

# Generate all targets
all: $(APPDIR)/$(APP).bin
	@echo "all ok"

$(APPDIR)/$(APP)%:$(APP)%
	install -m 0666 -D $< $@

#ZSIZE:=$$(( 16384 - `du -b "$(APP).bin" | awk '{print $$1}'` ))

# Binary image
$(APP).bin: autoconfig.asm crt0.rel $(OBJ) $(LIBSMAKE)
	$(LD) -imjwx -b _CODE=0x0080 -b _DATA=$(STARTDATA) -o $(APP) crt0.rel $(OBJ) $(LIBSLINK) > /dev/null
	@if [[ -f $(APP).ihx ]]; then \
	echo "Hex generated: "$(APP).ihx ; \
	else \
	"Hex generated FAIL! Exit 1: "$(APP).ihx ; \
	exit 1 ; \
	fi
	$(HEX2BIN) -s 0x0000 $(APP).ihx 2>&1 >/dev/null
	$(DZ80) -m=0x0000 $(APP).bin > $(APP)_d.asm
	echo $(ZSIZE)
	dd if=$(APP).bin of=$(APP).bin.tap bs=16384 count=1
	mv -f $(APP).bin.tap $(APP).bin

#	dd if=/dev/zero of=z.zero bs=$(ZSIZE) count=1
#	cat $(APP).bin z.zero > $(APP).bin.tap
#	rm -f z.zero
#	mv -f $(APP).bin.tap $(APP).bin

%.rel:%.c
	$(CC) -c $(COPTS) $<

%.rel:%.s
	$(AS) $(ASOPTS) -l -s -o $@ $<

crt0.rel: $(CRT0PATH)
	$(AS) $(ASOPTS) -l -s -o $@ $<

autoconfig.asm:
	$(AUTOCONFIG) config.mk $@

clean:
	rm -rf *.rel *.lst *.sym *.exp *.bin *.map *.mem *.lnk *.ihx *.rel *.rst *.asm *.bin *.rel *.hS *.\$$C *.lk *.noi *.tap

load:
	stty -F $(LDEVICE) $(LSPEED) raw -crtscts
	sleep 1
	cat $(APP).\$$C  > $(LDEVICE)
