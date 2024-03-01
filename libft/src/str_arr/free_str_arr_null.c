#include "lib_main.h"

void	free_str_arr_null(char **str_arr)
{
	int	i;

	i = 0;
	if (!str_arr)
		return ;
	while (str_arr[i])
	{
		free(str_arr[i]);
		i++;
		str_arr[i] = NULL;
	}
	free(str_arr);
}
