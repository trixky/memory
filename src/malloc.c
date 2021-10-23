#include "../includes/memory_handler.h"
#include <string.h>

t_block *ft_malloc_in_specific_zone_type(size_t size, t_zone **first_zone, t_zone **last_zone) {
    t_zone *block;
    if (!*last_zone) {
        *first_zone = ft_create_zone(NULL, BLOCK_LENGTH_TINY_MAX, ZONE_MIN_BLOCKS);
        *last_zone = *first_zone;
    }
    block = ft_find_the_optimal_free_block_in_zones(size, *first_zone);
    if (!block) {
        *last_zone = ft_create_zone(*last_zone, BLOCK_LENGTH_TINY_MAX, ZONE_MIN_BLOCKS);
        block = ft_find_the_optimal_free_block_in_zones(size, *last_zone);
    }

    return ft_malloc_block(block, size) + 1;
}

void *ft_malloc(size_t size) {
    printf("\n********** malloc **********\n");
    t_zone *ptr_block;

    if (size < BLOCK_LENGTH_SMALL_MIN)
        return ft_malloc_in_specific_zone_type(size, &g_tiny_first_zone, &g_tiny_last_zone);
    else if (size < BLOCK_LENGTH_LARGE_MIN)
        return ft_malloc_in_specific_zone_type(size, &g_small_first_zone, &g_small_last_zone);
    return NULL + 1;    // LARGE todo
}

// ft_create_zone(BLOCK_TINY_MAX, ZONE_MIN_BLOCKS);
// printf("getpagesize() = %d\n", getpagesize()); 
// struct rlimit rlim_cur;
// printf("getrlimit() = %d\n", getrlimit(RLIMIT_AS, &rlim_cur));
// printf("le int de gerlimit = %d\n", getrlimit(RLIMIT_AS, &rlim_cur));
// getrlimit(RLIMIT_AS, &rlim_cur);
// printf("errno = %s\n", strerror(errno));
// printf("rlim_cur = %llu\n", rlim_cur.rlim_cur);
// printf("rlim_cur = %llu\n", rlim_cur.rlim_max);
// printf("\n********** malloc \n********** %p\n", g_tiny_first_zone);
// char *ptr;
// printf("1) %p\n", ptr);
// ptr = (char *)mmap(0, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
// printf("2) %p\n", ptr);
// printf("3) %p\n", MAP_FAILED);
// printf("4) %p\n", NULL);
// printf("5) %c\n", ptr[0]);
// ptr[0] = 50;
// printf("6) %c\n", ptr[0]);