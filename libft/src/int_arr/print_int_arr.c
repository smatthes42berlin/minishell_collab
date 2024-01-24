#include "./lib_main.h"

void	print_int_arr(int *arr, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		ft_printf("%d\n", arr[i]);
		i++;
	}
}
