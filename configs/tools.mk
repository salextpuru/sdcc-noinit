# Processor type
CPU_TYPE=z80

# Development tools
CC=sdcc -m$(CPU_TYPE) --opt-code-size --nostdinc
LD=sdld$(CPU_TYPE)

CCLIB=sdcclib
AS=sdas$(CPU_TYPE)
DZ80=d$(CPU_TYPE)
HEX2BIN=hex2bin -p 0
BINMAN=$(SCR)/sdrmini
BIN2HOB=$(SCR)/bin2hob
AUTOCONFIG=$(SCR)/autoconfig
S2HS=$(SCR)/s2hs

# RS232 for load
LDEVICE=/dev/ttyUSB0
LSPEED=19200
