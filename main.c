#include "./includes/libft_malloc.h"
#include <stdlib.h>

int main() {
    printf("sizeof(char) = %ld\n", sizeof(char));
    printf("STRUCT_ZONE_SIZE = %ld\n", STRUCT_ZONE_SIZE);
    printf("STRUCT_BLOCK_SIZE = %ld\n", STRUCT_BLOCK_SIZE);
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ STARt\n");

    // -------------------------
    void *ptr0 = ft_malloc(1000);
    void *ptr1 = ft_malloc(1000);
    void *ptr2 = ft_malloc(1000);
    void *ptr3 = ft_malloc(1000);
    void *ptr4 = ft_malloc(1000);


    void *ptr5 = ft_malloc(8000);
    void *ptr6 = ft_malloc(8000);
    void *ptr7 = ft_malloc(8000);
    void *ptr8 = ft_malloc(8000);

    void *ptr9 = ft_malloc(20000);
    void *ptr10 = ft_malloc(30000);

    // -------------------------    
    // void *ptr0 = ft_malloc(100);
    // void *ptr1 = ft_malloc(800);
    // void *ptr2 = ft_malloc(150);
    // void *ptr3 = ft_malloc(900);
    // void *ptr4 = ft_malloc(500);
    // void *ptr5 = ft_malloc(1000);
    // void *ptr6 = ft_malloc(398);

    // void *ptrl1 = ft_malloc(20000);
    // void *ptrl2 = ft_malloc(20020);
    // void *ptrl3 = ft_malloc(20040);

    // -------------------------    

    // ft_free(ptr0);
    // ft_free(ptr1);
    // ft_free(ptr5);
    // ft_realloc(ptr3, 1000);
    // ft_realloc(ptr0, 400);
    // ft_free(ptr2);

    // ft_realloc(ptrl1, 9000);
    // ft_realloc(ptr6, 12000);

    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ show_alloc_mem_ex\n");
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ show_alloc_mem_ex\n");
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ show_alloc_mem_ex\n");
    show_alloc_mem_ex();

    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ show_alloc_mem\n");
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ show_alloc_mem\n");
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ show_alloc_mem\n");
    show_alloc_mem();
}