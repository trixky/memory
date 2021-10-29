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
    size_t      ret = 0;
	t_block		*block;

	t_zone *zone;
	char *header;
	size_t header_size;

	if (zone_type == TINY) {
		zone = g_tiny_first_zone;
		header = "TINY : 0x";
		header_size = 9;
	}
	else {
		zone = g_small_first_zone;
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
			ret += print_block(block);
			block = block->next;
		}

		zone = zone->next;
	}
    
    return ret;
}

size_t		ft_print_larges() {
	size_t ret = 0;
	t_large *large = g_larges;

	while (large) {
		write(STDOUT_FILENO, "LARGE : 0x", 10);
		ft_puthexa((unsigned long)large + STRUCT_ZONE_SIZE);
		write(STDOUT_FILENO, "\n", 1);

		ret += print_large(large);

		large = large->next;
	}

	return ret;
}

void		show_alloc_mem(void)
{
	size_t		total = 0;

	pthread_mutex_lock(&g_lock);		// LOCK
    total += ft_print_zones(TINY);
    total += ft_print_zones(SMALL);
    total += ft_print_larges();
	pthread_mutex_unlock(&g_lock);		// UNLOCK

	write(STDOUT_FILENO, "Total : ", 8);
	ft_putnbr(total);
	write(STDOUT_FILENO, " octets\n", 8);
}