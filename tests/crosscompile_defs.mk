CROSS_COMPILE   = arm-unknown-eabi-
AS              = $(CROSS_COMPILE)as
LD              = $(CROSS_COMPILE)ld
CC              = $(CROSS_COMPILE)gcc -mcpu=cortex-a15
CPP             = $(CC) -E
AR              = $(CROSS_COMPILE)ar
NM              = $(CROSS_COMPILE)nm
STRIP           = $(CROSS_COMPILE)strip
OBJCOPY         = $(CROSS_COMPILE)objcopy
OBJDUMP         = $(CROSS_COMPILE)objdump

PORT_DIR		= raspi2

export AR AS CC CPP LD NM OBJCOPY OBJDUMP STRIP

CFLAGS += -Wall -std=c99
