
# Target specific source files of the $(TARGET_TOPDIR) directory
TARGET_TOPDIR	:= ../../../safran/bsps/raspi2
TARGET_SRCS		= $(wildcard $(TARGET_TOPDIR)/*.c)

SRC_DIR		= 	src/
SRC_FILES	= 	md5 \
				mith_lib \
				mith_workload \
				th_bignum \
				th_encode \
				th_getopt \
				th_lib \
				th_math \
				th_rand

SRCS 		= $(addprefix $(SRC_DIR), $(addsuffix .c,$(SRC_FILES))) $(TARGET_SRCS)
OBJS		= $(SRCS:.c=.o)

HEADERS		= $(TARGET_TOPDIR) include al/include
INCLUDES	= $(addprefix -I,$(HEADERS))

CFLAGS 		= -Wall $(DFLAGS)

.PHONY: all
all: $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

.PHONY: clean
clean:
	$(RM) $(OBJS)
