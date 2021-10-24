#include "../includes/memory_handler.h"

void ft_free(void *ptr) {
    if (ptr) {
        ft_find_zone_from_a_pointer(ptr);
        ft_destroy_block((t_block *)ptr - 1);
    }
}
