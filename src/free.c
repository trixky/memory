#include "libft_malloc.h"

void ft_free(void *ptr, bool history) {
    if (ptr) {
        int     zone_type;
        t_zone  *zone = ft_find_zone_from_pointer(ptr, &zone_type);

        if (zone) {
            t_block *block = ft_find_block_in_a_zone_from_pointer(ptr, zone);
            if (block) {
                bool    zone_freed = false;
                int     block_size = block->size;
                ft_free_block(block);
                if ((zone->prev || zone->next) && zone->blocks && !zone->blocks->next && zone->blocks->free) {
                    zone_freed = true;
                    ft_free_zone(zone, zone_type);
                }
                if (history)
                    ft_push_free_in_history(ptr, block_size, zone_type, block, zone, zone_freed);
                    
                return ;
            }
        }
        else {
            t_large *large = ft_find_large_from_pointer(ptr);
            if (large) {
                if (history)
                    ft_push_free_in_history(ptr, large->size, LARGE, large, NULL, true);
                ft_free_large(large);
                
                return ;
            }
        }
        if (history)
            ft_push_free_error_in_history(ptr);
    }
}

void free(void *ptr) {
    pthread_mutex_lock(&g_lock);        // LOCK
    ft_free(ptr, true);
    pthread_mutex_unlock(&g_lock);      // UNLOCK
}
