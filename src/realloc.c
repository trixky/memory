#include "../includes/memory_handler.h"

void *ft_realloc(void *ptr, size_t size) {
    printf("\n********** realloc **********\n");
    if (ptr) {
        int zone_type;
        t_zone *zone = ft_find_zone_from_a_pointer(ptr, &zone_type);

        if (zone) {
            t_block *block = ft_find_block_in_a_zone_from_ptr(ptr, zone);

            if (block) {
                printf("$$$$$$$$$$$$$$$$$ passage 1\n");
                if (size < block->size) {
                    if (size + STRUCT_BLOCK_SIZE < block->size) {
                        printf("$$$$$$$$$$$$$$$$$ passage 2\n");
                        block->size = size;
                        ft_split_block(block, size);
                    }
                    else if (block->next && block->next->free) { // mettre ca dans block ?
                        printf("$$$$$$$$$$$$$$$$$ passage 3\n");
                        t_block block_next_copie = *(block->next);

                        block->next = (void *)(block + 1) + size;
                        block->next->free = true;
                        block->next->size = block->size - size + block_next_copie.size;
                        block->next->previous = block;
                        block->next->next = block_next_copie.next;

                        block->size = size;
                    }
                }
                else if (block->next && block->next->free && size < block->size + block->next->size + STRUCT_BLOCK_SIZE) {
                    if (size < block->size + block->next->size) {
                        printf("$$$$$$$$$$$$$$$$$ passage 4 (tested)\n");
                    // ***** plus grand mais avec un block free suffisament grand derriere | on split
                        t_block block_next_copie = *(block->next);
                        block->next = (void *)(block + 1) + size;
                        block->next->free = true;
                        block->next->size = block_next_copie.size - (size - block->size);
                        block->next->previous = block;
                        block->next->next = block_next_copie.next;
                        block->size = size;
                    }
                    else {
                        printf("$$$$$$$$$$$$$$$$$ passage 5\n");
                    // ***** plus grand mais avec un block free suffisament grand derriere | on split pas
                        block->size += block->next->size + STRUCT_BLOCK_SIZE;
                        if (block->next->next)
                            block->next->next->previous = block;
                        block->next = block->next->next;
                    }
                }
                else {
                        printf("$$$$$$$$$$$$$$$$$ passage 6\n");
                // ***** plus grand et on trouve un autre block ailleur et on copie tout dessus et on free l'ancien
                    ptr = ft_malloc(size);
                    ft_copy_block(block, (t_block *)ptr - 1);
                    ft_free_block(block);
                }
            }
        }

        return ptr;
    }
}
