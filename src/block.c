#include "../includes/memory_handler.h"

t_block *ft_malloc_block(t_block *block, size_t size) {
    printf("\n********** ft_malloc_block **********\n");
    if (block) {
        if (block) {
            printf("################### 1\n");
            block->free = false;
            if (block->size > size + sizeof(t_block)) {
                printf("################### 2\n");
                t_block *block_split = (void *)(block + 1) + size;

                block_split->free = true;
                block_split->size = block->size - sizeof(t_block) - size;
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
    block->previous->size += sizeof(t_block) * 2 + block->size + block->next->size;
    block->previous->next = block->next->next;
}

inline void ft_merge_previous_free_block(t_block *block) {
    if (block->next) {
        block->next->previous = block->previous;
    }
    block->previous->size += sizeof(t_block) + block->size;
    block->previous->next = block->next;
}

inline void ft_merge_next_free_block(t_block *block) {
    if (block->next->next) {
        block->next->next->previous = block;
    }
    block->size += sizeof(t_block) + block->next->size;
    block->next = block->next->next;
}

void ft_destroy_block(t_block *block) {
    block -= 1;
    t_zone *ptr_zone = ft_find_zone_from_block(g_tiny_first_zone, block);

    if (block->previous && block->next)
        if (block->previous->free) {
            if (block->next->free)
                merge_surrounding: ft_merge_surrounding_free_blocks(block);
            else
                merge_previous: ft_merge_previous_free_block(block);
            goto skip_set_free;
        }
        else if (block->next->free)
            merge_next: ft_merge_next_free_block(block);
    else if (block->previous && block->previous->free)
        goto merge_previous;
    else if (block->next && block->next->free)
        goto merge_next;

    block->free = true;

    skip_set_free: return ;
}