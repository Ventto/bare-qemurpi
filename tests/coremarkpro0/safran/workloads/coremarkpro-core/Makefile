SRCS 		= main.c
OBJS		= $(SRCS:.c=.o)

HEADERS		= $(BSPDIR) \
			  ../../../eembc/coremarkpro/mith/include \
			  ../../../eembc/coremarkpro/mith/al/include
INCLUDES	= $(addprefix -I,$(HEADERS))

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
