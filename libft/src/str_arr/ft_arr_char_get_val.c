#include "./lib_main.h"

char	*ft_arr_char_get_val(char **arr, char *key)
{
	int	i;
	int	key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (arr[i])
	{
		if (!ft_strncmp(arr[i], key, key_len))
			if (arr[i][key_len] == '=')
				return (ft_strdup((arr[i]) + key_len + 1));
		i++;
	}
	return (NULL);
}
