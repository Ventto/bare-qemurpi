include ../crosscompile_defs.mk

APP  = kernel7
ELF  = $(APP).elf
BIN  = $(APP).bin
LDSCRIPT = kernel.ld

all: $(BIN)

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

$(ELF): main.o startup.o
	$(LD) -Map $(APP).map -T $(LDSCRIPT) $^ -o $@

startup.o: startup.S
	$(AS) $(DFLAG) $< -o $@

main.o: main.c
	$(CC) -ffreestanding -c $(CFLAGS) $< -o $@

debug: DFLAG+=-g
debug: CFLAGS+=$(DFLAG)
debug: all

clean:
	$(RM) startup.o main.o $(APP).map $(ELF) $(BIN)

.PHONY: all debug clean
