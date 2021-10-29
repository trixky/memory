#include "../includes/libft_malloc.h"

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

t_block *ft_find_block_in_a_zone_from_ptr(void *ptr, t_zone *zone) {
    if (ptr && zone) {
        t_block *block = (t_block *)ptr - 1;
        t_block *block_tmp = zone->blocks;

        while (block_tmp != block && block_tmp)
            block_tmp = block_tmp->next;

        return block_tmp;
    }

    return NULL;
}

t_zone *ft_find_zone_from_a_pointer(void *ptr, int *zone_type) {
    if (ptr) {
        t_zone *zone = g_tiny_first_zone;

        while (zone && (ptr < ZONE_DATA_START_TINY(zone) || ZONE_DATA_END_TINY(zone) < ptr))
            zone = zone->next;
        
        if (!zone) {
            zone = g_small_first_zone;
            while (zone && (ZONE_DATA_START_SMALL(zone) < ptr || ptr < ZONE_DATA_END_SMALL(zone)))
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

    printf("********** ft_malloc_zone ********** [%p] size = %d\n", zone, zone_size);

    zone->blocks = (t_block *)(zone + 1);
    zone->blocks->free = true;
    zone->blocks->size = zone_size - STRUCT_ZONE_SIZE - STRUCT_BLOCK_SIZE;
    zone->blocks->prev = NULL;
    zone->blocks->next = NULL;
    zone->prev = prev_zone;
    zone->next = NULL;

    return zone;
}

int ft_free_zone(t_zone *zone, int zone_type) {
    if (zone->prev)
        zone->prev->next = zone->next;
    else if (zone_type == TINY)
        g_tiny_first_zone = zone->next;
    else
        g_small_first_zone = zone->next;

    if (zone->next)
        zone->next->prev = zone->prev;
    else if (zone_type == TINY)
        g_tiny_last_zone = zone->prev;
    else
        g_small_last_zone = zone->prev;
    
    return munmap(zone, zone_type == TINY ? ZONE_TOTAL_SIZE_TINY : ZONE_TOTAL_SIZE_SMALL);
}

void ft_show_zone(t_zone *zone) {

    if (zone) {
        t_block *ptr;
        ptr = zone->blocks;
        while (ptr) {
            printf("----------------------------------------------\n");
            printf("prev : %p%s\t free : %s\n", ptr->prev, ptr->prev ? "" : "\t", ptr->free ? "true" : "false");
            printf("curr : %p%s\t size : %ld\toctets\n", ptr, ptr ? "" : "\t", ptr->size);
            printf("next : %p\n", ptr->next);
            ptr = ptr->next;
        }
    } else {
        printf("****** zone is nil\n");
    }
}

void ft_show_large(t_large *large) {
    printf("prev: %p%s\t curr: %p\tsize : %ld\tnext: %p\n", large->prev, large->prev ? "" : "\t", large, large->size, large->next);
}

void ft_show_zones() {
    printf("\n===============================================\n");
    printf("================ ft_show_zones ================\n");
    printf("===============================================\n");
	pthread_mutex_lock(&g_lock);		// LOCK
    t_zone *zone = g_tiny_first_zone;
    printf("\n================== tiny_zones =================\n");
    while (zone) {
        printf(">>>>>>>>>>>>>>>> zone %p\n", zone);
        ft_show_zone(zone);
        zone = zone->next;
    }
    printf("\n================= small_zones =================\n");
    zone = g_small_first_zone;
    while (zone) {
        printf(">>>>>>>>>>>>>>>> zone %p\n", zone);
        ft_show_zone(zone);
        zone = zone->next;
    }
    printf("\n=================== larges ====================\n");
    t_large *large = g_larges;
    printf(">>>>>>>>>>>>>>>> larges %p\n", large);
    while (large) {
        ft_show_large(large);
        large = large->next;
    }
	pthread_mutex_unlock(&g_lock);		// UNLOCK
}