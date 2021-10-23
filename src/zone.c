#include "../includes/memory_handler.h"

t_zone *ft_find_zone_with_a_sufficient_block_size(size_t size, t_zone *zone) {
    while (zone && zone->max_block_size < size)
        zone = zone->next;
    
    return zone;
}

t_zone *ft_create_zone(t_zone *previous_zone, int block_length_max, int block_nb) {
    int zone_len = (block_length_max + sizeof(t_block)) * block_nb + sizeof(t_zone);
    zone_len += getpagesize() - zone_len % getpagesize(); // up to the pagesize multiple
    printf("\n********** ft_create_zone ********** (size = %d) pagesize %d\n", zone_len, getpagesize());

    t_zone *new_zone = (t_zone *)mmap(0, zone_len, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);

    new_zone->size = 0;
    new_zone->max_block_size = zone_len - sizeof(t_zone) - sizeof(t_block);
    new_zone->blocks = (t_block *)(new_zone + 1);
    new_zone->blocks->free = true;
    new_zone->blocks->size = new_zone->max_block_size;
    new_zone->blocks->previous = NULL;
    new_zone->blocks->next = NULL;
    new_zone->previous = previous_zone;
    new_zone->next = NULL;

    return new_zone;
}

t_zone *ft_find_zone_from_block_for_specific_zone_type(t_zone *zone, t_block *block) {
    t_zone *ptr_zone = zone;
    t_block *ptr_block;

    while (ptr_zone) {
        ptr_block = ptr_zone->blocks;
        while (ptr_block) {
            if (ptr_block == block) {
                return ptr_zone;
            }
            ptr_block = ptr_block->next;
        }
        ptr_zone = ptr_zone->next;
    }

    return NULL;
}

t_zone *ft_find_zone_from_block(t_zone *zone, t_block *block) {
    t_zone *ptr_zone = ft_find_zone_from_block_for_specific_zone_type(g_tiny_zones, block);
    if (!ptr_zone)
        ptr_zone = ft_find_zone_from_block_for_specific_zone_type(g_small_zones, block);

    return ptr_zone;
}


void ft_show_zone(t_zone *zone) {
    printf("\n********** ft_show_zone ********** (zone = %p) \n", zone);

    if (zone) {
        t_block *ptr;
        // free_blocks
        printf("****** blocks\n");
        ptr = zone->blocks;
        while (ptr) {
            printf("----------------\n");
            printf("previous = %p\n", ptr->previous);
            printf("me = %p\n", ptr);
            printf("size = %ld\n", ptr->size);
            printf("free = %s\n", ptr->free ? "true" : "false");
            printf("next = %p\n", ptr->next);
            ptr = ptr->next;
        }
    } else {
        printf("****** zone is nil\n");
    }
}