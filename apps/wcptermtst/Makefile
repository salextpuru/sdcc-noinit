# App name
APP=termtst

LDEVICE=/dev/ttyUSB0
LSPEED=19200


# Config files
include *.mk

# CRT0
CRT0PATH=$(TOP)/libsrc/crt0/$(CRT0WCPLUGIN)

# Object files
OBJ=plugin.rel

# Generate all targets
all: $(APPDIR)/$(APP).wmf
	@echo "all ok"

$(APPDIR)/$(APP)%:$(APP)%
	install -m 0666 -D $< $@

#
$(APP).wmf: plheader.bin $(APP).bin
	cat plheader.bin $(APP).bin > $@

# Binary image
$(APP).bin: autoconfig.asm crt0.rel $(OBJ)
	$(LD) -imjwx -b _CODE=$(START) $(LIBSLINK) -o $(APP) crt0.rel $(OBJ)  > /dev/null
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

# HEADER
plheader.asm:
	$(SCR)/plughdr_1page $@ $(APP)

plheader.rel: plheader.asm
	$(AS) $(ASOPTS) -l -s -o $@ $<

plheader.bin: plheader.rel
	$(LD) -imjwx -b _CODE=$(STARTPLHEADER) $(LIBSLINK) $<  > /dev/null
	@if [[ -f "plheader.ihx" ]]; then \
	echo "Hex generated: "plheader.ihx ; \
	else \
	"Hex generated FAIL! Exit 1: "plheader.ihx ; \
	exit 1 ; \
	fi
	$(HEX2BIN) -s $(STARTPLHEADER) plheader.ihx 2>&1 >/dev/null
	$(DZ80) -m=$(STARTPLHEADER) plheader.bin > plheader_d.asm

clean:
	rm -rf *.rel *.lst *.sym *.exp *.bin *.map *.mem *.lnk *.ihx *.rel *.rst *.asm *.bin *.rel *.hS *.\$$C *.lk *.noi *.tap *.wmf

load:
	stty -F $(LDEVICE) $(LSPEED) raw -crtscts
	sleep 1
	cat $(APP).\$$C  > $(LDEVICE)
