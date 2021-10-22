#include "../includes/memory_handler.h"

t_block *ft_create_block(t_zone *zone, size_t size, int block_len_min) {
    t_block *ptr_block = zone->blocks;

    while (ptr_block && (!ptr_block->free || ptr_block->size < size)) {
        ptr_block = ptr_block->next;
    }

    if (ptr_block) {
        ptr_block->free = false;
        if (ptr_block->size > size + sizeof(t_block)) {
            t_block *ptr_block_split = (void *)(ptr_block + 1) + size;

            ptr_block_split->free = true;
            ptr_block_split->size = ptr_block->size - sizeof(t_block) - size;
            ptr_block_split->next = ptr_block->next;
            ptr_block_split->previous = ptr_block;
            ptr_block->size = size;
            ptr_block->next = ptr_block_split;
        }
        zone->size++;

        return ptr_block;
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

t_block *ft_destroy_block(t_block *block) {
    t_zone *ptr_zone = ft_find_zone_from_block(g_tiny_zones, block);

    block->free = true;

    if (block->previous && block->next)
        if (block->previous->free)
            if (block->next->free)
                ft_merge_surrounding_free_blocks(block);
            else
                ft_merge_previous_free_block(block);
        else if (block->next->free)
            ft_merge_next_free_block(block);
    else if (block->previous && block->previous->free)
        ft_merge_previous_free_block(block);
    else if (block->next && block->next->free)
        ft_merge_next_free_block(block);

    return NULL;
}