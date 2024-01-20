#include "./lib_main.h"

size_t	ft_split_num_substr(char const *s, char c)
{
	size_t	state;
	size_t	num_substr;
	int		i;

	state = 0;
	num_substr = 0;
	i = -1;
	while (s[++i])
	{
		if (state == 0 && s[i] != c)
		{
			state = 1;
			num_substr++;
		}
		if (state == 1 && s[i] == c)
			state = 0;
	}
	return (num_substr);
}
