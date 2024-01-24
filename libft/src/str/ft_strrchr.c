#include "lib_main.h"

char	*ft_strrchr(const char *s, int c)
{
	char		c_cast;
	size_t		s_len;
	const char	*str_start;

	s_len = ft_strlen(s);
	c_cast = (unsigned char)c;
	str_start = s;
	s = s + s_len;
	while (s != str_start && c_cast != *s)
		s--;
	if (*s == c_cast)
		return ((char *)s);
	return (NULL);
}
