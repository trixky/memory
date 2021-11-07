#include "libft_malloc.h"

t_global        g_;
pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;

void *ft_malloc_in_specific_zone_type(size_t size, t_zone **first_zone, t_zone **last_zone, int zone_size, int zone_type, bool history) {
    t_block *block;
    t_zone  *zone;

    if (!*last_zone) {
        zone = ft_malloc_zone(NULL, zone_size);
        if ((void *)zone == (void *)-1) {
            if (history)
                ft_push_malloc_error_in_history(size);

            return NULL;
        }
        *first_zone = zone;
        *last_zone = zone;
    }
    block = ft_find_the_optimal_free_block_in_zones(size, *first_zone);
    if (!block) {
        zone = ft_malloc_zone(*last_zone, zone_size);
        if ((void *)zone == (void *)-1) {
            if (history)
                ft_push_malloc_error_in_history(size);

            return NULL;
        }
        (*last_zone)->next = zone;
        *last_zone = zone;
        block = ft_find_the_optimal_free_block_in_zones(size, *last_zone);
    }
    block = ft_malloc_block(block, size);

    if (history)
        ft_push_malloc_in_history(block + 1, size, zone_type, block, zone);

    return block + 1;
}

void *ft_malloc_out_of_zone(size_t size, bool history) {
    t_large *large = (t_large *)mmap(0, size + STRUCT_LARGE_SIZE, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);

    if ((void *)large == (void *)-1) {
        if (history)
            ft_push_malloc_error_in_history(size);

        return NULL;
    }

    large->size = size;
    large->prev = NULL;

    if (g_.larges) {
        large->next = g_.larges;
        large->next->prev = large;
    }
    else
        large->next = NULL;

    g_.larges = large;

    if (history)
        ft_push_malloc_in_history(large + 1, size, LARGE, large, NULL);

    return large + 1;
}

void *ft_malloc(size_t size, bool history) {
    if (size < BLOCK_LENGTH_SMALL_MIN)
        return ft_malloc_in_specific_zone_type(size, &g_.tiny_first_zone, &g_.tiny_last_zone, ZONE_TOTAL_SIZE_TINY, TINY, history);
    else if (size < BLOCK_LENGTH_LARGE_MIN)
        return ft_malloc_in_specific_zone_type(size, &g_.small_first_zone, &g_.small_last_zone, ZONE_TOTAL_SIZE_SMALL, SMALL, history);
    
    return ft_malloc_out_of_zone(size, history);
}

void *malloc(size_t size) {
    pthread_mutex_lock(&g_lock);        // LOCK
    void *ptr = ft_malloc(size, true);
    pthread_mutex_unlock(&g_lock);      // UNLOCK

    return ptr;
}