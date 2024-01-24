#include "lib_main.h"

int	count_lines_fd(int fd)
{
	int		line_num;
	int		num_bytes;
	int		i;
	char	buffer[BUFFER_SIZE];

	num_bytes = read(fd, buffer, BUFFER_SIZE);
	if (num_bytes == 0)
		return (0);
	line_num = 1;
	while (num_bytes != 0)
	{
		i = 0;
		if (num_bytes == -1)
			return (-1);
		while (i < num_bytes)
		{
			if (buffer[i] == '\n')
				line_num++;
			i++;
		}
		num_bytes = read(fd, buffer, BUFFER_SIZE);
	}
	return (line_num);
}
