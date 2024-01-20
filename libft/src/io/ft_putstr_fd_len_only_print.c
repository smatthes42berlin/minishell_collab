#include "lib_main.h"

int		ft_isprint(int c);
size_t	ft_putchar_fd_len(char c, int fd);

size_t	ft_putstr_fd_len_only_print(char *s, int fd)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (ft_isprint(s[i]))
		{
			ft_putchar_fd_len(s[i], fd);
			j++;
		}
		i++;
	}
	return (j);
}
