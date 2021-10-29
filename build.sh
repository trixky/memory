LIBRARY_NAME=libft_malloc
LIBRARY_EXTENSION=.so
LIBRARY=${LIBRARY_NAME}_${LIBRARY_EXTENSION}

make re

gcc ./main.c $LIBRARY
make clean
echo "\n\n\n"
./a.out