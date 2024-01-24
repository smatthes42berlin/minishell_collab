#include "lib_main.h"

size_t	ft_putchar_fd_len(char c, int fd)
{
	return ((size_t)write(fd, &c, 1));
}
