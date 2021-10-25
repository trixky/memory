#include "../includes/memory_handler.h"
#include <string.h>

t_block *ft_malloc_in_specific_zone_type(size_t size, t_zone **first_zone, t_zone **last_zone, int zone_size) {
    t_block *block;

    if (!*last_zone) {
        *first_zone = ft_malloc_zone(NULL, zone_size);
        *last_zone = *first_zone;
    }
    block = ft_find_the_optimal_free_block_in_zones(size, *first_zone);
    if (!block) {
        (*last_zone)->next = ft_malloc_zone(*last_zone, zone_size);
        *last_zone = (*last_zone)->next;
        block = ft_find_the_optimal_free_block_in_zones(size, *last_zone);
    }

    return ft_malloc_block(block, size) + 1;
}

void *ft_malloc(size_t size) {
    if (size < BLOCK_LENGTH_SMALL_MIN)
        return ft_malloc_in_specific_zone_type(size, &g_tiny_first_zone, &g_tiny_last_zone, ZONE_TOTAL_SIZE_TINY);
    else if (size < BLOCK_LENGTH_LARGE_MIN)
        return ft_malloc_in_specific_zone_type(size, &g_small_first_zone, &g_small_last_zone, ZONE_TOTAL_SIZE_SMALL);
    return NULL + 1;    // LARGE todo
}