#include "./includes/libft_malloc.h"
#include <stdlib.h>

int main() {
    printf("sizeof(char) = %ld\n", sizeof(char));
    printf("STRUCT_ZONE_SIZE = %ld\n", STRUCT_ZONE_SIZE);
    printf("STRUCT_BLOCK_SIZE = %ld\n", STRUCT_BLOCK_SIZE);
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ STARt\n");

    // -------------------------
    void *ptra = ft_malloc(0);
    void *ptrb = ft_malloc(30);
    void *ptr0 = ft_malloc(1001);
    void *ptr1 = ft_malloc(1002);
    void *ptr2 = ft_malloc(1003);
    void *ptr3 = ft_malloc(1004);
    void *ptr4 = ft_malloc(1005);


    void *ptr5 = ft_malloc(8000);
    void *ptr6 = ft_malloc(8000);
    void *ptr7 = ft_malloc(8000);
    void *ptr8 = ft_malloc(8000);

    void *ptr9 = ft_malloc(20000);
    void *ptr10 = ft_malloc(30000);

    ptr1 = ft_realloc(ptr1, 1003);
    void *ptrc1 = ft_malloc(1006);
    printf("ptrc1 = %p\n", ptrc1);
    ptrc1 = ft_realloc(ptrc1, 742);
    ptrb = ft_realloc(ptrb, 31);

    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ show_alloc_mem_ex\n");
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ show_alloc_mem_ex\n");
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ show_alloc_mem_ex\n");
    show_alloc_mem_ex();

    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ show_alloc_mem\n");
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ show_alloc_mem\n");
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ show_alloc_mem\n");
    show_alloc_mem();
}