#include "lib_main.h"

int	str_contains_str_index(const char *big, const char *little)
{
	int	i;
	int	j;

	i = 0;
	if (!little || !big)
		return (-1);
	if (!*little)
		return (ft_strlen(big) - 1);
	while (big[i])
	{
		if (big[i] == *little)
		{
			j = 0;
			while (big[i + j] == little[j] && little[j])
			{
				j++;
			}
			if (!little[j])
				return (i);
		}
		i++;
	}
	return (-1);
}
