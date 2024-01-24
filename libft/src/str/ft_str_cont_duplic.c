#include "lib_main.h"

int	ft_str_cont_duplic(const char *str)
{
	int				count[256];
	int				i;
	int				num_cur_char;
	unsigned char	cur_char;

	ft_arr_set_int(count, 256, 0);
	i = 0;
	while (str[i])
	{
		cur_char = (unsigned char)str[i];
		num_cur_char = count[cur_char] + 1;
		count[cur_char] = num_cur_char;
		if (num_cur_char > 1)
			return (1);
		i++;
	}
	return (0);
}
