#include "../includes/memory_handler.h"

void *ft_malloc(size_t size) {
    printf("*** malloc ***\n");
    char *ptr;
    printf("1) %p\n", ptr);
    ptr = (char *)mmap(0, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    printf("2) %p\n", ptr);
    printf("3) %p\n", MAP_FAILED);
    printf("4) %p\n", NULL);
    printf("5) %c\n", ptr[0]);
    ptr[0] = 50;
    printf("6) %c\n", ptr[0]);
    printf("7) %d\n", AREA_MIN_SIZE);
    printf("8) %d\n", TINY_AREA_LEN);
}
