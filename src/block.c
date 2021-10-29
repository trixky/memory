#include "../includes/libft_malloc.h"

inline void ft_split_block(t_block *block, size_t size) {
    t_block *block_split = (void *)(block + 1) + size;

    block_split->free = true;
    block_split->size = block->size - STRUCT_BLOCK_SIZE - size;
    block_split->next = block->next;
    block_split->prev = block;
    block->size = size;
    block->next = block_split;
}

inline void ft_shift_next_block(t_block *block, size_t size) {
    t_block block_next_copie = *(block->next);

    block->next = (void *)(block + 1) + size;
    block->next->free = true;
    block->next->size = block->size - size + block_next_copie.size;
    block->next->prev = block;
    block->next->next = block_next_copie.next;

    block->size = size;
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
                block_split->prev = block;
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
        block->next->next->prev = block->prev;
    }
    block->prev->size += STRUCT_BLOCK_SIZE * 2 + block->size + block->next->size;
    block->prev->next = block->next->next;
}

inline void ft_merge_previous_free_block(t_block *block) {
    if (block->next) {
        block->next->prev = block->prev;
    }
    block->prev->size += STRUCT_BLOCK_SIZE + block->size;
    block->prev->next = block->next;
}

inline void ft_merge_next_free_block(t_block *block) {
    if (block->next->next) {
        block->next->next->prev = block;
    }
    block->size += STRUCT_BLOCK_SIZE + block->next->size;
    block->next = block->next->next;
}

void ft_free_block(t_block *block) {
    if (block->prev && block->next) {
        if (block->prev->free) {
            if (block->next->free)
                merge_surrounding: ft_merge_surrounding_free_blocks(block);
            else
                merge_prev: ft_merge_previous_free_block(block);
            goto skip_set_free;
        }
        else if (block->next->free)
            merge_next: ft_merge_next_free_block(block);
    }
    else if (block->prev && block->prev->free)
        goto merge_prev;
    else if (block->next && block->next->free)
        goto merge_next;

    block->free = true;

    skip_set_free: return ;
}