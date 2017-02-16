APP  = test
ELF  = $(APP).elf
BIN  = $(APP).bin
LDSCRIPT = $(APP).ld

CFLAGS += -Wall

all: $(BIN)

$(BIN): $(ELF)
	arm-unknown-eabi-objcopy -O binary $^ $@

$(ELF): $(APP).o startup.o
	arm-unknown-eabi-ld -T $(LDSCRIPT) $< -o $@

startup.o: startup.s
	arm-unknown-eabi-as -mcpu=arm926ej-s -g $^ -o $@

$(APP).o: $(APP).c
	arm-unknown-eabi-gcc -c -mcpu=arm926ej-s $(CFLAGS) $^ -o $@

debug: CFLAGS+=-g
debug: all

clean:
	$(RM) startup.o $(APP).o $(ELF) $(BIN)

.PHONY: all debug clean
