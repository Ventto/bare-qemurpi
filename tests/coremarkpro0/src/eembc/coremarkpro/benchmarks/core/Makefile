SRCS		= 	core_list_join.c \
				core_matrix.c \
				core_mith.c \
				core_portme.c \
				core_state.c \
				core_util.c
OBJS		= $(SRCS:.c=.o)
HEADERS		= $(BSPDIR) ../../mith/include ../../mith/al/include
INCS		= $(addprefix -I, $(HEADERS))

.PHONY: all
all: $(OBJS)

%.o: %.c %h
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

.PHONY: clean
clean:
	$(RM) $(OBJS)
