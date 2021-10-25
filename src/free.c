#include "../includes/memory_handler.h"

void ft_free(void *ptr) {
    if (ptr) {
        int zone_type;
        t_zone *zone = ft_find_zone_from_a_pointer(ptr, &zone_type);
        if (zone) {
            t_block *block = ft_find_block_in_a_zone_from_ptr(ptr, zone);
            ft_free_block(block);
            if (zone->blocks && !zone->blocks->next && zone->blocks->free)
                ft_free_zone(zone, zone_type);
        }
    }
}
