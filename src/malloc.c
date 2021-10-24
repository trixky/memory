#include "../includes/memory_handler.h"
#include <string.h>

t_block *ft_malloc_in_specific_zone_type(size_t size, t_zone **first_zone, t_zone **last_zone) {
    t_block *block;
    if (!*last_zone) {
        *first_zone = ft_create_zone(NULL, BLOCK_LENGTH_TINY_MAX);
        *last_zone = *first_zone;
    }
    block = ft_find_the_optimal_free_block_in_zones(size, *first_zone);
    if (!block) {
        *last_zone = ft_create_zone(*last_zone, BLOCK_LENGTH_TINY_MAX);
        block = ft_find_the_optimal_free_block_in_zones(size, *last_zone);
    }

    return ft_malloc_block(block, size) + 1;
}

void *ft_malloc(size_t size) {
    printf("\n********** malloc **********\n");
    if (size < BLOCK_LENGTH_SMALL_MIN)
        return ft_malloc_in_specific_zone_type(size, &g_tiny_first_zone, &g_tiny_last_zone);
    else if (size < BLOCK_LENGTH_LARGE_MIN)
        return ft_malloc_in_specific_zone_type(size, &g_small_first_zone, &g_small_last_zone);
    return NULL + 1;    // LARGE todo
}