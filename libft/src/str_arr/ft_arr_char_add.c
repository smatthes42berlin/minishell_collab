#include "./lib_main.h"

char	**free_null(char **cpy);

char	**ft_arr_char_add(char **arr, char *val)
{
	int		i;
	int		arr_len;
	char	**cpy;

	i = 0;
	arr_len = ft_arr_len_char(arr);
	cpy = malloc(sizeof(*cpy) * (arr_len + 1 + 1));
	if (!cpy)
		return (NULL);
	while (i < arr_len)
	{
		cpy[i] = ft_strdup(arr[i]);
		if (!cpy[i])
			return (free_null(cpy));
		i++;
	}
	cpy[i] = ft_strdup(val);
	if (!cpy[i])
		return (free_null(cpy));
	i++;
	cpy[i] = NULL;
	return (cpy);
}

char	**free_null(char **cpy)
{
	free_str_arr_null(cpy);
	return (NULL);
}
