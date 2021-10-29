LIBRARY_NAME=libft_malloc
LIBRARY_EXTENSION=.so
LIBRARY=${LIBRARY_NAME}_${LIBRARY_EXTENSION}

if [ -z "$1" ]
then
    echo You have to specify a main file...
    exit 1
fi

make re

gcc ./tests/$1 $LIBRARY
make clean
echo "\n------------------------ exec a.out :"
/usr/bin/time -v ./a.out