#include "../includes/memory_handler.h"

t_zone *ft_create_zone(int block_length_max, int block_nb) {
    int zone_len = (block_length_max + sizeof(t_block)) * block_nb + sizeof(t_zone);
    zone_len += zone_len % getpagesize(); // up to the pagesize multiple
    printf("\n********** ft_create_zone ********** (size = %d)\n", zone_len);

    t_zone *zone = (t_zone *)mmap(0, zone_len, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);


    zone->size = 0;
    zone->blocks = (t_block *)(zone + 1);
    zone->blocks->free = true;
    zone->blocks->size = zone_len - sizeof(t_zone) - sizeof(t_block);
    zone->blocks->next = NULL;
    zone->blocks->previous = NULL;
    zone->next = NULL;

    return zone;
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