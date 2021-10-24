#include "../includes/memory_handler.h"

t_block *ft_find_the_optimal_free_block_in_zone(size_t size, t_zone *zone) {
    if (zone) {
        t_block *block = zone->blocks;
        t_block *block_best = NULL;

        while (block) {
            if (block->free && size <= block->size && (!block_best || size < block_best->size))
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

t_zone *ft_create_zone(t_zone *previous_zone, int block_length_max, int block_nb) {
    int zone_len = (block_length_max + sizeof(t_block)) * block_nb + sizeof(t_zone);
    zone_len += getpagesize() - zone_len % getpagesize(); // up to the pagesize multiple
    printf("\n********** ft_create_zone ********** (size = %d) pagesize %d\n", zone_len, getpagesize());

    t_zone *new_zone = (t_zone *)mmap(0, zone_len, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);

    new_zone->blocks = (t_block *)(new_zone + 1);
    new_zone->blocks->free = true;
    new_zone->blocks->size = zone_len - sizeof(t_zone) - sizeof(t_block);
    new_zone->blocks->previous = NULL;
    new_zone->blocks->next = NULL;
    new_zone->previous = previous_zone;
    new_zone->next = NULL;

    return new_zone;
}

t_zone *ft_find_zone_from_block_in_specific_zone_type(t_zone *zone, t_block *block) {
    t_block *block_tmp;

    while (zone) {
        block_tmp = zone->blocks;
        while (block_tmp) {
            if (block_tmp == block) {
                return zone;
            }
            block_tmp = block_tmp->next;
        }
        zone = zone->next;
    }

    return NULL;
}

t_zone *ft_find_zone_from_block(t_block *block) {
    t_zone *zone = ft_find_zone_from_block_in_specific_zone_type(g_tiny_first_zone, block);
    if (!zone)
        zone = ft_find_zone_from_block_in_specific_zone_type(g_small_first_zone, block);

    return zone;
}


void ft_show_zone(t_zone *zone) {
    printf("\n================ ft_show_zone ================ [zone = %p] \n", zone);

    if (zone) {
        t_block *ptr;
        ptr = zone->blocks;
        while (ptr) {
            printf("----------------------------------------------\n");
            printf("prev : %p%s\t free : %s\n", ptr->previous, ptr->previous ? "" : "\t", ptr->free ? "true" : "false");
            printf("curr : %p%s\t size : %ld\tbits\n", ptr, ptr ? "" : "\t", ptr->size);
            printf("next : %p\n", ptr->next);
            ptr = ptr->next;
        }
    } else {
        printf("****** zone is nil\n");
    }
}