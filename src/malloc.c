#include "../includes/memory_handler.h"
#include <string.h>

void *ft_malloc(size_t size) {
    printf("\n********** malloc **********\n");
    t_zone *ptr;
    if (size < BLOCK_LENGTH_SMALL_MIN) {
    // if (1 || size < BLOCK_LENGTH_SMALL_MIN) {
        printf("====== TINY\n");
        if (!g_tiny_zones) {
            g_tiny_zones = ft_create_zone(BLOCK_LENGTH_TINY_MAX, ZONE_MIN_BLOCKS);
        }
        ptr = g_tiny_zones;
        ft_create_block(g_tiny_zones, size, BLOCK_LENGTH_TINY_MIN);

    } else if (size < BLOCK_LENGTH_LARGE_MIN) {
        printf("====== SMALL\n");
        if (!g_small_zones) {
            g_small_zones = ft_create_zone(BLOCK_LENGTH_SMALL_MAX, ZONE_MIN_BLOCKS);
            ft_create_block(g_small_zones, size, BLOCK_LENGTH_SMALL_MIN);
        }
        ptr = g_small_zones;
        ft_create_block(g_small_zones, size, BLOCK_LENGTH_SMALL_MIN);
    } else {
        printf("====== LARGE\n");
    }
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
// printf("\n********** malloc \n********** %p\n", g_tiny_zones);
// char *ptr;
// printf("1) %p\n", ptr);
// ptr = (char *)mmap(0, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
// printf("2) %p\n", ptr);
// printf("3) %p\n", MAP_FAILED);
// printf("4) %p\n", NULL);
// printf("5) %c\n", ptr[0]);
// ptr[0] = 50;
// printf("6) %c\n", ptr[0]);