#include "libft_malloc.h"

void ft_copy_data(void *data_src, void *data_dst, size_t len) {
    for (size_t i = 0; i < len; i++)
        ((char *)data_dst)[i] = ((char *)data_src)[i];
}

void *ft_realloc_in_zones(void *ptr, size_t size, bool history) {
    int zone_type;
    t_zone *zone = ft_find_zone_from_pointer(ptr, &zone_type);
    
    if (zone) {
        t_block *block = ft_find_block_in_a_zone_from_pointer(ptr, zone);

        if (block && block->size != size) {
            if (size < block->size) {
                int old_size = block->size;
                if (size + STRUCT_BLOCK_SIZE < block->size)
                    ft_split_block(block, size);
                else if (block->next && block->next->free)
                    ft_shift_next_block(block, size);
                push_realloc_with_same_block: ft_push_realloc_in_history(ptr, ptr, old_size, size, zone_type, zone_type, block, block, zone, zone, false);
            }
            else if (block->next && block->next->free && size < block->size + block->next->size + STRUCT_BLOCK_SIZE && GET_ZONE_TYPE(size) == GET_ZONE_TYPE(block->size)) {
                if (size < block->size + block->next->size)
                    ft_shift_next_block(block, size);
                else
                    ft_merge_next_free_block(block);
                goto push_realloc_with_same_block;
            }
            else {
                void *old_ptr = ptr;

                if ((ptr = ft_malloc(size, false)) == NULL) {
                    if (history)
                        ft_push_realloc_error_in_history(ptr, size);

                    return NULL;
                }
                
                if (history)
                    ft_push_realloc_in_history(old_ptr, ptr, block->size, size, GET_ZONE_TYPE(block->size), GET_ZONE_TYPE(size), block, (t_block *)ptr - 1, zone, ft_find_zone_from_pointer(ptr, &zone_type), false);

                ft_copy_data(block + 1, ptr, block->size < size ? block->size : size);
                ft_free_block(block);

            }

            return ptr;
        }
    }

    return NULL;
}

void *ft_realloc_in_larges(void *ptr, size_t size, bool history) {
    t_large *large = ft_find_large_from_pointer(ptr);

    if (large) {
        if (large->size != size) {
            if ((ptr = ft_malloc(size, false)) == NULL) {
                if (history)
                    ft_push_realloc_error_in_history(ptr, size);

                return NULL;
            }

            void *old_ptr = ptr;
            if (history)
                ft_push_realloc_in_history(old_ptr, ptr, large->size, size, LARGE, GET_ZONE_TYPE(size), large, (t_block *)ptr - 1, NULL, NULL, false);
            
            ft_copy_data(large + 1, ptr, large->size < size ? large->size : size);
            ft_free_large(large);

            return ptr;
        }
    }
    if (history)
        ft_push_realloc_error_in_history(ptr, size);

    return NULL;
}

void *ft_realloc(void *ptr, size_t size, bool history) {
    if (ptr) {
        void *new_ptr = ft_realloc_in_zones(ptr, size, history);

        return new_ptr != NULL ? new_ptr : ft_realloc_in_larges(ptr, size, history);
    }

    return ft_malloc(size, true);
}

void *realloc(void *ptr, size_t size) {
    pthread_mutex_lock(&g_lock);        // LOCK
    ptr = ft_realloc(ptr, size, true);
    pthread_mutex_unlock(&g_lock);      // UNLOCK

    return ptr;
}