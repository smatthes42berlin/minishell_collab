#include "lib_main.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*s_u;
	size_t			i;

	i = 0;
	s_u = (unsigned char *)s;
	while (i < n)
	{
		s_u[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
