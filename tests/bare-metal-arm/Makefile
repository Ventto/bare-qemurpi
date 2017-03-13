APP  = test
ELF  = $(APP).elf
BIN  = $(APP).bin
LDSCRIPT = $(APP).ld

CFLAGS += -Wall

all: $(BIN)

$(BIN): $(ELF)
	arm-unknown-eabi-objcopy -O binary $^ $@

$(ELF): $(APP).o startup.o
	arm-unknown-eabi-ld -Map $(APP).map -T $(LDSCRIPT) $< -o $@

startup.o: startup.s
	arm-unknown-eabi-as $(DFLAG) $^ -o $@

$(APP).o: $(APP).c
	arm-unknown-eabi-gcc -c $(CFLAGS) $^ -o $@

debug: DFLAG+=-g
debug: CFLAGS+=$(DFLAG)
debug: all

clean:
	$(RM) startup.o $(APP).o $(ELF) $(BIN)

.PHONY: all debug clean
