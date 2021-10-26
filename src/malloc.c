#include "../includes/memory_handler.h"

void *ft_malloc_in_specific_zone_type(size_t size, t_zone **first_zone, t_zone **last_zone, int zone_size) {
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

void *ft_malloc_out_of_zone(size_t size) {
    t_large *large = (t_large *)mmap(0, size + STRUCT_LARGE_SIZE, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);

    large->size = size;
    large->prev = NULL;

    if (g_larges) {
        large->next = g_larges;
        large->next->prev = large;
    }
    else
        large->next = NULL;
    
    g_larges = large;

    return large + 1;
}

void *ft_malloc(size_t size) {
    if (size < BLOCK_LENGTH_SMALL_MIN) {
        printf("chat 1\n");
        return ft_malloc_in_specific_zone_type(size, &g_tiny_first_zone, &g_tiny_last_zone, ZONE_TOTAL_SIZE_TINY);
    }
    else if (size < BLOCK_LENGTH_LARGE_MIN) {
        printf("chat 2\n");
        return ft_malloc_in_specific_zone_type(size, &g_small_first_zone, &g_small_last_zone, ZONE_TOTAL_SIZE_SMALL);
    }
    printf("chat 3\n");
    return ft_malloc_out_of_zone(size);
}