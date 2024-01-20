#include "lib_main.h"

size_t	handle_p(int fd, va_list args)
{
	char			*base;
	unsigned long	ptr_l;
	size_t			chars_written;

	base = "0123456789abcdef";
	ptr_l = va_arg(args, unsigned long);
	if (ptr_l == 0)
		chars_written = ft_putstr_fd_len("(nil)", fd);
	else
	{
		chars_written = ft_putstr_fd_len("0x", fd);
		chars_written += ft_putnbr_base_fd_ul(fd, ptr_l, base);
	}
	return (chars_written);
}
