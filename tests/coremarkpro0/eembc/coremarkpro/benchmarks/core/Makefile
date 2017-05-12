
# Target specific source files of the $(TARGET_TOPDIR) directory
TARGET_TOPDIR	:= ../../../../safran/bsps/raspi2
TARGET_SRCS		= $(wildcard $(TARGET_TOPDIR)/*.c)

SRCS	= 	core_list_join.c \
			core_matrix.c \
			core_mith.c \
			core_portme.c \
			core_state.c \
			core_util.c

#SRCS 	+= $(TARGET_SRCS)
OBJS	= $(SRCS:.c=.o)

HEADERS		= ./ $(TARGET_TOPDIR) ../../mith/include ../../mith/al/include
INCLUDES	= $(addprefix -I, $(HEADERS))

CFLAGS 		= -Wall $(DFLAGS)

.PHONY: all
all: $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

.PHONY: clean
clean:
	$(RM) $(OBJS)
