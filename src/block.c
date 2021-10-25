#include "../includes/memory_handler.h"

inline void ft_split_block(t_block *block, size_t size) {
    t_block *block_split = (void *)(block + 1) + size;

    block_split->free = true;
    block_split->size = block->size - STRUCT_BLOCK_SIZE - size;
    block_split->next = block->next;
    block_split->previous = block;
    block->size = size;
    block->next = block_split;
}

t_block *ft_malloc_block(t_block *block, size_t size) {
    if (block) {
        if (block) {
            block->free = false;
            if (block->size > size + STRUCT_BLOCK_SIZE) {
                t_block *block_split = (void *)(block + 1) + size;

                block_split->free = true;
                block_split->size = block->size - STRUCT_BLOCK_SIZE - size;
                block_split->next = block->next;
                block_split->previous = block;
                block->size = size;
                block->next = block_split;
            }

            return block;
        }
    }

    return NULL;
}

inline void ft_merge_surrounding_free_blocks(t_block *block) {
    if (block->next->next) {
        block->next->next->previous = block->previous;
    }
    block->previous->size += STRUCT_BLOCK_SIZE * 2 + block->size + block->next->size;
    block->previous->next = block->next->next;
}

inline void ft_merge_previous_free_block(t_block *block) {
    if (block->next) {
        block->next->previous = block->previous;
    }
    block->previous->size += STRUCT_BLOCK_SIZE + block->size;
    block->previous->next = block->next;
}

inline void ft_merge_next_free_block(t_block *block) {
    if (block->next->next) {
        block->next->next->previous = block;
    }
    block->size += STRUCT_BLOCK_SIZE + block->next->size;
    block->next = block->next->next;
}

void ft_free_block(t_block *block) {
    if (block->previous && block->next) {
        if (block->previous->free) {
            if (block->next->free)
                merge_surrounding: ft_merge_surrounding_free_blocks(block);
            else
                merge_previous: ft_merge_previous_free_block(block);
            goto skip_set_free;
        }
        else if (block->next->free)
            merge_next: ft_merge_next_free_block(block);
    }
    else if (block->previous && block->previous->free)
        goto merge_previous;
    else if (block->next && block->next->free)
        goto merge_next;

    block->free = true;

    skip_set_free: return ;
}

void ft_copy_block(t_block *block_src, t_block *block_dst) {
    char *ptr_data_src = (char *)(block_src + 1);
    char *ptr_data_dst = (char *)(block_dst + 1);

    if (block_src && block_dst)
        for (long int i = block_src->size < block_dst->size ? block_src->size : block_dst->size; i > 0; i--)
            *(ptr_data_dst + i) = *(ptr_data_src + i);
}