#include "lib_main.h"

static void	put_character_ul(int fd, unsigned long nbr, t_base_info base_info,
				size_t *chars_printed);

size_t	ft_putnbr_base_fd_ul(int fd, unsigned long nbr, const char *base)
{
	t_base_info	base_info;
	size_t		chars_printed;

	chars_printed = 0;
	if (!ft_putnbr_base_check(base, &base_info))
		return (0);
	put_character_ul(fd, nbr, base_info, &chars_printed);
	return (chars_printed);
}

void	put_character_ul(int fd, unsigned long nbr, t_base_info base_info,
		size_t *chars_printed)
{
	long	base_index;
	long	num_div;

	if (nbr < (unsigned long)base_info.base_len)
	{
		*chars_printed += ft_putchar_fd_len(base_info.base[nbr], fd);
	}
	else
	{
		base_index = nbr % (unsigned long)base_info.base_len;
		num_div = nbr / base_info.base_len;
		put_character_ul(fd, num_div, base_info, chars_printed);
		*chars_printed += ft_putchar_fd_len(base_info.base[base_index], fd);
	}
}
