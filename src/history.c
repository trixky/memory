#include "libft_malloc.h"

void ft_shift_history() {
    g_.actions++;
    for (int i = HISTORY_SIZE - 1; i > 0; i--)
        g_.history[i] = g_.history[i - 1];
}

void ft_push_malloc_error_in_history(size_t size) {
    ft_shift_history();
    
    g_.history[0].type = MALLOC;
    g_.history[0].size = size;
    g_.history[0].address = NULL;
    g_.history[0].zone_type = NOWHERE;
    g_.history[0].block_or_large = NULL;
    g_.history[0].zone = NULL;
    g_.history[0].error = true;
}

void ft_push_malloc_in_history(void *address, size_t size, int zone_type, void *block_or_large, t_zone *zone) {
    ft_shift_history();
    
    g_.history[0].type = MALLOC;
    g_.history[0].address = address;
    g_.history[0].size = size;
    g_.history[0].zone_type = zone_type;
    g_.history[0].block_or_large = block_or_large;
    g_.history[0].zone = zone;
    g_.history[0].error = false;
}

void ft_push_free_error_in_history(void *address) {
    ft_shift_history();
    
    g_.history[0].type = FREE;
    g_.history[0].address = address;
    g_.history[0].size = 0;
    g_.history[0].zone_type = NOWHERE;
    g_.history[0].block_or_large = NULL;
    g_.history[0].zone = NULL;
    g_.history[0].error = true;
    g_.history[0].option = false;
}

void ft_push_free_in_history(void *address, size_t size, int zone_type, void *block_or_large, t_zone *zone, int zone_freed) {
    ft_shift_history();
    
    g_.history[0].type = FREE;
    g_.history[0].address = address;
    g_.history[0].size = size;
    g_.history[0].zone_type = zone_type;
    g_.history[0].block_or_large = block_or_large;
    g_.history[0].zone = zone;
    g_.history[0].error = false;
    g_.history[0].option = zone_freed;
}

void ft_push_realloc_error_in_history(void *address, size_t new_size) {
    ft_shift_history();
    
    g_.history[0].type = REALLOC;
    g_.history[0].size = 0;
    g_.history[0].new_size = new_size;
    g_.history[0].address = address;
    g_.history[0].new_address = NULL;
    g_.history[0].zone_type = NOWHERE;
    g_.history[0].new_zone_type = NOWHERE;
    g_.history[0].block_or_large = NULL;
    g_.history[0].new_block_or_large = NULL;
    g_.history[0].zone = NULL;
    g_.history[0].new_zone = NULL;
    g_.history[0].error = true;
}


void ft_push_realloc_in_history(void *address, void *new_address, size_t size, size_t new_size, int zone_type, int new_zone_type, void *block_or_large, void *new_block_or_large, t_zone *zone, t_zone *new_zone, bool error) {
    ft_shift_history();
    
    g_.history[0].type = REALLOC;
    g_.history[0].size = size;
    g_.history[0].new_size = new_size;
    g_.history[0].address = address;
    g_.history[0].new_address = new_address;
    g_.history[0].zone_type = zone_type;
    g_.history[0].new_zone_type = new_zone_type;
    g_.history[0].block_or_large = block_or_large;
    g_.history[0].new_block_or_large = new_block_or_large;
    g_.history[0].zone = zone;
    g_.history[0].new_zone = new_zone;
    g_.history[0].error = error || (new_address == NULL && new_size > 0);
}
