ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

LIBRARY_NAME = libft_malloc
LIBRARY_EXTENSION = .so
LIBRARY = ${LIBRARY_NAME}${LIBRARY_EXTENSION}
DYNAMIC_LIBRARY = ${LIBRARY_NAME}_${HOSTTYPE}${LIBRARY_EXTENSION}

CC = gcc
CCFLAGS = -fPIC -Wall -Wextra -Werror

RM = rm -rf

DIR_HEADERS 	= ./includes/
DIR_SRCS 		= ./src/
DIR_OBJS 		= ./obj/
SUB_DIRS 		= .
SUB_DIR_OBJS	=	$(SUB_DIRS:%=$(DIR_OBJS)%)

SRCS =	block.c \
		free.c \
		large.c \
		malloc.c \
		realloc.c \
		show.c \
		zone.c

OBJS			=	$(SRCS:%.c=$(DIR_OBJS)%.o)

all: $(LIBRARY)

$(LIBRARY): $(DYNAMIC_LIBRARY)
	@ln -sf $(DYNAMIC_LIBRARY) $(LIBRARY)

$(DYNAMIC_LIBRARY): $(OBJS)
	@$(CC) $(CCFLAGS) $(OBJS) -shared -o $(DYNAMIC_LIBRARY)

$(OBJS):		| $(DIR_OBJS)

$(DIR_OBJS)%.o: $(DIR_SRCS)%.c
	@$(CC) $(CCFLAGS) -I $(DIR_HEADERS) -c $< -o $@

$(DIR_OBJS):	$(SUB_DIR_OBJS)

$(SUB_DIR_OBJS):
	@mkdir -p $(SUB_DIR_OBJS)

clean:
	-${RM} ${DIR_OBJS} $(SRCS:.c=.o)

fclean: clean
	-${RM} ${LIBRARY}
	-${RM} ${DYNAMIC_LIBRARY}

re: clean fclean all

.PHONY: all clean fclean re
