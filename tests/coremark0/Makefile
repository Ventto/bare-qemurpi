PORT_DIR=raspi2
include $(PORT_DIR)/core_portme.mak

ITERATIONS		:=100

CFLAGS 			+= -DITERATIONS=$(ITERATIONS)

CORE_SRCS 	= core_list_join.c \
			  core_main.c \
			  core_matrix.c \
			  core_state.c \
			  core_util.c

SRCS 		= $(CORE_SRCS) $(PORT_SRCS)
OBJS 		= $(SRC:.c=.o)
HEADERS 	= coremark.h

ELF 		= coremark.elf

.PHONY: all
all: $(ELF)

$(ELF): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) -o $(ELF)

.PHONY: debug
debug: CFLAGS+=-g
debug: all

.PHONY: clean
clean:
	$(RM) $(ELF)
