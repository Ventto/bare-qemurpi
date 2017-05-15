CROSS_COMPILE   = arm-unknown-eabi-
AR              = $(CROSS_COMPILE)ar
AS              = $(CROSS_COMPILE)as
LD              = $(CROSS_COMPILE)ld
CC              = $(CROSS_COMPILE)gcc -mcpu=cortex-a15
CPP             = $(CC) -E
LD              = $(CROSS_COMPILE)ld
NM              = $(CROSS_COMPILE)nm
OBJCOPY         = $(CROSS_COMPILE)objcopy
OBJDUMP         = $(CROSS_COMPILE)objdump
STRIP           = $(CROSS_COMPILE)strip

PORT_DIR		= raspi2

export AR AS CC CPP LD NM OBJCOPY OBJDUMP STRIP

CFLAGS += -Wall -std=c99
