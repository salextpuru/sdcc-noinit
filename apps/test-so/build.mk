# App name
APP=test-so

# Object files
OBJ=main.rel

# LIBS (user-defined) if LIBS not defined then ALL libraies will be used.

# External additional TAP file
EXTTAPS=$(LIBSRC)/libtestso/testso_v1.so $(LIBSRC)/libtestso/testso_v2.so

EXTTAPS_START=0x8000

# CRT0
# CRT0PATH=$(TOP)/libsrc/crt0/$(CRT0)
