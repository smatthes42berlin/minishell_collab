#include "lib_main.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	c1_u;
	unsigned char	c2_u;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] && i < (n - 1))
		i++;
	c1_u = (unsigned char)s1[i];
	c2_u = (unsigned char)s2[i];
	if (c1_u > c2_u)
		return (1);
	if (c1_u < c2_u)
		return (-1);
	return (0);
}
