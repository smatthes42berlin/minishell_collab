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

int	ft_printf_to_str(char **res, const char *format, ...)
{
	va_list	args;
	int		chars_printed;
	int		fd[2];

	if (pipe(fd))
		return (-1);
	va_start(args, format);
	chars_printed = ft_vdprintf(fd[1], format, args);
	va_end(args);
	if (close(fd[1]))
		return (-1);
	if (read_whole_file(fd[0], res) == -1)
		return (-1);
	if (close(fd[0]))
		return (-1);
	return (chars_printed);
}
