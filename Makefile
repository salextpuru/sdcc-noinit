# Development tools
TOP:=$(shell pwd)
SCR:=$(TOP)/scripts

# Libraries
LIBSRC:=$(TOP)/libsrc
LIBDIR:=$(TOP)/libs

# Applications
APPSRC:=$(TOP)/apps
APPDIR:=$(TOP)/bin

# Config files
CONFIGS:=$(TOP)/configs
include $(CONFIGS)/*.mk

# Toolchain path
PATH:=$(PATH):$(TCPATH)

# CRT0
CRT0PATH=$(TOP)/libsrc/crt0/$(CRT0)

# Generate library names
LIBS:=$(addprefix $(LIBDIR)/, $(LIBRARY:=.lib) )

# Generate lib specificaton
LIBSLINK:=$(addprefix -l $(LIBDIR)/, $(LIBRARY:=.lib) ) $(STDLIBS)

# Generate includes
INCS:=$(addprefix -I $(LIBSRC)/, $(LIBRARY) )
COPTS+=-I $(TOP)/include $(INCS)

# Generate application names
APPS:=$(addprefix $(APPDIR)/, $(APPLICATIONS:=.bin) )

all: libs apps kdevelop_path
	@echo "$(STDLIBS)"
	@echo "all ok"

$(APPDIR)/%.bin: $(APPSRC)/%
	make -C $<

apps: .EXPORT_ALL_VARIABLES $(APPS)
	@echo -n

$(LIBDIR)/lib%.lib: $(LIBSRC)/lib%
	make -C $<

.EXPORT_ALL_VARIABLES:
	@echo "Export All variables"

libs: .EXPORT_ALL_VARIABLES $(LIBS)
	@echo -n

kdevelop_path:
	@echo -n > $(TOP)/.kdev_include_paths
	@echo "$(TOP)/include" >> $(TOP)/.kdev_include_paths
	@for i in $(addprefix $(LIBSRC)/, $(LIBRARY) ) $(addprefix $(APPDIR)/, $(APPLICATIONS) ) ; do \
	echo $$i >> $(TOP)/.kdev_include_paths ; \
	done


clean:
	rm -rf *.rel *.lst *.sym *.exp *.bin *.map *.mem *.lnk *.ihx *.rel *.rst *.asm *.bin *.rel *.hS *.\$$C *.lk *.noi *.tap $(APPDIR) $(LIBDIR)
	@for i in $(LIBRARY) ; do make -C $(LIBSRC)/$$i clean ; done
	@for i in $(APPLICATIONS) ; do make -C $(APPSRC)/$$i clean ; done
