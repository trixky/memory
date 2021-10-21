#include "../includes/memory_handler.h"

t_zone *ft_create_zone(int block_length_max, int block_nb) {
    printf("\n********** ft_create_zone **********\n");
    int zone_len = (block_length_max + sizeof(t_block)) * block_nb + sizeof(t_zone);
    zone_len += zone_len % getpagesize(); // up to the pagesize multiple

    t_zone *zone = (t_zone *)mmap(0, zone_len, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    zone->next = NULL;
    zone->m_blocks = NULL;
    zone->f_blocks = (t_block *)(zone + 1);
    zone->f_blocks->next = NULL;
    zone->f_blocks->size = zone_len - sizeof(t_zone) - sizeof(t_block);

    // printf("sizeof t_zone = %ld\n",  sizeof(t_block));
    // printf("sizeof t_zone = %ld\n",  sizeof(t_zone));
    // printf("zone_len = %d\n", zone_len);

    // printf("\nzone = %p\n", zone);
    // printf("zone->next = %p\n", zone->next);
    // printf("zone->m_blocks = %p\n", zone->m_blocks);
    // printf("zone->f_blocks = %p\n", zone->f_blocks);
    // printf("zone->f_blocks->next = %p\n", zone->f_blocks->next);
    // printf("zone->f_blocks->size = %d\n", zone->f_blocks->size);

    return zone;
}