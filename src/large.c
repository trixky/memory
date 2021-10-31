#include "libft_malloc.h"

t_large *ft_find_large_from_pointer(void *ptr) {
    t_large *large = (t_large *)ptr - 1;
    t_large *large_tmp = g_.g_larges;

    while (large_tmp && large_tmp != large)
        large_tmp = large_tmp->next;
    
    return large_tmp;
}

void ft_free_large(t_large *large) {
    if (large->prev)
        large->prev->next = large->next;
    else
        g_.g_larges = large->next;
    if (large->next)
        large->next->prev = large->prev;
    
    munmap(large, STRUCT_LARGE_SIZE + large->size);
}