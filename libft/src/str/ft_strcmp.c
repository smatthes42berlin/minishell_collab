#include "lib_main.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	c1_u;
	unsigned char	c2_u;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] == s2[i] && s1[i])
		i++;
	c1_u = (unsigned char)s1[i];
	c2_u = (unsigned char)s2[i];
	if (c1_u > c2_u)
		return (1);
	if (c1_u < c2_u)
		return (-1);
	return (0);
}
