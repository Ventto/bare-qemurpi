# Toolchain configuration
include ../crosscompile_defs.mk

PORT_SRCS 	= $(PORT_DIR)/core_portme.c \
			  $(PORT_DIR)/syscall.c

PORT_CFLAGS = -ffreestanding
XCFLAGS		=
FLAGS_STR 	= "$(PORT_CFLAGS) $(XCFLAGS) $(XLFLAGS) $(LFLAGS_END)"
CFLAGS 		+= $(PORT_CFLAGS) -I$(PORT_DIR) -I. -DFLAGS_STR=\"$(FLAGS_STR)\"
