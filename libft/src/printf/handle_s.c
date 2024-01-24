#include "lib_main.h"

size_t	handle_s(int fd, va_list args)
{
	char	*str;

	str = va_arg(args, char *);
	if (!str)
		return (ft_putstr_fd_len("(null)", fd));
	return (ft_putstr_fd_len(str,
			fd));
}
