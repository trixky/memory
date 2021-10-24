#ifndef _MEMORY_HANDLER_H
# define _MEMORY_HANDLER_H

#include <unistd.h>
// getpagesize
#include <sys/mman.h>
// mmap
// munmap
#include <sys/time.h>
#include <sys/resource.h>
// getrlimit
#include <stdio.h>
// printf
#include <errno.h>
// errno
#include <stdbool.h>

#define STRUCT_BLOCK_SIZE sizeof(t_block)
#define STRUCT_ZONE_SIZE sizeof(t_zone)

#define BLOCKS_PER_ZONE 100

#define BLOCK_LENGTH_TINY_MIN	1
#define BLOCK_LENGTH_TINY_MAX	256
#define BLOCK_LENGTH_SMALL_MIN	(BLOCK_LENGTH_TINY_MAX + 1)
#define BLOCK_LENGTH_SMALL_MAX	1024
#define BLOCK_LENGTH_LARGE_MIN	(BLOCK_LENGTH_SMALL_MAX + 1)

#define ZONE_SIZE(max_block_data_size) (STRUCT_ZONE_SIZE + BLOCKS_PER_ZONE * (STRUCT_BLOCK_SIZE + max_block_data_size))

typedef struct				s_block
{
	bool					free;
	long int				size;
	struct s_block*			previous;
	struct s_block*			next;
}							t_block;

typedef struct				s_zone {
	t_block*				blocks;
	struct s_zone*			previous;
	struct s_zone*			next;
}							t_zone;

typedef struct				s_large {
	struct s_large*			next;
}							t_large;

t_zone*						g_tiny_first_zone;
t_zone*						g_tiny_last_zone;
t_zone*						g_small_first_zone;
t_zone*						g_small_last_zone;
unsigned long long int		g_allowed_bytes;

// free.c
void ft_free(void *ptr);
// malloc.c
void *ft_malloc(size_t size);
// realloc.c
void *ft_realloc(void *ptr, size_t size);
// zone.c
t_block *ft_find_the_optimal_free_block_in_zones(size_t size, t_zone *zone);
t_zone *ft_create_zone(t_zone *previous_zone, int max_block_data_size);
t_zone *ft_find_zone_from_block(t_block *block);
void ft_show_zone(t_zone *zone);
// block.c
t_block *ft_malloc_block(t_block *block, size_t size);
void ft_destroy_block(t_block *block);

#endif