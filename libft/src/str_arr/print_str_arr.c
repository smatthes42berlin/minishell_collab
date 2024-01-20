#include "./lib_main.h"

void	print_str_arr(char **arr, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		ft_printf("%s\n", arr[i]);
		i++;
	}
}
