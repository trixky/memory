#ifndef _LIBFT_MALLOC_H
# define _LIBFT_MALLOC_H

#include <unistd.h>
// getpagesize
#include <sys/mman.h>
// mmap
// munmap
#include <sys/time.h>
#include <sys/resource.h>
// getrlimit
#include <pthread.h>
// pthread_mutex_lock
// pthread_mutex_unlock
#include <unistd.h>
// write
#include <stdio.h>
// printf
#include <errno.h>
// errno
#include <stdbool.h>

#define TINY	0
#define SMALL	1
#define LARGE	2

#define PAGESIZE getpagesize()

#define STRUCT_BLOCK_SIZE	sizeof(t_block)
#define STRUCT_ZONE_SIZE	sizeof(t_zone)
#define STRUCT_LARGE_SIZE	sizeof(t_large)

#define BLOCKS_PER_ZONE 3

#define BLOCK_LENGTH_TINY_MIN	1
#define BLOCK_LENGTH_TINY_MAX	1024
#define BLOCK_LENGTH_SMALL_MIN	(BLOCK_LENGTH_TINY_MAX + 1)
#define BLOCK_LENGTH_SMALL_MAX	8192
#define BLOCK_LENGTH_LARGE_MIN	(BLOCK_LENGTH_SMALL_MAX + 1)

#define ZONE_TOTAL_SIZE_MIN(block_length_max) 	STRUCT_ZONE_SIZE + BLOCKS_PER_ZONE * (STRUCT_BLOCK_SIZE + block_length_max)
#define ZONE_TOTAL_SIZE_TINY					ZONE_TOTAL_SIZE_MIN(BLOCK_LENGTH_TINY_MAX) + PAGESIZE - (ZONE_TOTAL_SIZE_MIN(BLOCK_LENGTH_TINY_MAX) % PAGESIZE)
#define ZONE_TOTAL_SIZE_SMALL					ZONE_TOTAL_SIZE_MIN(BLOCK_LENGTH_SMALL_MAX) + PAGESIZE - (ZONE_TOTAL_SIZE_MIN(BLOCK_LENGTH_SMALL_MAX) % PAGESIZE)

#define ZONE_DATA_START(zone)		(void *)zone + STRUCT_ZONE_SIZE + STRUCT_BLOCK_SIZE
#define ZONE_DATA_START_TINY(zone)	ZONE_DATA_START(zone)
#define ZONE_DATA_START_SMALL(zone)	ZONE_DATA_START(zone)
#define ZONE_DATA_END_TINY(zone)	(void *)zone + ZONE_TOTAL_SIZE_TINY
#define ZONE_DATA_END_SMALL(zone)	(void *)zone + ZONE_TOTAL_SIZE_SMALL

typedef struct				s_block
{
	bool					free;
	size_t					size;
	struct s_block*			prev;
	struct s_block*			next;
}							t_block;

typedef struct				s_zone {
	t_block*				blocks;
	struct s_zone*			prev;
	struct s_zone*			next;
}							t_zone;

typedef struct				s_large {
	size_t					size;
	struct s_large*			prev;
	struct s_large*			next;
}							t_large;

t_zone						g_zones[5];
// [0] : tiny   > first
// [1] : tiny      > last
// [2] : small  > first
// [3] : small     > last
// [4] : large  > first

t_zone*						g_tiny_first_zone;
t_zone*						g_tiny_last_zone;
t_zone*						g_small_first_zone;
t_zone*						g_small_last_zone;
t_large*					g_larges;

extern 						pthread_mutex_t g_lock;

// ---------------------------------------------------------- free.c
void		ft_free(void *ptr);
// ---------------------------------------------------------- large.c
t_large 	*ft_find_large_from_a_pointer(void *ptr);
void 		ft_free_large(t_large *large);
// ---------------------------------------------------------- malloc.c
void		*ft_malloc(size_t size);
// ---------------------------------------------------------- realloc.c
void		*ft_realloc(void *ptr, size_t size);
// ---------------------------------------------------------- show.c
void		show_alloc_mem(void);
// ---------------------------------------------------------- zone.c
t_zone		*ft_find_zone_from_a_pointer(void *ptr, int *zone_type);
t_block		*ft_find_the_optimal_free_block_in_zones(size_t size, t_zone *zone);
t_block 	*ft_find_block_in_a_zone_from_ptr(void *ptr, t_zone *zone);
t_zone		*ft_malloc_zone(t_zone *prev_zone, int zone_len);
int 		ft_free_zone(t_zone *zone, int zone_type);
void		ft_show_zones();
// ---------------------------------------------------------- block.c
void 		ft_split_block(t_block *block, size_t size);
void 		ft_shift_next_block(t_block *block, size_t size);
t_block		*ft_malloc_block(t_block *block, size_t size);
void 		ft_merge_surrounding_free_blocks(t_block *block);
void 		ft_merge_previous_free_block(t_block *block);
void 		ft_merge_next_free_block(t_block *block);
void		ft_free_block(t_block *block);

#endif