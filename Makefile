LIBRARY_NAME = memory_handler.a
CC = gcc
CFLAGS = -fPIC
# CFLAGS = -fPIC -Wall -Wextra -Werror
LL = ar
LFLAGS = -crs
RM = rm -f

SRCS =	./src/free.c \
		./src/malloc.c \
		./src/realloc.c

OBJS = $(SRCS:.c=.o)

all: ${LIBRARY_NAME}

$(LIBRARY_NAME): $(OBJS)
	$(LL) ${LFLAGS} -o $@ $^

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

include $(SRCS:.c=.d)

re: clean fclean all

clean:
	-${RM} ${OBJS} $(SRCS:.c=.d)

fclean: clean
	-${RM} ${LIBRARY_NAME}

.PHONY: all re clean
