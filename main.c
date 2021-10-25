#include "./includes/memory_handler.h"
#include <stdlib.h>

int main() {
    printf("sizeof(char) = %ld\n", sizeof(char));
    printf("STRUCT_ZONE_SIZE = %ld\n", STRUCT_ZONE_SIZE);
    printf("STRUCT_BLOCK_SIZE = %ld\n", STRUCT_BLOCK_SIZE);
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ STARt\n");

    // -------------------------    
    void *ptr0 = ft_malloc(16);
    void *ptr1 = ft_malloc(800);
    void *ptr2 = ft_malloc(150);

    // -------------------------    

    // ft_free(ptr0);
    ft_free(ptr1);
    ft_realloc(ptr0, 18);
    // ft_free(ptr2);

    ft_show_zones();
}