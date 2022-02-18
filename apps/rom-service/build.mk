# App name
APP=rom-service

# Object files
OBJ=main.rel keyidle.rel

# LIBS (user-defined) if LIBS not defined then ALL libraies will be used.
LIBS=libzxkbd libconio libz80 libfonts

# CRT0
CRT0PATH=$(TOP)/libsrc/crt0/$(CRT0ROM)
