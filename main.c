#include "./includes/memory_handler.h"

int main() {
    printf("=========================================\n");

    // ft_malloc(257);
    ft_malloc(16);
    void *ptr = ft_malloc(200);
    void *ptr2 = ft_malloc(16);
    void *ptr3 = ft_malloc(28632);
    // ft_malloc(28680);
    // ft_malloc(100);
    // ft_malloc(100);
    // ft_malloc(100);
    // ft_malloc(100);
    // ft_malloc(1000);
    // ft_malloc(16);
    // ft_realloc(NULL, 0);
    // ft_free(NULL);

    ft_free(ptr);
    ft_free(ptr2);

    printf("=========================================\n");
    // ft_show_zone(g_small_zones);
    ft_show_zone(g_tiny_zones);
    printf("=========================================\n");
}