SRC_DIR		= 	src/
SRC_FILES	= 	md5.c \
				mith_lib.c \
				mith_workload.c \
				th_bignum.c \
				th_encode.c \
				th_getopt.c \
				th_lib.c \
				th_math.c \
				th_rand.c

BSP_SRCS	= $(wildcard $(BSPDIR)/*.c)
SRCS 		= $(addprefix $(SRC_DIR), $(SRC_FILES)) $(BSP_SRCS)
OBJS		= $(SRCS:.c=.o)

HEADERS		= ./ $(BSPDIR) include al/include
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
