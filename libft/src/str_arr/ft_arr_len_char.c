#include "./lib_main.h"

size_t	ft_arr_len_char(char **arr)
{
	size_t	arr_len;

	arr_len = 0;
	if (!arr || !arr[0])
		return (arr_len);
	while (arr[arr_len])
		arr_len++;
	return (arr_len);
}
