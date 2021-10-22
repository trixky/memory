#include "./includes/memory_handler.h"

int main() {
    printf("=========================================\n");

    // ft_malloc(257);
    ft_malloc(16);
    ft_malloc(32);
    // ft_malloc(29736);
    // ft_malloc(100);
    // ft_malloc(100);
    // ft_malloc(100);
    // ft_malloc(100);
    // ft_malloc(1000);
    // ft_malloc(16);
    // ft_realloc(NULL, 0);
    // ft_free(NULL);

    printf("=========================================\n");
    // ft_show_zone(g_small_zones);
    ft_show_zone(g_tiny_zones);
}