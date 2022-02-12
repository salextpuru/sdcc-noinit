# App name
APP=rom-service

# Object files
OBJ=main.rel

# LIBS (user-defined) if LIBS not defined then ALL libraies will be used.
LIBS=libconio libz80 libfonts

# CRT0
CRT0PATH=$(TOP)/libsrc/crt0/$(CRT0ROM)
