# App name
APP=wcplugin

# CRT0
CRT0PATH=$(TOP)/libsrc/crt0/$(CRT0WCPLUGIN)

# LIBS (user-defined) if LIBS not defined then ALL libraies will be used.
LIBS=libwcplugin libuart libz80

# Object files
OBJ=plugin.rel