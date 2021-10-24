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
    void *ptr2 = ft_malloc(222);


    // -------------------------    
    // void *ptr6 = ft_malloc(900);
    // void *ptr7 = ft_malloc(1020);
    // void *ptr8 = ft_malloc(960);
    // void *ptr9 = ft_malloc(970);
    // void *ptrx = ft_malloc(16);

    ft_free(ptr1);
    // ft_free(ptr5 + 50);
    // ft_free(ptr4);
    // ft_free(ptr2);

    // ptr1 = ft_malloc(128);

    // ft_free(ptr3);

    // ft_free(ptr1);

    ft_show_zones();
}