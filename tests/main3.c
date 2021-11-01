#include <stdlib.h>
#include "../includes/libft_malloc.h"

int main() {
    // -------------------------

    int i;

    void *addr1 = malloc(1020);
    void *addr2 = malloc(1021);
    void *addr3 = malloc(1022);
    void *addr4 = malloc(1023);
    free(addr2);
    free(addr3);
    free(addr4);
    free(addr1);

    // show_alloc_mem_ex();
    show_alloc_mem();
}