#include "../includes/libft_malloc.h"

size_t			ft_strlen(const char *s)
{
	const char *ptr;

	ptr = s;
	while (*ptr)
		++ptr;
	return (ptr - s);
}

void			ft_putnbr(size_t n)
{
	int				i;
	char			str[12];
	size_t			nnbr;
	int				size;

	size = 0;
	nnbr = n;
	while (nnbr)
		nnbr /= 10 + 0 * size++;
	nnbr = n;
	if (!size)
		str[size++] = '0';
	str[size] = '\0';
	i = size;
	while (i--)
	{
		str[i] = (nnbr % 10) + 48;
		nnbr /= 10;
	}
	write(STDOUT_FILENO, str, ft_strlen(str));
}

void			ft_puthexa(unsigned long n)
{
	int				i;
	char			str[20];
	unsigned long	nnbr;
	int				size;

	size = 0;
	nnbr = n;
	while (n)
		n /= 16 + 0 * size++;
	if (!size)
		str[size++] = '0';
	str[size] = '\0';
	i = size;
	n = nnbr;
	while (i--)
	{
		if (nnbr % 16 < 10)
			str[i] = (nnbr % 16) + 48;
		else
			str[i] = (nnbr % 16) + (65 - 10);
		nnbr /= 16;
	}
	write(STDOUT_FILENO, str, ft_strlen(str));
}

size_t		print_block(t_block *block)
{
	write(STDOUT_FILENO, "0x", 2);
	ft_puthexa((unsigned long)block + STRUCT_BLOCK_SIZE);
	write(STDOUT_FILENO, " - ", 3);
	write(STDOUT_FILENO, "0x", 2);
	ft_puthexa((unsigned long)block + STRUCT_BLOCK_SIZE + block->size);
	write(STDOUT_FILENO, " : ", 3);
	ft_putnbr(block->size);
	write(STDOUT_FILENO, " octets\n", 8);
	return (block->size);
}

size_t		print_large(t_large *large)
{
	write(STDOUT_FILENO, "0x", 2);
	ft_puthexa((unsigned long)large + STRUCT_LARGE_SIZE);
	write(STDOUT_FILENO, " - ", 3);
	write(STDOUT_FILENO, "0x", 2);
	ft_puthexa((unsigned long)large + STRUCT_LARGE_SIZE + large->size);
	write(STDOUT_FILENO, " : ", 3);
	ft_putnbr(large->size);
	write(STDOUT_FILENO, " octets\n", 8);
	return (large->size);
}

size_t        ft_print_zones(int zone_type) {
    size_t      size = 0;
	t_block		*block;

	t_zone *zone;
	char *header;
	size_t header_size;

	if (zone_type == TINY) {
		zone = g_.g_tiny_first_zone;
		header = "TINY : 0x";
		header_size = 9;
	}
	else {
		zone = g_.g_small_first_zone;
		header = "SMALL : 0x";
		header_size = 10;
	}

	while (zone) {
		write(STDOUT_FILENO, header, header_size);
		ft_puthexa((unsigned long)zone + STRUCT_ZONE_SIZE);
		write(STDOUT_FILENO, "\n", 1);

		block = zone->blocks;
		while (block)
		{
			size += print_block(block);
			block = block->next;
		}

		zone = zone->next;
	}
    
    return size;
}

size_t		ft_print_larges(void) {
	size_t size = 0;
	t_large *large = g_.g_larges;

	while (large) {
		write(STDOUT_FILENO, "LARGE : 0x", 10);
		ft_puthexa((unsigned long)large + STRUCT_ZONE_SIZE);
		write(STDOUT_FILENO, "\n", 1);

		size += print_large(large);

		large = large->next;
	}

	return size;
}

void		show_alloc_mem(void)
{
	size_t		total = 0;

	pthread_mutex_lock(&g_lock);		// LOCK
    total += ft_print_zones(TINY);
    total += ft_print_zones(SMALL);
    total += ft_print_larges();

	write(STDOUT_FILENO, "Total : ", 8);
	ft_putnbr(total);
	write(STDOUT_FILENO, " octets\n", 8);
	pthread_mutex_unlock(&g_lock);		// UNLOCK
}

void ft_show_zone(t_zone *zone) {
    if (zone) {
        t_block *block;
        block = zone->blocks;
        while (block) {
			printf(ANSI_COLOR_YELLOW "      block " ANSI_COLOR_RESET "%p :\n" , block);
            printf("         prev : %p\n", block->prev);
            printf("         free : %s\t%s: " ANSI_COLOR_GREEN "%ld\n" ANSI_COLOR_RESET, block->free ? ANSI_COLOR_BLUE "true" ANSI_COLOR_RESET: ANSI_COLOR_RED "false" ANSI_COLOR_RESET, block->size != 0 ? "bytes" : "byte", block->size);
            printf("         next : %p\n", block->next);


            block = block->next;
        }
		printf("\n");
    }
}

void ft_show_large(t_large *large) {
	if (large) {
		printf(ANSI_COLOR_YELLOW "      block " ANSI_COLOR_RESET "%p :\n" , large);
		printf("         prev : %p\n", large->prev);
		printf("         %s: " ANSI_COLOR_GREEN "%ld\n" ANSI_COLOR_RESET, large->size != 0 ? "bytes" : "byte", large->size);
		printf("         next : %p\n\n", large->next);
	}
}

void show_alloc_mem_ex(void) {
	pthread_mutex_lock(&g_lock);		// LOCK
    printf("\n===============================================\n");
    printf("============== show_alloc_mem_ex ==============\n");
    printf("===============================================\n\n");
    t_zone *zone = g_.g_tiny_first_zone;
	if (zone) {
		printf(ANSI_COLOR_YELLOW "tiny" ANSI_COLOR_RESET " :\n");
		while (zone) {
			printf(ANSI_COLOR_YELLOW "   zone " ANSI_COLOR_RESET "%p :\n" , zone);
			ft_show_zone(zone);
			zone = zone->next;
		}
	}
    zone = g_.g_small_first_zone;
	if (zone) {
    	printf(ANSI_COLOR_YELLOW "small" ANSI_COLOR_RESET " :\n");
		while (zone) {
			printf(ANSI_COLOR_YELLOW "   zone " ANSI_COLOR_RESET "%p :\n" , zone);
			ft_show_zone(zone);
			zone = zone->next;
		}
	}
    t_large *large = g_.g_larges;
	if (large) {
		printf(ANSI_COLOR_YELLOW "large" ANSI_COLOR_RESET " :\n");
		while (large) {
			ft_show_large(large);
			large = large->next;
		}
	}
	pthread_mutex_unlock(&g_lock);		// UNLOCK
}