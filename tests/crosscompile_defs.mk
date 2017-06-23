CROSS_COMPILE   = arm-unknown-eabi-
AS              = $(CROSS_COMPILE)as
LD              = $(CROSS_COMPILE)ld
CC              = $(CROSS_COMPILE)gcc
CPP             = $(CC) -E
AR              = $(CROSS_COMPILE)ar
NM              = $(CROSS_COMPILE)nm
STRIP           = $(CROSS_COMPILE)strip
OBJCOPY         = $(CROSS_COMPILE)objcopy
OBJDUMP         = $(CROSS_COMPILE)objdump

export 			AR AS CC CPP LD NM OBJCOPY OBJDUMP STRIP

ARCHFLAGS 		= -march=armv7-a
CFLAGS 			:= -Wall -Werror -std=c99 $(ARCHFLAGS)
AFLAGS			:= $(ARCHFLAGS)
