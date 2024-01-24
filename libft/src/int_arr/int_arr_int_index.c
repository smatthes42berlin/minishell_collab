#include "./lib_main.h"

int	int_arr_int_index(int *arr, int search, int arr_len)
{
	int	i;

	i = 0;
	while (i < arr_len)
	{
		if (arr[i] == search)
			return (i);
		i++;
	}
	return (-1);
}
