include ../../crosscompile_defs.mk

TARGET		:= raspi2

TOPDIR		= $(shell pwd)
export TOPDIR

COREDIR 	= $(TOPDIR)/eembc/coremarkpro/benchmarks/core
MITHDIR 	= $(TOPDIR)/eembc/coremarkpro/mith
BSPDIR		= $(TOPDIR)/safran/bsps/$(TARGET)
WORKDIR		= $(TOPDIR)/safran/workloads/coremarkpro-core

HEADERS		= $(BSPDIR) $(MITHDIR)/include $(MITHDIR)/al/include
INCS		= $(addprefix -I,$(HEADERS))

SRCS		= $(shell find . -type f -iname '*.c')
OBJS		= $(SRCS:.c=.o) startup.o

ELF			= coremark.elf
LDSCRIPT	= $(BSPDIR)/kernel.ld

CFLAGS 		= -Wall -pedantic -std=c99
export CFLAGS

.PHONY: all
all: $(ELF)

$(ELF): core mith target exec
	$(CC) -Wl,-Map=coremark.map -T $(LDSCRIPT) $(OBJS) -lm -o $@

.PHONY: core
core:
	$(MAKE) -C $(COREDIR) BSPDIR=$(BSPDIR)

.PHONY: mith
mith:
	$(MAKE) -C $(MITHDIR) BSPDIR=$(BSPDIR)

.PHONY: target
target:
	$(MAKE) -C $(BSPDIR)

.PHONY: exec
exec: $(WORKDIR)/main.o

$(WORKDIR)/main.o: $(WORKDIR)/main.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

.PHONY: debug
debug: CFLAGS=-g
debug: all

.PHONY: clean
clean:
	$(MAKE) -C $(COREDIR) BSPDIR=$(BSPDIR) clean
	$(MAKE) -C $(MITHDIR) BSPDIR=$(BSPDIR) clean
	$(MAKE) -C $(MITHDIR) BSPDIR=$(BSPDIR) clean
	$(RM) $(OBJS) $(ELF)



