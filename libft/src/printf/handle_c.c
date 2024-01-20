#include "lib_main.h"

size_t	handle_c(int fd, va_list args)
{
	unsigned char	c;

	c = (unsigned char)va_arg(args, int);
	return (ft_putchar_fd_len(c, fd));
}
