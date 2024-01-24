#include "./lib_main.h"

int	malloc_error_free(char **res, size_t i_num_substr,
size_t substr_len)
{
	size_t	i;

	res[i_num_substr] = malloc(sizeof(**res) * (substr_len + 1));
	if (!res[i_num_substr])
	{
		i = 0;
		while (i < i_num_substr)
		{
			free(res[i]);
			i++;
		}
		free(res);
		return (0);
	}
	return (1);
}
