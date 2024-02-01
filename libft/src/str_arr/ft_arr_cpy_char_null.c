#include "./lib_main.h"

char	**ft_arr_cpy_char_null(char **arr)
{
	int		i;
	int		arr_len;
	char	**cpy;

	arr_len = ft_arr_len_char(arr);
	i = 0;
	cpy = malloc(sizeof(*cpy) * (arr_len + 1));
	if (!cpy)
		return (NULL);
	while (i < arr_len)
	{
		cpy[i] = ft_strdup(arr[i]);
		if (!cpy[i])
		{
			free_str_arr(cpy, i - 1);
			return (NULL);
		}
		i++;
	}
	cpy[arr_len] = NULL;
	return (cpy);
}
