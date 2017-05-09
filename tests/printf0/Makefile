APP  = kernel7
ELF  = $(APP).elf
BIN  = $(APP).bin
LDSCRIPT = kernel.ld

SRCS = main.c syscall.c
OBJS = $(SRCS:.c=.o)

CFLAGS += -Wall

all: $(BIN)

$(BIN): $(ELF)
	arm-unknown-eabi-objcopy -O binary $< $@

$(ELF): startup.o exit.o $(OBJS)
	arm-unknown-eabi-gcc -lc -Wl,-Map=$(APP).map -T $(LDSCRIPT) $^ -o $@

main.o: main.c
	arm-unknown-eabi-gcc -c $(CFLAGS) $< -o $@

syscall.o: syscall.c
	arm-unknown-eabi-gcc -c $(CFLAGS) $< -o $@

startup.o: startup.S
	arm-unknown-eabi-as $(DFLAG) $< -o $@

exit.o: exit.S
	arm-unknown-eabi-as $(DFLAG) $< -o $@

debug: DFLAG+=-g
debug: CFLAGS+=$(DFLAG)
debug: all

clean:
	$(RM) startup.o exit.o $(OBJS) $(APP).map $(ELF) $(BIN)

.PHONY: all debug clean
