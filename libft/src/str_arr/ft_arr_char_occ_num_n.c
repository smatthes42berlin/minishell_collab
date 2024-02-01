#include "./lib_main.h"

int	ft_arr_char_occ_num_n(char **arr, char *val)
{
	int	i;
	int	key_length;
	int	num_occ;

	key_length = ft_str_chr_index(val, '=');
	i = 0;
	num_occ = 0;
	while (arr[i])
	{
		if (!ft_strncmp(arr[i], val, key_length))
			num_occ++;
		i++;
	}
	return (num_occ);
}
