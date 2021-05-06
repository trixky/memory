#ifndef _MEMORY_HANDLER_H
# define _MEMORY_HANDLER_H

#include <unistd.h>
#include <stdbool.h>
// getpagesize
#include <sys/mman.h>
// mmap
// munmap

#include <stdio.h>
// printf

#define AREA_MIN_SIZE 100
#define TINY_AREA_LEN AREA_MIN_SIZE
#define SMALL_AREA_LEN AREA_MIN_SIZE

#define TINY_ALLOC_MIN	1
#define TINY_ALLOC_MAX	4
#define SMALL_ALLOC_MIN	5
#define SMALL_ALLOC_MAX	64
#define LARGE_ALLOC_MIN	65


typedef struct	s_piles
{
	int			time;
	int			brute_force_array[3];
	int			brute_force_array_save[3];
}				t_piles;

typedef struct	s_alloc {
	bool		allocated;
}				t_alloc;

typedef struct	s_tiny_area {
	void		*ptr_start;
	void		*ptr_next;
}				t_tiny_area;

void ft_free(void *ptr);
void *ft_malloc(size_t size);
void *ft_realloc(void *ptr, size_t size);

#endif