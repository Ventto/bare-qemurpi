include ../crosscompile_defs.mk

APP  	= kernel7
ELF  	= $(APP).elf
BIN  	= $(APP).bin
MAP  	= $(APP).map
LINK 	= startup.x

SRCS 	= bootstrap.S \
			vectors.S \
			irq.S \
			isr.c \
	   		syscall.c \
			bcm2836_control.c \
	   		bcm2835_systimers.c \
			not_main.c
OBJS 	= $(addprefix src/, $(patsubst %.S,%.o,$(patsubst %.c,%.o,$(SRCS))))

INCDIRS = -I./include
CFLAGS 	+= -nostartfiles $(INCDIRS)
AFLAGS  +=

.PHONY: all
all: $(BIN)

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

$(ELF): $(OBJS)
	$(CC) $(CFLAGS) -Wl,-Map=$(MAP) -T $(LINK) $^ -o $@

src/bootstrap.o: src/bootstrap.S
	$(AS) $(AFLAGS) $< -o $@

src/vectors.o: src/vectors.S
	$(AS) $(AFLAGS) $< -o $@

src/generic_timers.o: src/generic_timers.S
	$(AS) $(AFLAGS) $< -o $@

.PHONY: debug
debug: AFLAGS+=-g
debug: CFLAGS+=-g
debug: all

.PHONY: clean
clean:
	$(RM) $(OBJS) $(ELF) $(BIN) $(MAP)
