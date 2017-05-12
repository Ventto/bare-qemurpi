SRCS	= 	core_list_join.c \
			core_matrix.c \
			core_mith.c \
			core_portme.c \
			core_state.c \
			core_util.c

OBJS	= $(SRCS:.c=.o)

HEADERS		= ./ $(BSPDIR) ../../mith/include ../../mith/al/include
INCLUDES	= $(addprefix -I, $(HEADERS))

CFLAGS 		= -Wall $(DFLAGS)

.PHONY: all
all: $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

.PHONY: debug
debug: CFLAGS+=-g
debug: all

.PHONY: clean
clean:
	$(RM) $(OBJS)
