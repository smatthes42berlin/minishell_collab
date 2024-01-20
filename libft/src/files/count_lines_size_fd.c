#include "lib_main.h"

int	count_lines_size_fd(int fd, t_file_info *file_info)
{
	int		line_num;
	int		num_bytes;
	int		i;
	char	buffer[BUFFER_SIZE];

	num_bytes = read(fd, buffer, BUFFER_SIZE);
	if (num_bytes == 0)
		return (0);
	line_num = 1;
	file_info->file_size = 0;
	while (num_bytes != 0)
	{
		i = 0;
		if (num_bytes == -1)
			return (-1);
		file_info->file_size += num_bytes;
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
