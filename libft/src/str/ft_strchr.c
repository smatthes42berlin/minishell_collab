#include "lib_main.h"

char	*ft_strchr(const char *s, int c)
{
	char	c_cast;

	c_cast = (unsigned char)c;
	if (*s == c_cast)
		return ((char *)s);
	while (*s != c_cast && *s)
		s++;
	if (*s == c_cast)
		return ((char *)s);
	return (NULL);
}
