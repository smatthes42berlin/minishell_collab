#include "lib_main.h"

static int	free_res_code(char **res, int code);

int	read_whole_file(int fd, char **res)
{
	int		num_bytes;
	char	*tmp;
	char	buffer[BUFFER_SIZE + 1];

	*res = NULL;
	num_bytes = read(fd, buffer, BUFFER_SIZE);
	if (num_bytes == -1)
		return (-1);
	if (num_bytes == 0)
		return (0);
	buffer[num_bytes] = '\0';
	if (ft_str_n_dup_int(buffer, 0, res) == -1)
		return (-1);
	while (num_bytes == BUFFER_SIZE)
	{
		num_bytes = read(fd, buffer, BUFFER_SIZE);
		if (num_bytes == -1)
			return (-1);
		buffer[num_bytes] = '\0';
		if (ft_str_n_join_int(*res, buffer, 0, &tmp) == -1)
			return (free_res_code(res, -1));
		free(*res);
		*res = tmp;
	}
	return (0);
}

static int	free_res_code(char **res, int code)
{
	free(*res);
	return (code);
}
