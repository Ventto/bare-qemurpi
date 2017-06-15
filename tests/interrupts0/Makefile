include ../crosscompile_defs.mk

APP  = kernel7
ELF  = $(APP).elf
BIN  = $(APP).bin
MAP  = $(APP).map

SRCS = bcm2835_uart.c \
	   irq_handlers.c \
	   main.c \
	   startup.S
OBJS = $(addprefix src/, $(patsubst %.S,%.o,$(patsubst %.c,%.o,$(SRCS))))

LINK = startup.x

INCDIRS = -I./include
CFLAGS += -ffreestanding -nostartfiles $(INCDIRS)

.PHONY: all
all: $(BIN)

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

$(ELF): $(OBJS)
	$(CC) $(CFLAGS) -Wl,-Map=$(MAP) -T $(LINK) $^ -o $@

src/startup.o: src/startup.S
	$(AS) $(DFLAGS) $< -o $@

.PHONY: debug
debug: DFLAGS=-g
debug: CFLAGS+=$(DFLAGS)
debug: all

.PHONY: clean
clean:
	$(RM) $(OBJS) $(ELF) $(BIN) $(MAP)
