APP  = kernel7
ELF  = $(APP).elf
BIN  = $(APP).bin
LDSCRIPT = kernel.ld

CFLAGS += -Wall

all: $(BIN)

$(BIN): $(ELF)
	arm-unknown-eabi-objcopy -O binary $< $@

$(ELF): main.o startup.o
	arm-unknown-eabi-ld -Map $(APP).map -T $(LDSCRIPT) $^ -o $@

startup.o: startup.S
	arm-unknown-eabi-as $(DFLAG) $< -o $@

main.o: main.c
	arm-unknown-eabi-gcc -ffreestanding -c $(CFLAGS) $< -o $@

debug: DFLAG+=-g
debug: CFLAGS+=$(DFLAG)
debug: all

clean:
	$(RM) startup.o main.o $(APP).map $(ELF) $(BIN)

.PHONY: all debug clean
