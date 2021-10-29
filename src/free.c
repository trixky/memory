#include "../includes/libft_malloc.h"

void ft_free(void *ptr) {
    if (ptr) {
        int zone_type;
        pthread_mutex_lock(&g_lock);        // LOCK
        t_zone *zone = ft_find_zone_from_pointer(ptr, &zone_type);
        if (zone) {
            t_block *block = ft_find_block_in_a_zone_from_pointer(ptr, zone);
            if (block) {
                ft_free_block(block);
                if (zone->blocks && !zone->blocks->next && zone->blocks->free)
                    ft_free_zone(zone, zone_type);
            }
        }
        else {
            t_large *large = ft_find_large_from_pointer(ptr);
            if (large)
                ft_free_large(large);
        }
        pthread_mutex_unlock(&g_lock);      // UNLOCK
    }
}
