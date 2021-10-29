#include "../includes/libft_malloc.h"

void ft_copy_data(void *data_src, void *data_dst, size_t len) {
    for (size_t i = 0; i < len; i++)
        ((char *)data_dst)[i] = ((char *)data_src)[i];
}

void *ft_realloc(void *ptr, size_t size) {
    if (ptr) {
        pthread_mutex_lock(&g_lock);            // LOCK
        int zone_type;
        t_zone *zone = ft_find_zone_from_a_pointer(ptr, &zone_type);

        if (zone) {
            t_block *block = ft_find_block_in_a_zone_from_ptr(ptr, zone);

            if (block && block->size != size) {
                if (size < block->size) { // plus petit
                    if (size + STRUCT_BLOCK_SIZE < block->size) // plus petit | on split
                        ft_split_block(block, size);
                    else if (block->next && block->next->free) // plus petit | on split pas
                        ft_shift_next_block(block, size);
                }
                else if (block->next && block->next->free && size < block->size + block->next->size + STRUCT_BLOCK_SIZE) { // plus grand
                    if (size < block->size + block->next->size) // on prend sur le next block free | on split
                        ft_shift_next_block(block, size);
                    else // on prend sur le next block free | on split pas
                        ft_merge_next_free_block(block);
                }
                else { // trop grand
                    ptr = ft_malloc(size);
                    ft_copy_data(block + 1, ptr, block->size < size ? block->size : size);
                    ft_free_block(block);
                }
            }
        }
        else {
            t_large *large = ft_find_large_from_a_pointer(ptr);

            if (large && large->size != size) {
                ptr = ft_malloc(size);
                ft_copy_data(large + 1, ptr, large->size < size ? large->size : size);
                ft_free_large(large);
            }
        }
        pthread_mutex_unlock(&g_lock);          // UNLOCK


        return ptr;
    }
}
