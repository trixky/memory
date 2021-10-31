#include "libft_malloc.h"

int main() {
    printf("sizeof(char) = %ld\n", sizeof(char));
    printf("STRUCT_ZONE_SIZE = %ld\n", STRUCT_ZONE_SIZE);
    printf("STRUCT_BLOCK_SIZE = %ld\n", STRUCT_BLOCK_SIZE);
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ STARt\n");

    // -------------------------
    void *ptra = malloc(0);
    void *ptrb = malloc(30);
    void *ptr0 = malloc(1001);
    void *ptr1 = malloc(1002);
    void *ptr2 = malloc(1003);
    void *ptr3 = malloc(1004);
    void *ptr4 = malloc(1005);


    void *ptr5 = malloc(8000);
    void *ptr6 = malloc(8000);
    void *ptr7 = malloc(8000);
    void *ptr8 = malloc(8000);

    void *ptr9 = malloc(20000);
    void *ptr10 = malloc(30000);

    ptr1 = realloc(ptr1, 1003);
    void *ptrc1 = malloc(1006);
    printf("ptrc1 = %p\n", ptrc1);
    ptrc1 = realloc(ptrc1, 742);
    ptrb = realloc(ptrb, 31);

    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ show_alloc_mem_ex\n");
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ show_alloc_mem_ex\n");
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ show_alloc_mem_ex\n");
    show_alloc_mem_ex();

    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ show_alloc_mem\n");
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ show_alloc_mem\n");
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ show_alloc_mem\n");
    show_alloc_mem();
}