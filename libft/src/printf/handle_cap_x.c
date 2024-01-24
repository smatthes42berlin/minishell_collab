#include "lib_main.h"

size_t	handle_cap_x(int fd, va_list args)
{
	char			*base;
	unsigned long	nbr;

	nbr = (unsigned long)va_arg(args, unsigned int);
	base = "0123456789ABCDEF";
	return (ft_putnbr_base_fd_ul(fd, nbr, base));
}
