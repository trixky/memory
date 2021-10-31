#!/bin/sh 

LIBRARY_NAME=libft_malloc
LIBRARY_EXTENSION=.so
LIBRARY=${LIBRARY_NAME}${LIBRARY_EXTENSION}

if [ -z "$1" ]
then
    echo You have to specify a main file...
    exit 1
fi

make re

gcc ./tests/$1 $LIBRARY
echo "\n------------------------ exec a.out :"
LD_LIBRARY_PATH=. LD_PRELOAD=libft_malloc.so /usr/bin/time -v ./a.out