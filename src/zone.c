#include "libft_malloc.h"

t_block *ft_find_the_optimal_free_block_in_zone(size_t size, t_zone *zone) {
    if (zone) {
        t_block *block = zone->blocks;
        t_block *block_best = NULL;

        while (block) {
            if (block->free && size <= block->size && (!block_best || block->size < block_best->size))
                block_best = block;
            block = block->next;
        }

        return block_best;
    }

    return NULL;
}

t_block *ft_find_the_optimal_free_block_in_zones(size_t size, t_zone *zone) {
    if (zone) {
        t_block *block = NULL;
        
        while (!(block = ft_find_the_optimal_free_block_in_zone(size, zone)) && zone) {
            zone = zone->next;
        }

        return block;
    }

    return NULL;
}

t_block *ft_find_block_in_a_zone_from_pointer(void *ptr, t_zone *zone) {
    if (ptr && zone) {
        t_block *block = (t_block *)ptr - 1;
        t_block *block_tmp = zone->blocks;

        while (block_tmp != block && block_tmp)
            block_tmp = block_tmp->next;

        return block_tmp;
    }

    return NULL;
}

t_zone *ft_find_zone_from_pointer(void *ptr, int *zone_type) {
    if (ptr) {
        t_zone *zone = g_.tiny_first_zone;

        while (zone && (ptr < ZONE_DATA_START_TINY(zone) || ZONE_DATA_END_TINY(zone) < ptr))
            zone = zone->next;
        
        if (!zone) {
            zone = g_.small_first_zone;
                while (zone && (ptr < ZONE_DATA_START_SMALL(zone) || ZONE_DATA_END_SMALL(zone) < ptr))
                zone = zone->next;
            if (zone_type && zone)
                *zone_type = SMALL;
        }
        else if (zone_type)
            *zone_type = TINY;

        return zone;
    }

    return NULL;
}

t_zone *ft_malloc_zone(t_zone *prev_zone, int zone_size) {
    t_zone *zone = (t_zone *)mmap(0, zone_size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    
    if ((void *)zone != (void *)-1) {
        zone->blocks = (t_block *)(zone + 1);
        zone->blocks->free = true;
        zone->blocks->size = zone_size - STRUCT_ZONE_SIZE - STRUCT_BLOCK_SIZE;
        zone->blocks->prev = NULL;
        zone->blocks->next = NULL;
        zone->prev = prev_zone;
        zone->next = NULL;
    }

    return zone;
}

int ft_free_zone(t_zone *zone, int zone_type) {
    if (zone->prev)
        zone->prev->next = zone->next;
    else if (zone_type == TINY)
        g_.tiny_first_zone = zone->next;
    else
        g_.small_first_zone = zone->next;

    if (zone->next)
        zone->next->prev = zone->prev;
    else if (zone_type == TINY)
        g_.tiny_last_zone = zone->prev;
    else
        g_.small_last_zone = zone->prev;
    
    return munmap(zone, zone_type == TINY ? ZONE_TOTAL_SIZE_TINY : ZONE_TOTAL_SIZE_SMALL);
}
