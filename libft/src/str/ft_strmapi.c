#include "lib_main.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			s_len;
	char			*map_str;
	unsigned int	i;

	s_len = ft_strlen(s);
	map_str = malloc(sizeof(*map_str) * (s_len + 1));
	if (!map_str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		map_str[i] = f(i, s[i]);
		i++;
	}
	map_str[i] = '\0';
	return (map_str);
}
