include ../crosscompile_defs.mk

TARGET		:= raspi2

TOPDIR		= $(shell pwd)
export TOPDIR

COREDIR 	= $(TOPDIR)/src/eembc/coremarkpro/benchmarks/core
MITHDIR 	= $(TOPDIR)/src/eembc/coremarkpro/mith
BSPDIR		= $(TOPDIR)/src/safran/bsps/$(TARGET)
WORKDIR		= $(TOPDIR)/src/safran/workloads/coremarkpro-core
BUILDDIR   	:= build
BINDIR		= $(BUILDDIR)/$(TARGET)/coremarkpro-core

HEADERS		= $(BSPDIR) $(MITHDIR)/include $(MITHDIR)/al/include
INCS		= $(addprefix -I,$(HEADERS))

SRCS		= $(shell find . -type f -iname '*.c')
OBJS		= $(SRCS:.c=.o) src/startup.o

APPNAME		= coremark
ELF			= $(APPNAME).elf
MAP			= $(APPNAME).map

LDSCRIPT	= $(BSPDIR)/kernel.ld
CFLAGS 		+= -pedantic
export CFLAGS

.PHONY: all
all: $(BINDIR) $(ELF)

$(BINDIR):
	mkdir -p $@

$(ELF): core mith target $(WORKDIR)/main.o
	$(CC) -Wl,-Map=$(MAP) -T $(LDSCRIPT) $(OBJS) -lm -o $@
	@mv $(ELF) $(MAP) $(BINDIR)

.PHONY: core
core:
	$(MAKE) -C $(COREDIR) BSPDIR=$(BSPDIR)

.PHONY: mith
mith:
	$(MAKE) -C $(MITHDIR) BSPDIR=$(BSPDIR)

.PHONY: target
target:
	$(MAKE) -C $(BSPDIR)

$(WORKDIR)/main.o: $(WORKDIR)/main.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

.PHONY: debug
debug: CFLAGS=-g
debug: all

.PHONY: distclean
distclean: clean
	$(RM) -r $(BUILDDIR)

.PHONY: clean
clean:
	$(MAKE) -C $(COREDIR) BSPDIR=$(BSPDIR) clean
	$(MAKE) -C $(MITHDIR) BSPDIR=$(BSPDIR) clean
	$(MAKE) -C $(MITHDIR) BSPDIR=$(BSPDIR) clean
	$(RM) $(OBJS) $(BINDIR)/$(ELF) $(BINDIR)/$(MAP)
