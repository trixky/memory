#include "../includes/memory_handler.h"

t_block *ft_get_last_m_block(t_zone *zone) {
    t_block *ptr = zone->m_blocks;
    
    while (ptr && ptr->next) {
        ptr = ptr->next;
    }

    return ptr;
}

t_block *ft_get_last_f_block(t_zone *zone) {
    t_block *ptr = zone->f_blocks;
    
    while (ptr && ptr->next) {
        ptr = ptr->next;
    }

    return ptr;
}

t_block *ft_create_block(t_zone *zone, size_t size, int block_len_min) {
    printf("\n********** ft_create_block **********\n");
    int split_size = size + sizeof(t_block) + block_len_min - 1;
    t_block *f_ptr_prev = NULL;
    t_block *f_ptr_curr = zone->f_blocks;

    // find a f_block
    while (f_ptr_curr &&
           (f_ptr_curr->size < size ||
            (f_ptr_curr->size > size &&
             f_ptr_curr->size < split_size))) {
        f_ptr_prev = f_ptr_curr;
        f_ptr_curr = f_ptr_curr->next;
    }

    // if a f_block finded
    if (f_ptr_curr) {
    // keep a copy the finded f_block
        t_block f_ptr_curr_copy;
        f_ptr_curr_copy.size = f_ptr_curr->size;
        f_ptr_curr_copy.next = f_ptr_curr->next;

    // push a m_block on the top of the pile
        // if there is no m_block in the stack
        if (zone->m_blocks) {
            t_block *m_ptr_prev = zone->m_blocks;
            zone->m_blocks = f_ptr_curr;
            zone->m_blocks->next = m_ptr_prev;
        // else there is a block in the stack
        } else {
            zone->m_blocks = f_ptr_curr;
            zone->m_blocks->next = NULL;
        }

    // delete or split the f_block
        // if the f_block is the perfect size or too short to split
        if (f_ptr_curr_copy.size == size || f_ptr_curr_copy.size - sizeof(t_block) <= size) {
        // delete the f_block
        // set the size of the new m_block to size
            zone->m_blocks->size = f_ptr_curr_copy.size;
        // link the previous f_block to the next
            if (!f_ptr_prev) {
                zone->f_blocks = f_ptr_curr_copy.next;
            }
            else {
                f_ptr_prev->next = f_ptr_curr_copy.next;
            }
        }
        // else the block is bigger than the size
        else {
        // split the f_block
        // set the size of the new m_block to size
            zone->m_blocks->size = size;
        // create a new f_block from the extra current f_block
            f_ptr_curr = (void *)(f_ptr_curr + 1) + size;
            f_ptr_curr->size = f_ptr_curr_copy.size - sizeof(t_block) - size;
        // link the previous f_block to the next
            if (!f_ptr_prev) {
                zone->f_blocks = f_ptr_curr;
            } else {
                f_ptr_prev->next = f_ptr_curr;
            }
        }
        return zone->m_blocks;
    }
    return NULL;
}

// t_block *ft_find

t_block *ft_destroy_block(t_zone *zone, t_block *block) {
    printf("\n********** ft_destroy_block **********\n");
    // ATTENTION A ITERER SUR TOUTES LES ZONES
    t_zone *ptr_zone = zone;
    t_block *ptr_block = zone->m_blocks;
    while (ptr_zone) {
        while (ptr_block) {
            if (ptr_block == block) {
                goto STOP;
            }
            ptr_block = ptr_block->next;
        }
        ptr_zone = ptr_zone->next;
    }
    STOP:


}
