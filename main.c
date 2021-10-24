#include "./includes/memory_handler.h"

int main() {
    printf("sizeof(t_zone) = %ld\n", sizeof(t_zone));
    printf("sizeof(t_block) = %ld\n", sizeof(t_block));
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ STARt\n");
    // ft_malloc(257);
    ft_malloc(16);
    ft_malloc(200);
    // void *ptr = ft_malloc(200);
    // void *ptr2 = ft_malloc(16);
    // void *ptr3 = ft_malloc(28632);

    // ft_free(ptr);
    // ft_free(ptr2);

    // ft_show_zone(g_small_first_zone);
    ft_show_zone(g_tiny_first_zone);
}