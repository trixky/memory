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

#define ZONE_MIN_BLOCKS 100

#define BLOCK_LENGTH_TINY_MIN	1
#define BLOCK_LENGTH_TINY_MAX	256
#define BLOCK_LENGTH_SMALL_MIN	(BLOCK_LENGTH_TINY_MAX + 1)
#define BLOCK_LENGTH_SMALL_MAX	1024
#define BLOCK_LENGTH_LARGE_MIN	(BLOCK_LENGTH_SMALL_MAX + 1)

typedef struct				s_block
{
	bool					free;
	long int				size;
	struct s_block*			previous;
	struct s_block*			next;
}							t_block;

typedef struct				s_zone {
	int						size;
	long int				max_block_size;
	t_block*				blocks;
	struct s_zone*			previous;
	struct s_zone*			next;
}							t_zone;

typedef struct				s_large {
	struct s_large*			next;
}							t_large;

t_zone*						g_tiny_zones;
t_zone*						g_tiny_zones_end;
t_zone*						g_small_zones;
t_zone*						g_small_zones_end;
t_large*					g_larges;
unsigned long long int		g_allowed_bytes;

// free.c
void ft_free(void *ptr);
// malloc.c
void *ft_malloc(size_t size);
// realloc.c
void *ft_realloc(void *ptr, size_t size);
// zone.c
t_zone *ft_find_zone_with_a_sufficient_block_size(size_t size, t_zone *zone);
t_zone *ft_create_zone(t_zone *previous_zone, int block_length_max, int block_nb);
t_zone *ft_find_zone_from_block(t_zone *zone, t_block *block);
void ft_show_zone(t_zone *zone);
// block.c
t_block *ft_create_block(t_zone *zone, size_t size);
void ft_destroy_block(t_block *block);

#endif