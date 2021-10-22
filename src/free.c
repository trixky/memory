#include "../includes/memory_handler.h"

void ft_free(void *ptr) {
    printf("\n********** free **********\n");
    ft_destroy_block(ptr);
}
