#include "lib_main.h"

void	free_str_arr(char **str_arr, int num)
{
	num--;
	while (num >= 0)
	{
		free(str_arr[num]);
		num--;
	}
	free(str_arr);
}
