#include "./includes/memory_handler.h"

int main() {
    ft_malloc(257);
    ft_malloc(16);
    ft_malloc(16);
    ft_realloc(NULL, 0);
    ft_free(NULL);
}