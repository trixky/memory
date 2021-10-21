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

    int split_size = size + sizeof(t_block) + block_len_min;
    t_block *f_ptr_prev = NULL;
    t_block *f_ptr_curr = zone->f_blocks;

    printf("f_ptr_curr = %ld\n", sizeof(t_block));
    printf("f_ptr_curr = %p\n", f_ptr_curr);
    printf("f_ptr_curr + 1 = %p\n", f_ptr_curr + 1);
    printf("f_ptr_curr + 1* = %p\n", (void *)(f_ptr_curr + 1) + 1);

    while (f_ptr_curr &&
           (f_ptr_curr->size < size ||
            (f_ptr_curr->size > size &&
             f_ptr_curr->size < split_size))) {
        f_ptr_prev = f_ptr_curr;
        f_ptr_curr = f_ptr_curr->next;
    }

    if (f_ptr_curr) {
        if (zone->m_blocks) {
            t_block *m_ptr_prev = zone->m_blocks;
            zone->m_blocks = f_ptr_curr;
            zone->m_blocks->size = size;
            zone->m_blocks->next = m_ptr_prev;
        } else {
            zone->m_blocks = f_ptr_curr;
            zone->m_blocks->size = size;
            zone->m_blocks->next = NULL;
        }
        if (f_ptr_curr->size == size) {
            if (!f_ptr_prev) {
                zone->f_blocks = f_ptr_curr->next;
            }
            else {
                f_ptr_prev->next = f_ptr_curr->next;
            }
        }
        else {
            f_ptr_curr = (void *)(f_ptr_curr + 1) + size;
        }
    }
    return NULL;
}
