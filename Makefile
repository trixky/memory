ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

LIBRARY_NAME = libft_malloc
LIBRARY_EXTENSION = .so
LIBRARY = ${LIBRARY_NAME}_${LIBRARY_EXTENSION}
DYNAMIC_LIBRARY = ${LIBRARY_NAME}_${HOSTTYPE}_${LIBRARY_EXTENSION}
CC = gcc
CFLAGS = -fPIC
# CFLAGS = -fPIC -Wall -Wextra -Werror
LL = ar
LFLAGS = -crs
RM = rm -f

SRCS =	./src/block.c \
		./src/free.c \
		./src/large.c \
		./src/malloc.c \
		./src/realloc.c \
		./src/show.c \
		./src/zone.c

OBJS = $(SRCS:.c=.o)

all: ${LIBRARY}

$(LIBRARY): $(DYNAMIC_LIBRARY)
	@ln -sf $^ $@

$(DYNAMIC_LIBRARY): $(OBJS)
	$(LL) ${LFLAGS} -o $@ $^

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

include $(SRCS:.c=.d)

clean:
	-${RM} ${OBJS} $(SRCS:.c=.d)

fclean: clean
	-${RM} ${LIBRARY}
	-${RM} ${DYNAMIC_LIBRARY}

re: clean fclean all

.PHONY: all re clean
