#include "lib_main.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		chars_printed;

	va_start(args, format);
	chars_printed = ft_vdprintf(1, format, args);
	va_end(args);
	return (chars_printed);
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	va_list	args;
	int		chars_printed;

	va_start(args, format);
	chars_printed = ft_vdprintf(fd, format, args);
	va_end(args);
	return (chars_printed);
}
