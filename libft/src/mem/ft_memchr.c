#include "lib_main.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_u;
	unsigned char	c_u;
	size_t			i;

	i = 0;
	s_u = (unsigned char *)s;
	c_u = (unsigned char)c;
	if (n == 0)
		return (NULL);
	while (i < n)
	{
		if (s_u[i] == c_u)
			return ((void *)(s_u + i));
		i++;
	}
	return (NULL);
}
