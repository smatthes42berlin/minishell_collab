#include "lib_main.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*cmp_start;

	i = 0;
	if (!*little)
		return ((char *)big);
	while (i < len && big[i])
	{
		if (big[i] == *little)
		{
			cmp_start = (char *)(big + i);
			j = 0;
			while (big[i + j] == little[j] && little[j] && (i + j) <= len)
			{
				j++;
			}
			if (!little[j] && (i + j) <= len)
				return (cmp_start);
		}
		i++;
	}
	return (NULL);
}
