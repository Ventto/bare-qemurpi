include ../crosscompile_defs.mk

APP  = kernel7
ELF  = $(APP).elf
BIN  = $(APP).bin
MAP  = $(APP).map

SRCS = vectors.S \
	   generic_timers.S \
	   int_handlers.c \
	   syscall.c \
	   main.c
OBJS = $(addprefix src/, $(patsubst %.S,%.o,$(patsubst %.c,%.o,$(SRCS))))

LINK = startup.x

INCDIRS = -I./include
CFLAGS += -nostartfiles $(INCDIRS)

.PHONY: all
all: $(BIN)

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

$(ELF): $(OBJS)
	$(CC) $(CFLAGS) -Wl,-Map=$(MAP) -T $(LINK) $^ -o $@

src/vectors.o: src/vectors.S
	$(AS) $(DFLAGS) $< -o $@

src/generic_timers.o: src/generic_timers.S
	$(AS) $(DFLAGS) $< -o $@

.PHONY: debug
debug: DFLAGS=-g
debug: CFLAGS+=$(DFLAGS)
debug: all

.PHONY: clean
clean:
	$(RM) $(OBJS) $(ELF) $(BIN) $(MAP)
