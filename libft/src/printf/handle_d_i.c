#include "lib_main.h"

size_t	handle_d_i(int fd, va_list args)
{
	char	*base;
	long	nbr;

	nbr = (long)va_arg(args, int);
	base = "0123456789";
	return (ft_putnbr_base_fd_l(fd, nbr, base));
}
