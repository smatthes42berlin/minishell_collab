#include "./lib_main.h"

void	print_str_arr_null(char **arr)
{
	while (*arr)
	{
		ft_printf_fd(2, "%s\n", *arr);
		arr++;
	}
}
