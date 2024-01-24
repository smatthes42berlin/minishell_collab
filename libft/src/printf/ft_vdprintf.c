#include "lib_main.h"

static void	handle_specifiers(int fd, const char *cur_format,
				ssize_t *spec_chars_written, va_list args);

int	ft_vdprintf(int fd, const char *format, va_list args)
{
	int		i;
	ssize_t	spec_chars_written;
	int		tot_write_count;

	i = 0;
	tot_write_count = 0;
	if (!format)
		return (-1);
	while (format[i])
	{
		handle_specifiers(fd, &format[i], &spec_chars_written, args);
		if (spec_chars_written >= 0)
		{
			i += 2;
			tot_write_count += spec_chars_written;
		}
		else
		{
			tot_write_count += ft_putchar_fd_len(format[i], fd);
			i++;
		}
	}
	return (tot_write_count);
}

static void	handle_specifiers(int fd, const char *cur_format,
		ssize_t *spec_chars_written, va_list args)
{
	if (cur_format[0] != '%')
		*spec_chars_written = -1;
	else if (cur_format[1] == 'c')
		*spec_chars_written = handle_c(fd, args);
	else if (cur_format[1] == 's')
		*spec_chars_written = handle_s(fd, args);
	else if (cur_format[1] == 'p')
		*spec_chars_written = handle_p(fd, args);
	else if (ft_strchr("id", cur_format[1]))
		*spec_chars_written = handle_d_i(fd, args);
	else if (cur_format[1] == 'u')
		*spec_chars_written = handle_u(fd, args);
	else if (cur_format[1] == 'x')
		*spec_chars_written = handle_x(fd, args);
	else if (cur_format[1] == 'X')
		*spec_chars_written = handle_cap_x(fd, args);
	else if (cur_format[1] == '%')
		*spec_chars_written = ft_putchar_fd_len('%', fd);
	else
		*spec_chars_written = -2;
}
