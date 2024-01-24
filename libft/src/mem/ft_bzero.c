#include "lib_main.h"

void	*ft_bzero(void *s, size_t n)
{
	unsigned char	*s_u;

	s_u = (unsigned char *)s;
	while (n > 0)
	{
		s_u[n - 1] = '\0';
		n--;
	}
	return (s);
}
