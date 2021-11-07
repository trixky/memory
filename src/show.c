#include "libft_malloc.h"

size_t			ft_strlen(const char *str)
{
	const char *ptr;

	ptr = str;
	while (*ptr)
		++ptr;
	return (ptr - str);
}

void			ft_putnbr(size_t nbr)
{
	int				i;
	char			str[12];
	size_t			nnbr;
	int				size;

	size = 0;
	nnbr = nbr;
	while (nnbr)
		nnbr /= 10 + 0 * size++;
	nnbr = nbr;
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

void			ft_puthexa(unsigned long nbr)
{
	int				i;
	char			str[20];
	unsigned long	nnbr;
	int				size;

	size = 0;
	nnbr = nbr;
	while (nbr)
		nbr /= 16 + 0 * size++;
	if (!size)
		str[size++] = '0';
	str[size] = '\0';
	i = size;
	nbr = nnbr;
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

void		ft_putaddress(unsigned long nbr) {
	if (nbr == 0) {
		write(STDOUT_FILENO, "nil", 3);
	}
	else {
		write(STDOUT_FILENO, "0x", 2);
		ft_puthexa(nbr);
	}
}

size_t		ft_print_block(t_block *block)
{
	if (block && !block->free) {
		ft_putaddress((unsigned long)block + STRUCT_BLOCK_SIZE);
		write(STDOUT_FILENO, " - ", 3);
		ft_putaddress((unsigned long)block + STRUCT_BLOCK_SIZE + block->size);
		write(STDOUT_FILENO, " : ", 3);
		ft_putnbr(block->size);
		write(STDOUT_FILENO, " octets\n", 8);
		return (block->size);
	}

	return 0;
}

size_t		ft_print_large(t_large *large)
{
	if (large) {
		write(STDOUT_FILENO, "LARGE : ", 8);
		ft_putaddress((unsigned long)large + STRUCT_ZONE_SIZE);
		write(STDOUT_FILENO, "\n", 1);

		ft_putaddress((unsigned long)large + STRUCT_LARGE_SIZE);
		write(STDOUT_FILENO, " - ", 3);
		ft_putaddress((unsigned long)large + STRUCT_LARGE_SIZE + large->size);
		write(STDOUT_FILENO, " : ", 3);
		ft_putnbr(large->size);
		write(STDOUT_FILENO, " octets\n", 8);
		return (large->size);
	}

	return 0;
}

size_t        ft_print_zone(t_zone *zone, int zone_type) {
    size_t      size = 0;
	t_block		*block;

	if (zone_type == TINY)
		write(STDOUT_FILENO, "TINY : ", 7);
	else 
		write(STDOUT_FILENO, "SMALL : ", 8);

	ft_putaddress((unsigned long)zone + STRUCT_ZONE_SIZE);
	write(STDOUT_FILENO, "\n", 1);

	block = zone->blocks;
	while (block)
	{
		size += ft_print_block(block);
		block = block->next;
	}
    
    return size;
}

void		*ft_find_next_zone_or_large(void *ptr, int *type) {
	t_zone	*zone;
	t_large	*large;
	void	*best = NULL;

	zone = g_.tiny_first_zone;
	while (zone) {
		if ((void *)zone > ptr && ((void *)zone < best || best == NULL)) {
			*type = TINY;
			best = (void *)zone;
		}
		zone = zone->next;
	}

	zone = g_.small_first_zone;
	while (zone) {
		if ((void *)zone > ptr && ((void *)zone < best || best == NULL)) {
			*type = SMALL;
			best = (void *)zone;
		}
		zone = zone->next;
	}

	large = g_.larges;
	while (large) {
		if ((void *)large > ptr && ((void *)large < best || best == NULL)) {
			*type = LARGE;
			best = (void *)large;
		}
		large = large->next;
	}

	return best;
}

void		show_alloc_mem(void)
{
	size_t		total = 0;

	pthread_mutex_lock(&g_lock);		// LOCK

	void	*zone_or_large = NULL;
	int		zone_type;

	while ((zone_or_large = ft_find_next_zone_or_large(zone_or_large, &zone_type))) {
		if (zone_type != LARGE)
			total += ft_print_zone((t_zone *)zone_or_large, zone_type);
		else
			total += ft_print_large((t_large *)zone_or_large);
	}

	write(STDOUT_FILENO, "Total : ", 8);
	ft_putnbr(total);
	write(STDOUT_FILENO, " octets\n", 8);
	pthread_mutex_unlock(&g_lock);		// UNLOCK
}

void ft_show_error(bool error) {
	write(STDOUT_FILENO, "\n      error:\t\t", 15);
	if (error) {
		write(STDOUT_FILENO, ANSI_COLOR_RED, ANSI_COLOR_LEN);
		write(STDOUT_FILENO, "true", 4);
		write(STDOUT_FILENO, ANSI_COLOR_RESET, ANSI_COLOR_LEN);
	}
	else
		write(STDOUT_FILENO, "false", 5);
	write(STDOUT_FILENO, "\n", 1);
}

void ft_show_zone_type(int zone_type, int new_zone_type) {
	if (zone_type == TINY)
		write(STDOUT_FILENO, "tiny", 4);
	else if (zone_type == SMALL)
		write(STDOUT_FILENO, "small", 5);
	else if (zone_type == LARGE)
		write(STDOUT_FILENO, "large", 5);
	else
		write(STDOUT_FILENO, "nowhere", 7);
	
	if (new_zone_type != NOTHING) {
		write(STDOUT_FILENO, " > ", 3);
		if (new_zone_type == TINY)
			write(STDOUT_FILENO, "tiny", 4);
		else if (new_zone_type == SMALL)
			write(STDOUT_FILENO, "small", 5);
		else if (new_zone_type == LARGE)
			write(STDOUT_FILENO, "large", 5);
		else
			write(STDOUT_FILENO, "nowhere", 7);
	}
}

void ft_show_action_malloc(t_action *action) {
	write(STDOUT_FILENO, ANSI_COLOR_YELLOW, ANSI_COLOR_LEN);
	write(STDOUT_FILENO, "   action", 9);
	write(STDOUT_FILENO, ANSI_COLOR_RESET, ANSI_COLOR_LEN);
	write(STDOUT_FILENO, ": malloc\n", 9);

	write(STDOUT_FILENO, "      address:\t\t", 16);
	ft_putaddress((unsigned long)action->address);
	write(STDOUT_FILENO, "\n      bytes:\t\t", 15);
	ft_putnbr(action->size);
	write(STDOUT_FILENO, "\n      zone type:\t", 18);

	if (action->zone_type == LARGE) {
		write(STDOUT_FILENO, "large", 5);
		write(STDOUT_FILENO, "\n      block/zone:\t", 20);
		ft_putaddress((unsigned long)action->block_or_large);
	}
	else if (action->zone_type == NOWHERE) {
			write(STDOUT_FILENO, "nowhere", 7);
	}
	else {
		if (action->zone_type == TINY)
			write(STDOUT_FILENO, "tiny", 4);
		else
			write(STDOUT_FILENO, "small", 5);
		write(STDOUT_FILENO, "\n      block:\t\t", 15);
		ft_putaddress((unsigned long)action->block_or_large);
		write(STDOUT_FILENO, "\n      zone:\t\t", 14);
		ft_putaddress((unsigned long)action->zone);
	}

	ft_show_error(action->error);
}

void ft_show_action_free(t_action *action) {
	write(STDOUT_FILENO, ANSI_COLOR_YELLOW, ANSI_COLOR_LEN);
	write(STDOUT_FILENO, "   action", 9);
	write(STDOUT_FILENO, ANSI_COLOR_RESET, ANSI_COLOR_LEN);
	write(STDOUT_FILENO, ": free\n", 7);

	write(STDOUT_FILENO, "      address:\t\t", 16);
	ft_putaddress((unsigned long)action->address);
	write(STDOUT_FILENO, "\n      bytes:\t\t", 15);
	ft_putnbr(action->size);
	write(STDOUT_FILENO, "\n      zone type:\t", 19);

	if (action->zone_type == LARGE) {
		write(STDOUT_FILENO, "large", 5);
		write(STDOUT_FILENO, "\n      block/zone:\t", 20);
		ft_putaddress((unsigned long)action->block_or_large);
	}
	else if (action->zone_type == NOWHERE) {
			write(STDOUT_FILENO, "nowhere", 7);
	}
	else {
		if (action->zone_type == TINY)
			write(STDOUT_FILENO, "tiny", 4);
		else
			write(STDOUT_FILENO, "small", 5);
		write(STDOUT_FILENO, "\n      block:\t\t", 15);
		ft_putaddress((unsigned long)action->block_or_large);
		write(STDOUT_FILENO, "\n      zone:\t\t", 14);
		ft_putaddress((unsigned long)action->zone);
	}

	ft_show_error(action->error);
}

void ft_show_action_realloc(t_action *action) {
	write(STDOUT_FILENO, ANSI_COLOR_YELLOW, ANSI_COLOR_LEN);
	write(STDOUT_FILENO, "   action", 9);
	write(STDOUT_FILENO, ANSI_COLOR_RESET, ANSI_COLOR_LEN);
	write(STDOUT_FILENO, ": realloc\n", 10);

	write(STDOUT_FILENO, "      address:\t\t", 16);
	ft_putaddress((unsigned long)action->address);
	write(STDOUT_FILENO, " > ", 3);
	ft_putaddress((unsigned long)action->new_address);
	write(STDOUT_FILENO, "\n      bytes:\t\t", 15);
	ft_putnbr(action->size);
	write(STDOUT_FILENO, " > ", 3);
	ft_putnbr(action->new_size);
	write(STDOUT_FILENO, "\n      zone type:\t", 18);
	ft_show_zone_type(action->zone_type, action->new_zone_type);
	write(STDOUT_FILENO, "\n      block:\t\t", 15);
	ft_putaddress((unsigned long)action->block_or_large);
	write(STDOUT_FILENO, " > ", 3);
	ft_putaddress((unsigned long)action->new_block_or_large);
	write(STDOUT_FILENO, "\n      zone:\t\t", 14);
	ft_putaddress((unsigned long)action->zone);
	write(STDOUT_FILENO, " > ", 3);
	ft_putaddress((unsigned long)action->new_zone);

	ft_show_error(action->error);
}

void show_history(int depth) {
	pthread_mutex_lock(&g_lock);		// LOCK

	int showed = g_.actions;
	if (depth < showed)
		showed = depth;
	if (HISTORY_SIZE < depth)
		showed = HISTORY_SIZE;

	write(STDOUT_FILENO, ANSI_COLOR_YELLOW, ANSI_COLOR_LEN);
	write(STDOUT_FILENO, "\nhistory", 8);
	write(STDOUT_FILENO, ANSI_COLOR_RESET, ANSI_COLOR_LEN);
	write(STDOUT_FILENO, ": [actions:", 11);

	ft_putnbr(g_.actions);
    write(STDOUT_FILENO, "] [showed:", 10);
	ft_putnbr(showed);
    write(STDOUT_FILENO, "]\n", 2);

	for (int i = 0; i < showed; i++)
		switch (g_.history[i].type)
		{
			case TINY:
				ft_show_action_malloc(&g_.history[i]);
				break;
			case SMALL:
				ft_show_action_free(&g_.history[i]);
				break;
			case LARGE:
				ft_show_action_realloc(&g_.history[i]);
				break;
		}
	write(STDOUT_FILENO, "\n", 1);
	pthread_mutex_unlock(&g_lock);		// UNLOCK
}

void ft_show_zone(t_zone *zone) {
    if (zone) {
        t_block *block;
        block = zone->blocks;
        while (block) {
			write(STDOUT_FILENO, ANSI_COLOR_YELLOW, ANSI_COLOR_LEN);
			write(STDOUT_FILENO, "      block ", 12);
			write(STDOUT_FILENO, ANSI_COLOR_RESET, ANSI_COLOR_LEN);
			ft_putaddress((unsigned long)block);
			write(STDOUT_FILENO, ":\n", 2);

			write(STDOUT_FILENO, "         prev: ", 15);
			ft_putaddress((unsigned long)block->prev);
			write(STDOUT_FILENO, "\n         free: ", 16);
			if (block->free) {
				write(STDOUT_FILENO, ANSI_COLOR_BLUE, ANSI_COLOR_LEN);
				write(STDOUT_FILENO, "true", 4);
				write(STDOUT_FILENO, ANSI_COLOR_RESET, ANSI_COLOR_LEN);
			}
			else {
				write(STDOUT_FILENO, ANSI_COLOR_RED, ANSI_COLOR_LEN);
				write(STDOUT_FILENO, "false", 5);
				write(STDOUT_FILENO, ANSI_COLOR_RESET, ANSI_COLOR_LEN);
			}
			write(STDOUT_FILENO, "\t", 1);
			ft_putnbr(block->size);
			if (block->size != 1)
				write(STDOUT_FILENO, "\tbytes", 6);
			else
				write(STDOUT_FILENO, "\tbyte", 5);
			write(STDOUT_FILENO, "\n         next: ", 17);
			ft_putaddress((unsigned long)block->next);
			write(STDOUT_FILENO, "\n", 1);


            block = block->next;
        }
		write(STDOUT_FILENO, "\n", 1);
    }
}

void ft_show_large(t_large *large) {
	if (large) {
		write(STDOUT_FILENO, ANSI_COLOR_YELLOW, ANSI_COLOR_LEN);
		write(STDOUT_FILENO, "      block ", 12);
		write(STDOUT_FILENO, ANSI_COLOR_RESET, ANSI_COLOR_LEN);
		ft_putaddress((unsigned long)large);
		write(STDOUT_FILENO, ":\n", 2);

		write(STDOUT_FILENO, "         prev:\t", 15);
		ft_putaddress((unsigned long)large->prev);
		write(STDOUT_FILENO, "\n         ", 10);
		if (large->size != 1)
			write(STDOUT_FILENO, "bytes", 5);
		else
			write(STDOUT_FILENO, "byte", 4);
		write(STDIN_FILENO, ":\t", 2);
		ft_putnbr((unsigned long)large->size);
		write(STDOUT_FILENO, "\n         next:\t", 17);
		ft_putaddress((unsigned long)large->next);
		write(STDIN_FILENO, "\n\n", 2);
	}
}

void show_alloc_mem_ex(void) {
	pthread_mutex_lock(&g_lock);		// LOCK
    
	t_zone *zone = g_.tiny_first_zone;

	if (zone) {
		write(STDOUT_FILENO, ANSI_COLOR_YELLOW, ANSI_COLOR_LEN);
		write(STDOUT_FILENO, "\ntiny", 5);
		write(STDOUT_FILENO, ANSI_COLOR_RESET, ANSI_COLOR_LEN);
		write(STDOUT_FILENO, ":\n", 2);

		while (zone) {
			write(STDOUT_FILENO, ANSI_COLOR_YELLOW, ANSI_COLOR_LEN);
			write(STDOUT_FILENO, "   zone ", 8);
			write(STDOUT_FILENO, ANSI_COLOR_RESET, ANSI_COLOR_LEN);
			ft_putaddress((unsigned long)zone);
			write(STDOUT_FILENO, ":\n", 2);

			ft_show_zone(zone);
			zone = zone->next;
		}
	}
    zone = g_.small_first_zone;
	if (zone) {
		write(STDOUT_FILENO, ANSI_COLOR_YELLOW, ANSI_COLOR_LEN);
		write(STDOUT_FILENO, "small", 5);
		write(STDOUT_FILENO, ANSI_COLOR_RESET, ANSI_COLOR_LEN);
		write(STDOUT_FILENO, ":\n", 2);

		while (zone) {
			write(STDOUT_FILENO, ANSI_COLOR_YELLOW, ANSI_COLOR_LEN);
			write(STDOUT_FILENO, "   zone ", 8);
			write(STDOUT_FILENO, ANSI_COLOR_RESET, ANSI_COLOR_LEN);
			ft_putaddress((unsigned long)zone);
			write(STDOUT_FILENO, ":\n", 2);

			ft_show_zone(zone);
			zone = zone->next;
		}
	}
    t_large *large = g_.larges;
	if (large) {
		write(STDOUT_FILENO, ANSI_COLOR_YELLOW, ANSI_COLOR_LEN);
		write(STDOUT_FILENO, "large", 5);
		write(STDOUT_FILENO, ANSI_COLOR_RESET, ANSI_COLOR_LEN);
		write(STDOUT_FILENO, ":\n", 2);

		while (large) {
			ft_show_large(large);
			large = large->next;
		}
	}
	write(STDOUT_FILENO, "\n", 1);
	pthread_mutex_unlock(&g_lock);		// UNLOCK
}