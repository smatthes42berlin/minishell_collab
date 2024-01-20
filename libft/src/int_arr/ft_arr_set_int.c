#include "./lib_main.h"

size_t	ft_arr_set_int(int *arr, size_t size, int num)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		arr[i] = num;
		i++;
	}
	return (i);
}
