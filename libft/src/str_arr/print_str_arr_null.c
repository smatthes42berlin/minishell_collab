#include "./lib_main.h"

void	print_str_arr_null(char **arr)
{
	if (!arr)
		ft_printf("(null)\n");
	while (arr && *arr)
	{
		ft_printf_fd(2, "%s\n", *arr);
		arr++;
	}
}
