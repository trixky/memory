#include "../includes/libft_malloc.h"

int main() {
    printf("sizeof(char) = %ld\n", sizeof(char));
    printf("STRUCT_ZONE_SIZE = %ld\n", STRUCT_ZONE_SIZE);
    printf("STRUCT_BLOCK_SIZE = %ld\n", STRUCT_BLOCK_SIZE);
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ STARt\n");

    // -------------------------

    int i;
    char *addr;

    i = 0;
    while (i < 10) {
        addr = (char*)malloc(2000);

        addr[0] = 42;
        free(addr);
        i++;
    }

    // for (int i = 0; i < 10; i++) {
    //     char *ptra = (char *)malloc(16);
    //     ptra[0] = 42;
    //     free(ptra);
    // }

    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ show_alloc_mem_ex\n");
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ show_alloc_mem_ex\n");
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ show_alloc_mem_ex\n");
    show_alloc_mem_ex();
}